main()
{
    int num = 0x41414141;

    printf("Before: num = %#x \n", num);
    printf("%.20d%hn\n", num, &num);
    printf("After: num = %#x \n", num);
}