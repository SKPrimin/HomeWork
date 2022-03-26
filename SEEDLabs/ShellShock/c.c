#include <string.h>
#include <stdio.h>
#include <stdlib.h>
char **environ;
int main()
{
    char *argv[3];
    argv[0] = "/bin/ls";
    argv[1] = "-l";
    argv[2] = NULL;
    setuid(geteuid()); // make real uid = effective uid.
    execve(argv[0], argv, environ);
    return 0;
}