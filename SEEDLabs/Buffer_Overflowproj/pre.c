#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>

void catcher(int a)
{
    setresuid(geteuid(), geteuid(), geteuid());
    printf("WIN!\n");
    system("/bin/sh");
    exit(0);
}

int main(int argc, char **argv)
{
    if (argc != 3 || !atoi(argv[2]))
        return 1;
    signal(SIGFPE, catcher);
    return atoi(argv[1]) / atoi(argv[2]);
}