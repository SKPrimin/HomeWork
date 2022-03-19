//sidechannel.c
//s.pass rootÖ»¶Á
//S1deCh4nnelAttack3r

#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
       FILE *in = 0;
       char pass[20]="";
       unsigned int i=0, j=0;
       unsigned short correct=0,misplaced=0;
       unsigned short pwlen=strlen(pass) - 1, inlen=0;
       if(argc != 3 || (inlen=strlen(argv[1]) - 1) > 19)
               return 1;

       setresuid(geteuid(),geteuid(),geteuid());

       in = fopen("s.pass","r");
       pass[fread(pass, 1,19,in)] = 0;
       fclose(in);

       for (i = 0; i <= inlen && i <= pwlen; i++)
               if(pass[i] == argv[1][i])
                       correct++;
               else
                       for(j = 1; j < pwlen; j++)
                               if(argv[1][i] == pass[(i+j)%19])
                                       misplaced++;

       if(correct == 19)
               ((void (*)()) argv[2])();

       return 0;
}

