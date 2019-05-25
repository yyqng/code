#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>

#include <cerrno>
#include <cassert>

#include "comm.h"
#include "Log.h"
#include "TcpServer.h"

const char * const TcpServer::s_tag = "TcpServer";

bool TcpServer::Listen(const unsigned short port)
{
    // create socket
    FileDescriptor sock(::socket(AF_INET, SOCK_STREAM, 0));
    CheckExprLogReturnValue(sock, false, Log::ERR, s_tag, "Create socket failed, %s\n", strerror(errno));

    // set address reuse
    auto yes = 1;
    ::setsockopt(sock.Get(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    // set non-blocking
    CheckExprLogReturnValue(sock.SetNonblocking(), false, Log::ERR, s_tag, "Set socket nonblocking failed, %s\n", strerror(errno));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    // bind to *:port
    CheckExprLogReturnValue(::bind(sock.Get(), reinterpret_cast<sockaddr *>(&addr), sizeof addr) == 0, false,
                            Log::ERR, s_tag, "Bind socket failed, %s\n", strerror(errno));

    // listen
    CheckExprLogReturnValue(::listen(sock.Get(), 1024) == 0, false, Log::ERR, s_tag, "Listen socket failed, %s\n", strerror(errno));

    // set m_sock
    m_sock = std::move(sock);

    return true;
}

bool TcpServer::Listen(const char * path)
{
    assert(path);

    // check UNIX domain socket path length
    auto const pathlen = strlen(path);
    CheckExprLogReturnValue(pathlen < sizeof static_cast<sockaddr_un *>(nullptr)->sun_path, false,
                            Log::ERR, s_tag, "UNIX socket path is too long, len=%d\n", pathlen);

    // create UNIX socket
    FileDescriptor sock(::socket(AF_UNIX, SOCK_STREAM, 0));
    CheckExprLogReturnValue(sock, false, Log::ERR, s_tag, "Create socket failed, %s\n", strerror(errno));

    // set address reuse
    auto yes = 1;
    ::setsockopt(sock.Get(), SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);

    // set non-blocking
    CheckExprLogReturnValue(sock.SetNonblocking(), false,
                            Log::ERR, s_tag, "Set socket nonblocking failed, %s\n", strerror(errno));

    sockaddr_un addr{ };
    addr.sun_family = AF_UNIX;
    strcpy(addr.sun_path, path);

    // unlink & bind unix domain socket path
    unlink(path);

    // bind to local UNIX domain socket path
    CheckExprLogReturnValue(::bind(sock.Get(), reinterpret_cast<sockaddr *>(&addr), sizeof addr.sun_family + pathlen) == 0, false,
                            Log::ERR, s_tag, "Bind failed, %s\n", strerror(errno));

    // listen
    CheckExprLogReturnValue(::listen(sock.Get(), 1024) == 0, false,
                            Log::ERR, s_tag, "Listen socket failed, %s\n", strerror(errno));

    // set m_sock
    m_sock = std::move(sock);

    return true;
}

void TcpServer::OnRead(void)
{
    sockaddr_storage addr;  // NOLINT
    socklen_t addrlen = sizeof addr;

    // 接收新连接，并且设置为非阻塞

    int fd;

    while ((fd = ::accept4(m_sock.Get(), reinterpret_cast<sockaddr *>(&addr), &addrlen, SOCK_NONBLOCK)) != -1)
    {
        OnAccept(FileDescriptor(fd), addr, addrlen); // 调用OnAccept接口，需要子类来实现该接口
    }

    if (errno != EAGAIN)
    {
        // TODO: error
    }
}
