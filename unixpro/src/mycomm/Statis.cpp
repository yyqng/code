
#include "Statis.h"
#include <limits>
#include <stdio.h>
#include <unistd.h>

SINGLETON_CLASS_INIT(Statis);

std::string GetTimeStringFileName(time_t tNewTime)
{
    std::string fileName = "";
 
    struct tm tmpTm = *localtime(&tNewTime);
    struct tm* sTm = &tmpTm;

    char buf[30]={0};
    //snprintf(buf,sizeof(buf),"%d%02d%02d%02d%02d%02d",sTm->tm_year+1900,sTm->tm_mon+1,
	snprintf( buf, sizeof(buf), "%d%02d%02d", sTm->tm_year+1900, sTm->tm_mon+1, sTm->tm_mday );
    fileName = std::string(buf);

    return fileName;
}

Statis::Statis()
{
    m_tStart = ::time(NULL);  
    m_lastTimeOutput = ::time(NULL); 
    struct tm tmpTm = *localtime(&m_tStart);
    struct tm* sTm = &tmpTm;
            
    snprintf(m_chTimeForm,sizeof(m_chTimeForm),"%d-%02d-%02d %02d:%02d:%02d",sTm->tm_year+1900,sTm->tm_mon+1,
        sTm->tm_mday,sTm->tm_hour,sTm->tm_min,sTm->tm_sec);    

    m_logFileName =  std::string("log/spycap-")+ GetTimeStringFileName(m_tStart)+ ".log";
}

Statis::~Statis()
{
}


void Statis::AddStatis(StatisItem item, unsigned long value)
{
    switch (item)
    {
        case READ_PKT_SUC_CNT:
            m_generalStatis.read_pkt_suc_cnt+= value;
            break;
        case READ_PKT_ERR_CNT:
            m_generalStatis.read_pkt_err_cnt+= value;
            break;
        case SEND_PKT_SUC_CNT:
            m_generalStatis.send_pkt_suc_cnt+= value;
            break;
        case SEND_PKT_ERR_CNT:
            m_generalStatis.send_pkt_err_cnt+= value;
            break;
        case DISCARD_PKT_SUC_CNT:
            m_generalStatis.discard_pkt_suc_cnt+= value;
            break;
        case DISCARD_PKT_ERR_CNT:
            m_generalStatis.discard_pkt_err_cnt+= value;
            break;    
        case CTRL_PKT_CNT:
            m_generalStatis.ctrl_pkt_cnt+= value;
            break;  
        case BROAD_PKT_CNT:
            m_generalStatis.broad_pkt_cnt+= value;
            break;             
        default:
            break;
    };
    ShowStatis();
}

void Statis::ShowStatis()
{
    time_t tmpTime = ::time(NULL);
    if(tmpTime-m_lastTimeOutput>=0)
    {
        m_lastTimeOutput = tmpTime;
        std::ostringstream oss;
        int   prec=std::numeric_limits<double>::digits10;
        oss.precision(prec);

        oss<<"===================ReadZdtqQueue STATIS START============\n";
       

        oss<<"******statis from time: "<<m_chTimeForm<<"******"<<std::endl;       

        oss<<"read_pkt_suc_cnt"<<":\t"<<m_generalStatis.read_pkt_suc_cnt<<std::endl;
        oss<<"read_pkt_err_cnt"<<":\t"<<m_generalStatis.read_pkt_err_cnt<<std::endl;
        oss<<"send_pkt_suc_cnt"<<":\t"<<m_generalStatis.send_pkt_suc_cnt<<std::endl;
        oss<<"send_pkt_err_cnt"<<":\t"<<m_generalStatis.send_pkt_err_cnt<<std::endl;
        oss<<"discard_pkt_suc_cnt"<<":\t"<<m_generalStatis.discard_pkt_suc_cnt<<std::endl;
        oss<<"discard_pkt_err_cnt"<<":\t"<<m_generalStatis.discard_pkt_err_cnt<<std::endl; 
        oss<<"ctrl_pkt_cnt"<<":\t"<<m_generalStatis.ctrl_pkt_cnt<<std::endl; 
        oss<<"broad_pkt_cnt"<<":\t"<<m_generalStatis.broad_pkt_cnt<<std::endl; 
        
        time_t timevalue = ::time(NULL) - m_tStart;
        if (timevalue == 0)
            timevalue = 1;
        oss<<"read_pkt_suc_cnt mean"<<":\t"<<m_generalStatis.read_pkt_suc_cnt/timevalue<<" /sec"<<std::endl;
        oss<<"read_pkt_err_cnt mean"<<":\t"<<m_generalStatis.read_pkt_err_cnt/timevalue<<" /sec"<<std::endl;
        oss<<"send_pkt_suc_cnt mean"<<":\t"<<m_generalStatis.send_pkt_suc_cnt/timevalue<<" /sec"<<std::endl;
        oss<<"send_pkt_err_cnt mean"<<":\t"<<m_generalStatis.send_pkt_err_cnt/timevalue<<" /sec"<<std::endl;
        oss<<"discard_pkt_suc_cnt mean"<<":\t"<<m_generalStatis.discard_pkt_suc_cnt/timevalue<<" /sec"<<std::endl;
        oss<<"discard_pkt_err_cnt mean"<<":\t"<<m_generalStatis.discard_pkt_err_cnt/timevalue<<" /sec"<<std::endl;

        oss<<"===================ReadZdtqQueue END==============\n";

        long length = GetFileSize(m_logFileName.data());
        if(length>FILE_MAX_SIZE)
        {
            //unlink(m_logFileName.data());
            m_logFileName =  std::string("log/")+ GetTimeStringFileName(tmpTime)+ ".log";
        }
        
       	FILE* fp = fopen(m_logFileName.data(), "a");
    	if(NULL == fp)
    	{
    		return;
    	}

        struct tm *sTm = localtime(&tmpTime);
        char chTimeForm[20];
        snprintf(chTimeForm,sizeof(chTimeForm),"%d-%02d-%02d %02d:%02d:%02d\n",sTm->tm_year+1900,sTm->tm_mon+1,
        sTm->tm_mday,sTm->tm_hour,sTm->tm_min,sTm->tm_sec);
        fwrite(chTimeForm, sizeof(char),sizeof(chTimeForm), fp);
    	fwrite(oss.str().data(), sizeof(char), oss.str().size(), fp);
    	fclose(fp);     
    }
}

long Statis::GetFileSize(const char *fileName)
{
    if(NULL==fileName)
    {
        return 0;
    }

    long length = 0;
    FILE *fp = NULL;
    fp = fopen(fileName,"rb");
    if(NULL!=fp)
    {
        fseek(fp,0,SEEK_END);
        length = ftell(fp);
    }
    if(NULL!=fp)
    {
        fclose(fp);
        fp = NULL;
    }

    return length;
}



