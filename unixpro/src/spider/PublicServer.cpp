#include <arpa/inet.h>

#include <openssl/md5.h>

#include "Log.h"
#include "keys.h"
#include "conststr.h"
#include "PublicServer.h"
#include "PublicConnectionManager.h"
#include "SpiderEventDispatcher.h"
#include "PublicConnection.h"

namespace spider
{

    const char * const PublicServer::s_tag = "PubServer";
    static auto & s_connectionMgr = spider::PublicConnectionManager::GetInstance();

    PublicServer & PublicServer::GetInstance(void)
    {
        static PublicServer s_inst; // 局部静态变量的初始化从C++11标准开始是线程安全的
        return s_inst;
    }

    void PublicServer::OnAccept(FileDescriptor && sock, sockaddr_storage & addr, socklen_t)
    {
        uint32_t const events = EventDispatcher::READ | EventDispatcher::EDGE | EventDispatcher::CLOSE;

        // 创建客户端对象
        auto listener = spider::make_unique<PublicConnection>(reinterpret_cast<sockaddr_in &>(addr).sin_addr.s_addr,
            reinterpret_cast<sockaddr_in &>(addr).sin_port, std::move(sock), 64 << 10, events, &m_key, m_iv);
        CheckExprLogReturnVoid(listener, Log::ERR, s_tag, "failed to alloacte public connection object\n");

        // 创建客户端连接对象，并订阅事件
        CheckExprLogReturnVoid(s_connectionMgr.AddConnection(std::move(listener), events), Log::ERR,
                                s_tag, "failed to subscribe for new public connection: %s\n", strerror(errno));

        sLog.Write(Log::INF, s_tag, "new connection %s:%d\n",
                   inet_ntoa(reinterpret_cast<sockaddr_in&>(addr).sin_addr),
                   htons(reinterpret_cast<sockaddr_in&>(addr).sin_port));
    }

    void PublicServer::InitializeCrypto(void)
    {
        const conststr keystr(KEY_STR);

        MD5_CTX ctx;
        MD5_Init(&ctx);
        MD5_Update(&ctx, keystr.begin(), keystr.length());

        unsigned char keybits[16];
        MD5_Final(keybits, &ctx);
        AES_set_decrypt_key(keybits, sizeof keybits << 3, &m_key);

        MD5_Update(&ctx, keybits, sizeof keybits);
        MD5_Final(m_iv, &ctx);
    }

} // namespace spider
