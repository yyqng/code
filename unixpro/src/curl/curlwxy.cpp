#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <iostream>
#include "test-curl.h"
using namespace std;

int curlwxy(int argc, char *argv[])
{
    CURL *curl; 
    FILE*outfile, *infile;
    if(argc!=1)
    {
        printf("Usage : ./curltest\n");
        exit(1);
    }

    curl = curl_easy_init(); 
    if(curl!=NULL)
    {
        outfile = fopen("out.curl", "w");
        infile  = fopen("in.curl", "ab+");
        struct curl_slist *headers=NULL;
        headers = curl_slist_append(headers, "Host: www.zzzz.com");
        headers = curl_slist_append(headers, "Connection: keep-alive");
        headers = curl_slist_append(headers, "Referer: http://www.zzzz.com/");

        //curl_easy_setopt(curl, CURLOPT_URL, "https://www.weiyun.com/webapp/json/weiyunQdisk/DiskDirBatchList?refer=chrome_windows&g_tk=695600420");       
        curl_easy_setopt(curl, CURLOPT_URL, "http://www.zzzz.com/cgi-sys/defaultwebpage.cgi");
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5); 
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, outfile);
        curl_easy_setopt(curl, CURLOPT_READDATA, infile);
        
        CURLcode res = curl_easy_perform(curl);
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
        fclose(outfile);
        fclose(infile);
        curl_easy_cleanup(curl);
        if (res != CURLE_OK || http_code != 200) 
        {
            //printf (", res = %s, http_code = %d", &res ,&http_code);
            cout << "res = " << res << ", http_code = " << http_code << endl;
        }
        return (res == CURLE_OK && http_code == 200);
    }
    return 0;
}

