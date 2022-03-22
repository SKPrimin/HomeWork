/* overfun.c */

/* This program has a buffer overflow vulnerability. */
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int good(int addr)
{
    printf("Address of hmm: %p\n", addr);
}

int hmm()
{
    printf("Win.\n");
    setuid(geteuid());
    execl("/bin/sh", "sh", NULL);
}

extern char **environ;

int main(int argc, char **argv)
{

    int i, limit;

    for (i = 0; environ[i] != NULL; i++)
        memset(environ[i], 0x00, strlen(environ[i]));

    int (*fptr)(int) = good;
    char buf[32];

    strcpy(buf, argv[1]);

    int (*hmmptr)(int) = hmm;

    (*fptr)((int)hmmptr);

    return 0;
}