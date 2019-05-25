#pragma once

#include <openssl/aes.h>

#include "TcpServer.h"
#include "Debug.h"

namespace spider
{

    /**
     * @brief 公版爬虫服务器，对外接收数据请求,数据通过加密传输
     */
    class PublicServer
        : public ::TcpServer
    {
    public:
        /**
         * @brief 禁止复制&移动
         */
        PublicServer(const PublicServer &) = delete;
        PublicServer & operator=(const PublicServer &) = delete;
        PublicServer(PublicServer &&) = delete;
        PublicServer & operator=(PublicServer &&) = delete;

        /**
         * @brief 获取单例对象的引用
         */
        static PublicServer & GetInstance(void);

        /**
         * @brief 获取解密密钥
         */
        const AES_KEY & GetDecryptKey(void) const { return m_key; }

        /**
         * @brief 获取解密初始向量
         */
        const unsigned char * GetDecryptInitialVector(void) const { return m_iv; }

    protected:
        /**
         * @brief 构造函数
         */
        PublicServer(void)
        {
            InitializeCrypto();
        }

        /**
         * @brief 默认析构函数
         */
        ~PublicServer(void) = default;

        /**
         * @brief 接收新连接事件处理函数
         * @param sock 新连接套接字
         * @param addr 客户端地址
         * @param addrlen 地址结构实际长度
         */
        void OnAccept(FileDescriptor && sock, sockaddr_storage & addr, socklen_t addrlen) override;

        /**
         * @brief close事件处理
         */
        void OnClose(void) override { DebugPrint("handle spider server close event\n"); }

        /**
         * @brief error事件处理
         */
        void OnError(void) override { DebugPrint("handle spider server error event\n"); }

        /**
         * @brief 初始化密钥与初始向量
         */
        void InitializeCrypto(void);

    private:
        AES_KEY m_key;
        unsigned char m_iv[16];
        static const char * const s_tag;
    }; // class SpiderPublicServer

} // namespace spider
