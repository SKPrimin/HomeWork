#include <stdio.h>

typedef struct s
{
       int id;
       char name[20];
       void (*clean)(void *);
} VULNSTRUCT;

void *cleanMemory(void *mem)
{
       free(mem);
}
int main(int argc, char *argv[])
{
       void *ptr1;
       VULNSTRUCT *vuln = malloc(256);

       fflush(stdin);
       printf("Enter id num: ");
       scanf("%d", &vuln->id);
       printf("Enter your name: ");
       scanf("%s", vuln->name);

       vuln->clean = cleanMemory;

       if (vuln->id > 100)
       {
              vuln->clean(vuln);
       }

       ptr1 = malloc(256);
       strcpy(ptr1, argv[1]);

       free(ptr1);
       vuln->clean(vuln);

       return 0;
}
