#define MAX_LEN 256
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void foo(char *input)
{
	short len;
	char buffer[MAX_LEN];
	len = strlen(input);
	if (len < MAX_LEN)
		strcpy(buffer, input);
}

int main(int argc, char *argv[])
{

	if (argc != 2)
	{
		printf("Usage Error.\n");
		fflush(stdout);
		exit(-1);
	}
	foo(argv[1]);

	return 0;
}
