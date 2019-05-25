#include "libc.h"

void insertTest()
{
//make release will #define NDEBUG
//make : inserttest : exit(-1)
#undef NDEBUG // no use
#ifdef NDEBUG
    printf("Define NDEBUG\n");
#else
    printf("Not define NDEBUG\n");
#endif
    assert(NULL);
    printf("exit(0)\n");
}

void ctypeTest()
{
    printf("ispunct(\'1\'): %d\n",   ispunct('1') );
    printf("ispunct(\':\'): %d\n",   ispunct(':') );// ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~

    printf("isalnum(\'\\\'): %d\n",  isalnum('\\') );
    printf("isalnum(\'a\'): %d\n",   isalnum('a') );

    printf("isalpha(\'\\\'): %d\n",  isalpha('\\') );
    printf("isalpha(\'a\'): %d\n",   isalpha('a') );//ispunct || isalnum

    printf("isspace(\' \'): %d\n",   isspace(' ') );//'\t' '\n' '\v' '\f' '\r' ' '
    printf("isspace(\'\\n\'): %d\n", isspace('\n') );

    printf("isprint(\'\\a\'): %d\n", isprint('\a') );//ispunct || isalnum || isspace
    printf("isprint(\'a\'): %d\n",   isprint('a') );

    printf("iscntrl(\'\\n\'): %d\n", iscntrl('\n') );
    printf("iscntrl(\'a\'): %d\n",   iscntrl('a') );//000-037 177

    printf("isdigit(\'1\'): %d\n",   isdigit('1') );
    printf("isdigit(\'a\'): %d\n",   isdigit('a') );

    printf("islower(\'1\'): %d\n",   islower('A') );
    printf("islower(\'a\'): %d\n",   islower('a') );

    printf("isupper(\' \'): %d\n",   isupper(' ') );
    printf("isupper(\'A\'): %d\n",   isupper('A') );

    printf("isxdigit(\'A\'): %d\n",   isxdigit('A') );
    printf("isxdigit(\'a\'): %d\n",   isxdigit('a') );

    printf("toupper(\'1\'): %c\n",   toupper('1') );
    printf("toupper(\'a\'): %c\n",   toupper('a') );

    printf("tolower(\'1\'): %c\n",   tolower('1') );
    printf("tolower(\'a\'): %c\n",   tolower('a') );
}



void errnoTest()
{
    errno = ENOMSG;
    printf("errno = %d\n", errno);
    perror("failed");
    printf("falied: %s\n", strerror(errno));
}



void floatTest()
{
    printf("FLT_MAX = %.10e\n", FLT_MAX);
    printf("FLT_MIN = %.10e\n", FLT_MIN);
    printf("FLT_MANT_DIG = %d\n", FLT_MANT_DIG);
}


void limitsTest()
{
    printf("CHAR_BIT   = %d\n",  CHAR_BIT    );
    printf("SCHAR_MIN  = %d\n",  SCHAR_MIN   );
    printf("SCHAR_MAX  = %d\n",  SCHAR_MAX   );
    printf("UCHAR_MAX  = %d\n",  UCHAR_MAX   );
    printf("CHAR_MIN   = %d\n",  CHAR_MIN    );
    printf("CHAR_MAX   = %d\n",  CHAR_MAX    );
    printf("MB_LEN_MAX = %d\n",  MB_LEN_MAX  );
    printf("SHRT_MIN   = %d\n",  SHRT_MIN    );
    printf("SHRT_MAX   = %d\n",  SHRT_MAX    );
    printf("USHRT_MAX  = %d\n",  USHRT_MAX   );
    printf("INT_MIN    = %d\n",  INT_MIN     );
    printf("INT_MAX    = %d\n",  INT_MAX     );
    printf("UINT_MAX   = %d\n",  UINT_MAX    );
    printf("LONG_MIN   = %ld\n", LONG_MIN    );
    printf("LONG_MAX   = %ld\n", LONG_MAX    );
    printf("ULONG_MAX  = %lu\n", ULONG_MAX   );
}


void localeTest()
{
    time_t currtime;
    struct tm *timer;
    char buffer[80];

    time( &currtime );
    timer = localtime( &currtime );

    printf("Locale is: %s\n", setlocale(LC_ALL, "en_GB"));
    strftime(buffer,80,"%c", timer );
    printf("Date is: %s\n", buffer);


    printf("Locale is: %s\n", setlocale(LC_ALL, "de_DE"));
    strftime(buffer,80,"%c", timer );
    printf("Date is: %s\n", buffer);


    struct lconv * lc;

    setlocale(LC_MONETARY, "it_IT");
    lc = localeconv();
    printf("Local Currency Symbol: %s\n",lc->currency_symbol);
    printf("International Currency Symbol: %s\n",lc->int_curr_symbol);
 
    setlocale(LC_MONETARY, "en_US");
    lc = localeconv();
    printf("Local Currency Symbol: %s\n",lc->currency_symbol);
    printf("International Currency Symbol: %s\n",lc->int_curr_symbol);
 
    setlocale(LC_MONETARY, "en_GB");
    lc = localeconv();
    printf ("Local Currency Symbol: %s\n",lc->currency_symbol);
    printf ("International Currency Symbol: %s\n",lc->int_curr_symbol);
 
    printf("Decimal Point = %s\n", lc->decimal_point);


}



void mathTest()
{
    printf("acos( -1 )         = %f\n", acos( -1 ));
    printf(" cos( M_PI )       = %f\n",  cos( M_PI ));
    printf("asin( -1 )         = %f\n", asin( -1 ));
    printf(" sin( M_PI )       = %f\n",  sin( M_PI ));
    printf("atan( -1 )         = %f\n", atan( -1 ));
    printf(" tan( M_PI )       = %f\n",  tan( M_PI ));
    printf(" log( M_E )        = %f\n",  log( M_E ));
    printf(" log10( 10 )       = %f\n",  log10( 10 ));
    printf(" ceil( 10.5 )      = %f\n",  ceil( 10.5 ));
    printf(" floor( 10.5 )     = %f\n",  floor( 10.5 ));
    printf(" fmod( 10.5, 5.2 ) = %f\n",  fmod( 10.5, 5.2 ));
    printf(" pow( 4, 2.5 ) = %f\n",      pow( 4, 2.5 ));
}

jmp_buf jumpBuff;
void setjmpFuna()
{
    printf("Enter setjmpFuna()\n");
    setjmpFunb();
    printf("Leave setjmpFuna()\n");
}

void setjmpFunb()
{
    printf("Enter setjmpFunb()\n");
    setjmpFunc();
    printf("Leave setjmpFunb()\n");
}
void setjmpFunc()
{
    int setjmpRet = 2;
    printf("Enter setjmpFunc()\n");
    longjmp( jumpBuff, setjmpRet );
    printf("Leave setjmpFunc()\n");
}

void setjmpTest()
{
    printf("Enter setjmpTest()\n");
    int setjmpRet = 0;
    if( (setjmpRet = setjmp( jumpBuff )) ==0 )
    {
		printf("setjmpRet = %d\n", setjmpRet);
        setjmpFuna();
    }
	else
	{
		printf("setjmpRet = %d\n", setjmpRet);
	}
    printf("Leave setjmpTest()\n");
}

void sighandler(int signum)
{
    printf("Enter sighandler(),signum = %d \n", signum);
    exit(1);
}
void signalTest()
{
    sighandler_t ret = NULL;
    ret= signal(SIGINT, sighandler);
    if (ret == SIG_ERR)
        printf("signal(SIGINT, sighandler) return SIG_ERR.\n");

    ret = signal(SIGFPE, sighandler);
    if (ret == SIG_ERR)
        printf("signal(SIGFPE, sighandler) return SIG_ERR.\n");

    ret = signal(SIGABRT, sighandler);
    if (ret == SIG_ERR)
        printf("signal(SIGFPE, sighandler) return SIG_ERR.\n");

    printf("raise(SIGINT).\n");
    //int retrs = raise(SIGINT);
    //int retrs = raise(SIGFPE);
    int retrs = raise(SIGABRT);
    if (retrs != 0)
        printf("raise(SIGINT) ERROR.\n");

    while(1)
    {
        printf("Begin to sleep 1 s\n");
        sleep(1);
    }
    return ;
}



void stdargs(const char *s1, const char *s2, ...)
{
    char *str1 , *str2 , *str3;
    str1 = str2 = str3 = NULL;
    va_list valist;
    //Declare the last fixed parameter
    va_start(valist, s2);
    //Begin to read the parameters behind s2
    str1 = va_arg(valist, char*);
    str2 = va_arg(valist, char*);
    str3 = va_arg(valist, char*);
    va_end(valist);

    printf("Varied parameter:%s,%s,%s\n", str1, str2, str3);

}
void stdargsTest(int argc, char *argv[])
{
    if(argc < 4)
            return ;
    const char *s1 = "Fixed parameter";
    const char *s2 = "Fixed parameter";
    stdargs(s1, s2, argv[1], argv[2], argv[3]);
}


void stddefTest()
{
    struct address {
    char name[50];
    char street[50];
    int phone;
	};
    size_t offset = offsetof(struct address, name);
    printf("Offset of address.name    = %zu byte\n", offset );
    offset = offsetof(struct address, street);
    printf("Offset of address.street  = %zu byte\n", offset );
    offset = offsetof(struct address, phone);
    printf("Offset of address.phone   = %zu byte\n", offset );
	
}


void stdioTest()
{
}
