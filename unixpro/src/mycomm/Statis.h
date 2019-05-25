#ifndef __STATIS_H__
#define __STATIS_H__
////////////////////////////////////////////////////////////////////////////////
///
/// @file Statis.h
///
/// @brief
///
////////////////////////////////////////////////////////////////////////////////


#include "Singleton.hpp"
#include <string>
#include <stdio.h>
#include <sstream>

#define FILE_MAX_SIZE   50*1024*1024

enum StatisItem
{
    READ_PKT_SUC_CNT,
    READ_PKT_ERR_CNT,
    SEND_PKT_SUC_CNT,
    SEND_PKT_ERR_CNT,
    DISCARD_PKT_SUC_CNT,
    DISCARD_PKT_ERR_CNT,
    CTRL_PKT_CNT,
    BROAD_PKT_CNT,
};


////////////////////////////////////////////////////////////////////////////////
/// 
/// @class Statis
/// 
/// @brief OAM��
///
////////////////////////////////////////////////////////////////////////////////
class Statis
{
    friend class TSingletonClass<Statis>;
    
public:

    void AddStatis(StatisItem item, unsigned long value);

private:

    Statis();
    virtual ~Statis();

    void ShowStatis();
    long GetFileSize(const char *fileName);
    
    struct GeneralStatis
    {
        unsigned long read_pkt_suc_cnt;  
        unsigned long read_pkt_err_cnt;  
        unsigned long send_pkt_suc_cnt;  
        unsigned long send_pkt_err_cnt;  
        unsigned long discard_pkt_suc_cnt;  
        unsigned long discard_pkt_err_cnt;  
        unsigned long ctrl_pkt_cnt;
        unsigned long broad_pkt_cnt;
        
        GeneralStatis()
        {
            Clear();
        }
                
        void Clear()
        {
            read_pkt_suc_cnt = 0;  
            read_pkt_err_cnt = 0;  
            send_pkt_suc_cnt = 0;  
            send_pkt_err_cnt = 0;  
            discard_pkt_suc_cnt = 0;  

        }
        

    };
    GeneralStatis m_generalStatis;
    
    time_t m_tStart;
    char m_chTimeForm[20];
    time_t m_lastTimeOutput;
    std::string m_logFileName;
};

#define sStatis TSingletonClass<Statis>::GetInstance()

#endif // __STATIS_H__



