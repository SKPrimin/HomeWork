/*   task5.c   */
#include <stdio.h>
#include <stdlib.h>
#define LEN 32 //  256  bits

void main()
{

    int i;
    unsigned char *key = (unsigned char *)malloc(sizeof(unsigned char) * LEN);
    FILE *random = fopen("/dev/urandom", "r");
    for (i = 0; i < LEN; i++)
    {
        fread(key, sizeof(unsigned char) * LEN, 1, random);
        printf("%.2x", *key);
    }
    printf("\n");
    fclose(random);
}