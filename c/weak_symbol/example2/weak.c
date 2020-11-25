#include <stdio.h>
extern void symbol() __attribute__((weak));
void symbol()
{
    printf("%s.%s\n",__FILE__,__FUNCTION__);
}
int main()
{
    //asm(".weak symbol1\n\t .set symbol1, symbol222\n\t");
    symbol();
    return 0;
}
