/* stackesp.c */

/* This program has a buffer overflow vulnerability. */
/* Our task is to exploit this vulnerability */
/* sudo sysctl -w kernel.randomize_va_space=2 then use jmp esp or call esp(no nops) */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//use jmp esp or call esp
int someint = 0xe4ffd4ff;

int bof(char *str)
{
    char buffer[12];

    /* The following statement has a buffer overflow problem */
    strcpy(buffer, str);

    return 1;
}

int main(int argc, char **argv)
{
    char str[517];
    FILE *badfile;

    printf("%x\n", &someint);
    badfile = fopen("badfile", "r");
    fread(str, sizeof(char), 517, badfile);
    bof(str);

    printf("Returned Properly\n");
    return 1;
}