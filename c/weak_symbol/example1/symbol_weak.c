void alias_weak()
{
    printf("%s\n",__FUNCTION__);
}

//若不链接 strong.c 用 strong 的弱别名 alias_weak 代替 strong 。
//void strong() __attribute__ ((weak,alias("alias_weak")));  //这一包与下面的asm()一句是等效的。
int main()
{
    asm(".weak strong\n"
        ".set strong, alias_weak");
    strong();
    return 0;
}
