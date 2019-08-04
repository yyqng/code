#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <iostream>
#include "test-curl.h"
using namespace std;

//vim /etc/hosts  add:
//172.217.14.100 www.google.com
//Usage : ./curltest www.google.com
//Eqaul : curl -x socks5://userc:usercpasswd@45.78.30.207:10808 www.google.com
//linux : /etc/hosts   windows: C:\Windows\System32\drivers\etc\hosts ：
//172.217.14.100 www.google.com
//151.101.2.217 www.voxer.com  
int curlhttp(int argc, char *argv[])
//int main(int argc, char *argv[])
{
    CURL *curl; 
    if(argc!=2)
    {
        printf("Usage : ./test-curl <url>\n");
        exit(1);
    }

    curl = curl_easy_init(); 
    if(curl!=NULL)
    {
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);       

        //curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5); 
        //curl_easy_setopt(curl, CURLOPT_PROXY, "45.78.30.207:10808"); 
        //curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "userc:usercpasswd"); 

        //curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5_HOSTNAME); 
        //curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1"); 
        //curl_easy_setopt(curl, CURLOPT_PROXYPORT, "1080"); 

        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5_HOSTNAME); 
        curl_easy_setopt(curl, CURLOPT_PROXY, "107.172.86.48"); 
        curl_easy_setopt(curl, CURLOPT_PROXYPORT, "10808"); 
        curl_easy_setopt(curl, CURLOPT_PROXYPASSWORD , "thinkerthinkerthinker"); 
        //curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:7788"); 
        CURLcode res = curl_easy_perform(curl);
        long http_code = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
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

