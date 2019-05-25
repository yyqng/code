#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include <pthread.h>
#include "test-curl.h"
using namespace std;
/***************************************************************************
 *                                  _   _ ____  _
 *  Project                     ___| | | |  _ \| |
 *                             / __| | | | |_) | |
 *                            | (__| |_| |  _ <| |___
 *                             \___|\___/|_| \_\_____|
 *
 * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
 *
 * This software is licensed as described in the file COPYING, which
 * you should have received as part of this distribution. The terms
 * are also available at https://curl.haxx.se/docs/copyright.html.
 *
 * You may opt to use, copy, modify, merge, publish, distribute and/or sell
 * copies of the Software, and permit persons to whom the Software is
 * furnished to do so, under the terms of the COPYING file.
 *
 * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
 * KIND, either express or implied.
 *
 ***************************************************************************/
/* <DESC>
 * An example of curl_easy_send() and curl_easy_recv() usage.
 * </DESC>
 */
 
 
 
curl_socket_t sockfd; /* socket */
CURL * curl ;

/* Auxiliary function that waits on the socket. */
static int wait_on_socket(curl_socket_t sockfd, int for_recv, long timeout_ms)
{
	struct timeval tv;
	fd_set infd, outfd, errfd;
	int ret;
 
	tv.tv_sec = timeout_ms / 1000;
	tv.tv_usec= (timeout_ms % 1000) * 1000;
 
	FD_ZERO(&infd);
	FD_ZERO(&outfd);
	FD_ZERO(&errfd);
 
	FD_SET(sockfd, &errfd); /* always check for error */
 
	if(for_recv)
	{
		FD_SET(sockfd, &infd);
	}
	else
	{
		FD_SET(sockfd, &outfd);
	}
 
	/* select() returns the number of signalled sockets or -1 */
	ret = select(sockfd + 1, &infd, &outfd, &errfd, &tv);
	return ret;
}


void *test_recv(void *)
{
	size_t iolen;
	curl_off_t nread;
	puts("Reading response.");
 
    CURLcode res;
	/* read the response */
	for(;;)
	{
		char buf[1024] = {0};
		wait_on_socket(sockfd, 1, 60000L);
		res = curl_easy_recv(curl, buf, 1024, &iolen);
 
		if(CURLE_OK != res)
		break;
 
		nread = (curl_off_t)iolen;
 
		printf("%s\n", buf);
		printf("Received %" CURL_FORMAT_CURL_OFF_T " bytes.\n", nread);
	}
    return NULL;
}
 
int curltcp(int argc, char *argv[])
//int main(int argc, char *argv[])
{
	long sockextr;
	size_t iolen;
	//curl_off_t nread;
 
	/* A general note of caution here: if you're using curl_easy_recv() or
	curl_easy_send() to implement HTTP or _any_ other protocol libcurl
	supports "natively", you're doing it wrong and you should stop.
	This example uses HTTP only to show how to use this API, it does not
	suggest that writing an application doing this is sensible.
	*/
 
	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, "183.61.185.86");
		curl_easy_setopt(curl, CURLOPT_PORT, 110);
		/* Do not do the transfer - only connect to host */
		curl_easy_setopt(curl, CURLOPT_CONNECT_ONLY, 1L);
		CURLcode res = curl_easy_perform(curl);
 
		if(CURLE_OK != res)
		{
			printf("Error: %s\n", strerror(res));
			return 1;
		}
 
		/* Extract the socket from the curl handle - we'll need it for waiting.
		* Note that this API takes a pointer to a 'long' while we use
		* curl_socket_t for sockets otherwise.
		*/
		res = curl_easy_getinfo(curl, CURLINFO_LASTSOCKET, &sockextr);
 
		if(CURLE_OK != res)
		{
			printf("Error: %s\n", curl_easy_strerror(res));
			return 1;
		}
 
		sockfd = (curl_socket_t)sockextr;
 
		/* wait for the socket to become ready for sending */
		if(!wait_on_socket(sockfd, 0, 60000L))
		{
			printf("Error: timeout.\n");
			return 1;
		}
 
		pthread_t thread_recv_id;
		pthread_create ( &thread_recv_id, NULL , test_recv , NULL );
        sleep(2);
 
        /* Minimalistic http request */
        //const char *request = "GET / HTTP/1.0\r\nHost: example.com\r\n\r\n";
        int const reqnumber = 5;
        const char request[reqnumber][128] = 
                { {"CAPA\r\n"} , {"USER yaya99001\r\n"} , 
                {"PASS benben123456\r\n"} , {"STAT\r\n"}, {"UIDL\r\n"} };
		puts("Sending request.");
		/* Send the request. Real applications should check the iolen
		* to see if all the request has been sent */
        for(int i=0; i<reqnumber; ++i)
        {
            const char *p = request[i];
            res = curl_easy_send(curl, p , strlen(p), &iolen);
            if(CURLE_OK != res)
            {
                printf("Error: %s\n", curl_easy_strerror(res));
                return 1;
            }

            sleep(2);
		    //pthread_t thread_recv_id;
		    //pthread_create ( &thread_recv_id, NULL , test_recv , NULL );

            size_t iolen = 0;
            curl_off_t nread;
            puts("Reading response.");
         
            char buf[1024] = {0};
            curl_easy_recv(curl, buf, 1024, &iolen);
            //CURLcode res = curl_easy_recv(curl, buf, 1024, &iolen);
            //if(CURLE_OK != res)
            //{
            //    printf("Error: %s\n", curl_easy_strerror(res));
            //    return 1;
            //}
 
            nread = (curl_off_t)iolen;
            printf("%s\n", buf);
            printf("Received %" CURL_FORMAT_CURL_OFF_T " bytes.\n", nread);
        }
 
		/* always cleanup */
		curl_easy_cleanup(curl);
	}
	return 0;
}


int socks5_curl(int argc, char *argv[])
{
    CURL *curl; 
    if(argc!=2)
    {
        printf("Usage : ./curltest <url>\n");
        exit(1);
    }

    curl = curl_easy_init(); 
    if(curl!=NULL)
    {
        //curl -x socks5://userc:usercpasswd@45.78.30.207:10808 www.google.com
        curl_easy_setopt(curl, CURLOPT_URL, argv[1]);       
        curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5); 
        
        curl_easy_setopt(curl, CURLOPT_PROXY, "45.78.30.207:10808"); 
        curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "userc:usercpasswd"); 
        
        //curl_easy_setopt(curl, CURLOPT_PROXY, "172.245.156.202:10808"); 
        //curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, "test:test"); 
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
 
