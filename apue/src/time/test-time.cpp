#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <signal.h>
#include <unistd.h>
extern int errno;

time_t convert_str_to_tm(char const* str_time)
{
    struct tm tt;  
    memset(&tt,0,sizeof(tt));  
    tt.tm_year=atoi(str_time)-1900;  
    tt.tm_mon=atoi(str_time+5)-1;  
    tt.tm_mday=atoi(str_time+8);  
    tt.tm_hour=atoi(str_time+11);  
    tt.tm_min=atoi(str_time+14);  
    tt.tm_sec=atoi(str_time+17);  
    return mktime(&tt);
}
int convert_str_to_int_time(std::string   const & str_time)                                                       
{
    int ret = (int)convert_str_to_tm(str_time.c_str());
    return ret; 
}


void sig_int(int signo )
{
        std::cout<<"int interrupt"<<std::endl;
        //exit(-1);//注释掉此句,函数返回后程序继续执行
}

void sig_fpe(int signo )
{
        std::cout<<"fpe interrupt"<<std::endl;
        exit(-1);//注释掉此句将导致死循环
}

void singnaltest(int argc , char *argv[] )
{
        if( signal(SIGFPE , sig_fpe) == SIG_ERR)
        {
            std::cout<<"catch SIGFPE error"<<std::endl;
        }

        if( signal(SIGINT , sig_int) == SIG_ERR) //CTR+C触发
        {
            std::cout<<"catch SIGINT error"<<std::endl;
        }

        sleep(3);
        //int i = 2/0; //exit(-1);
        std::cout<<"Program is going on"<<std::endl;
}


std::string getSystemTime()                                                                                   
{ 
    time_t t = time(NULL); //获取目前秒时间                        
    tm* local = localtime(&t); //转为本地时间
    
    char buf[128]= {0};                                            
    strftime(buf, 64, "%Y%m%d", local);                            
    std::cout << buf << std::endl;                                 
    std::string ret = buf;
    return ret;
    //tm* gmt = gmtime(&t);//转为格林威治时间                      
    //strftime(buf, 64, "%Y-%m-%d %H:%M:%S", gmt);  
    //std::cout << buf << std::endl;                               
   return 0; 
} 

std::string GetTimeStringFileName(time_t tNewTime)
{
    std::string fileName = "";
 
    struct tm tmpTm = *localtime(&tNewTime);
    struct tm* sTm = &tmpTm;

    char buf[30]={0};
    //snprintf(buf,sizeof(buf),"%d%02d%02d%02d%02d%02d",sTm->tm_year+1900,sTm->tm_mon+1,
    snprintf(buf,sizeof(buf),"%d%02d%02d",sTm->tm_year+1900,sTm->tm_mon+1,
    sTm->tm_mday);   
    fileName = std::string(buf);

    return fileName;
}


void getYYYYMMDDtime()
{
    time_t tStart = ::time(NULL);  
    struct tm tmpTm = *localtime(&tStart);
    struct tm* sTm = &tmpTm;
            
    char chTimeForm[20] = {0};
    snprintf(chTimeForm, sizeof(chTimeForm), "%d-%02d-%02d %02d:%02d:%02d",
            sTm->tm_year+1900, sTm->tm_mon+1, sTm->tm_mday, sTm->tm_hour, sTm->tm_min, sTm->tm_sec );    
    //snprintf(chTimeForm, sizeof(chTimeForm), "%d-%02d-%02d",
    //        sTm->tm_year+1900, sTm->tm_mon+1, sTm->tm_mday );    

    std::string logFileName = std::string("log/")+ GetTimeStringFileName(tStart)+ ".log";

	
	printf("%s\n ", logFileName.c_str());

}


int
main(int argc, char *argv[])
{
    //singnaltest( argc , argv);
    getYYYYMMDDtime();

}

