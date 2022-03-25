#include <stdio.h>
#include <stdlib.h>
int main()
{
    char *shell = (char *)getenv("MYID");
    if (shell)
    {
        printf("Value: %s\n", shell);
        printf("Address: %x\n", (unsigned int)shell);
    }
    char *shell2 = (char *)getenv("MYSHELL");
    if (shell2)
    {
        printf("Value: %s\n", shell2);
        printf("Address: %x\n", (unsigned int)shell2);
    }
    return 1;
}