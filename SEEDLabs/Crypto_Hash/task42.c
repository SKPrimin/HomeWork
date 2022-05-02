#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <openssl/evp.h>
#include <time.h>
//生成随机字符串用到的字符
char strdict[] = "0123456789qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM!\"#$ % &'()*+, -./:;<=>?@[\\]^_`{|}~";
//生成随机字符串的函数
void generateString(unsigned char* gen_str, const unsigned int len)
{
    int dictlen = strlen(strdict);
    for (int i = 0; i < len; i++)
    {
        int randnumm = rand() % dictlen;
        gen_str[i] = strdict[randnumm];
    }
}

int main(int argc, char* argv[])
{

    EVP_MD_CTX* mdctx0, * mdctx1;
    const EVP_MD* md;
    unsigned char md_value0[EVP_MAX_MD_SIZE], md_value1[EVP_MAX_MD_SIZE];
    unsigned int md_len, count;
    float average = 0;
    const unsigned int len = 12;
    argv[1] = "md5";//使用md5算法
    unsigned char str1[len + 1] = { "\0" };//因为字符串末尾还需要一个\0作为结束标志，所以长度为len+1
    unsigned char str2[len + 1] = { "\0" };
    srand((unsigned int)time(NULL));//设置随机数种子
    for (int i = 0; i < 5; i++) //5次破解
    {
        count = 0;//尝试次数
        char hash_value0[7] = "1";//因为字符串末尾还需要一个\0作为结束标志，所以长度为7
        char hash_value1[7] = "0";
        while (strcmp(hash_value0, hash_value1))
        {
            generateString(str1, len);
            generateString(str2, len);
            if (strcmp((const char*)str1, (const char*)str2) == 0)
                continue;   //生成的两个随机字符串相等则重新生成
            if (argv[1] == NULL) {
                printf("Usage: mdtest digestname\n");
                exit(1);
            }

            md = EVP_get_digestbyname(argv[1]);
            if (md == NULL) {
                printf("Unknown message digest %s\n", argv[1]);
                exit(1);
            }
            //计算str1的哈希值
            mdctx0 = EVP_MD_CTX_new();
            EVP_DigestInit_ex2(mdctx0, md, NULL);
            EVP_DigestUpdate(mdctx0, str1, strlen((const char*)str1));
            EVP_DigestFinal_ex(mdctx0, md_value0, &md_len);
            EVP_MD_CTX_free(mdctx0);
            sprintf(hash_value0, "%02x%02x%02x", md_value0[0], md_value0[1], md_value0[2]);//只取前24位
            /*
            printf("Digest is: ");
            for (int i = 0; i < md_len; i++)
                printf("%02x", md_value0[i]);
            printf("\n");
            */
            //计算str2的哈希值
            mdctx1 = EVP_MD_CTX_new();
            EVP_DigestInit_ex2(mdctx1, md, NULL);
            EVP_DigestUpdate(mdctx1, str2, strlen((const char*)str2));
            EVP_DigestFinal_ex(mdctx1, md_value1, &md_len);
            EVP_MD_CTX_free(mdctx1);
            sprintf(hash_value1, "%02x%02x%02x", md_value1[0], md_value1[1], md_value1[2]);//只取前24位
            /*
            printf("Digest is: ");
            for (int i = 0; i < md_len; i++)
                printf("%02x", md_value1[i]);
            printf("\n");
            */
            count++;
        }
        printf("Number of attempts is :%d\n", count);
        average += count;
        //printf("str1 :%s\n", str1);
        //printf("str2 :%s\n", str2);
    }
    printf("The average number of attempts is:%f\n", average / 5);
    return 0;
}