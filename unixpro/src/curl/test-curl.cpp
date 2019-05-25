#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <iostream>
#include "test-curl.h"
using namespace std;

int main(int argc, char *argv[])
{
    //curltcp( argc, argv);
    curlhttp( argc, argv);
    //curlwxy( argc, argv);
    return 0;
}

