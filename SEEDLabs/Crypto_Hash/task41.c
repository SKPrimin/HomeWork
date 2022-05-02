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

    EVP_MD_CTX* mdctx;
    const EVP_MD* md;
    argv[2] = "e59ff9";//根据需要自己编一个哈希值（24位，6个十六进制数）
    char *hash_value0 = argv[2];
    char hash_value1[7] = "0"; //因为字符串末尾还需要一个\0作为结束标志，所以长度为7
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len, count;
    float average = 0;
    const unsigned int len = 12;//生成的随机字符串的长度
    argv[1] = "md5";//使用md5算法
    unsigned char str[len+1] = { "0" }; //len+1原因同上
    srand((unsigned int)time(NULL));    //设置随机数种子
    for (int i = 0; i < 5; i++) //5次破解
    {
        char hash_value1[7] = "0";
        count = 0;  //尝试次数
        while (strcmp(hash_value0, hash_value1))
        {
            generateString(str, len);
            //printf("random str:%s\n", str);
            if (argv[1] == NULL) {
                printf("Usage: mdtest digestname\n");
                exit(1);
            }

            md = EVP_get_digestbyname(argv[1]);
            if (md == NULL) {
                printf("Unknown message digest %s\n", argv[1]);
                exit(1);
            }
            //计算哈希值
            mdctx = EVP_MD_CTX_new();
            EVP_DigestInit_ex2(mdctx, md, NULL);
            EVP_DigestUpdate(mdctx, str, strlen((const char*)str));
            EVP_DigestFinal_ex(mdctx, md_value, &md_len);
            EVP_MD_CTX_free(mdctx);
            sprintf(hash_value1, "%02x%02x%02x", md_value[0], md_value[1], md_value[2]);//只取前24位
            /*
            printf("Digest is: ");
            for (int i = 0; i < md_len; i++)
                printf("%02x", md_value[i]);
            printf("\n");
            */
            count++;
        }
        printf("Number of attempts is :%d\n", count);
        average += count;
        //printf("The resulting string is %s:\n", str);
    }
    printf("The average number of attempts is:%f\n", average / 5);
    return 0;
}
