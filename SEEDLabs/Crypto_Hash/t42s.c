#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>
#include <openssl/bn.h>
#include <time.h>

// Hash function collision test.
// gcc -o t42 t42s.c -fpermissive -lcrypto

#define threshold 24
#define TIMES 5
void generate(char *buffer)
{
    srand(clock());
    for (int i = 0; i < 512 / 8; i++)
    {
        buffer[i] = (unsigned char)(rand() % 255);
    }
}

int verify(char *origin, char *result)
{
    int len = threshold / 8;
    for (int i = 0; i < len; i++)
    {
        if ((unsigned int)origin[i] != (unsigned int)result[i])
            return 0;
    }
    return 1;
}

int main()
{

    EVP_MD_CTX *mdctx;
    const EVP_MD *md = EVP_get_digestbyname("md5");
    unsigned char *message, *director;

    message = (unsigned char *)malloc(512 / 16);
    director = (unsigned char *)malloc(512 / 16);

    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, i;

    unsigned int sum = 0;
    for (int round = 1; round <= TIMES; round++)
    {

        // random initializate a digest .
        printf("Round %d, target hash : \n", round);
        srand(clock());
        for (int i = 0; i < 16; i++)
        {
            director[i] = (unsigned char)(rand() % 255);
            printf("%02x", director[i]);
        }
        printf("\n");

        long int trials = 0;
        do
        {
            trials++;
            generate(message);
            mdctx = EVP_MD_CTX_new();
            EVP_DigestInit_ex(mdctx, md, NULL);
            EVP_DigestUpdate(mdctx, message, 512 / 8);
            EVP_DigestFinal_ex(mdctx, md_value, &md_len);
            EVP_MD_CTX_free(mdctx);
        } while (!verify(director, md_value));
        sum += trials;

        printf("find solution:\n");
        for (int i = 0; i < 16; i++)
            printf("%02x", md_value[i]);

        printf("\nRound %d takes %ld trials.\n", round, trials);
    }

    printf("Average trials : %f", (double)sum / TIMES);

    return 0;
}
