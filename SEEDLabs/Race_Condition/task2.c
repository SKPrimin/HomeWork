#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
void no_perm(void)
{
	printf("no permission.\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char *argv[])
{
	char *fn = "/tmp/XYZ";
	char buffer[60];
	FILE *fp;
	long int i;
	long int rep = 0; // number of repetition
	struct stat inodes[2] = {0};

	rep = 50;
	/* get user input */
	scanf("%50s", buffer);
	for (i = 0; i < rep; ++i)
	{
		if (!access(fn, W_OK))
		{
			stat(fn, &inodes[i % 2]);
			if (i > 0)
			{
				if (inodes[0].st_ino != inodes[1].st_ino)
				{
					no_perm();
				}
			}
		}
		else
		{
			no_perm();
		}
	}
	fp = fopen(fn, "a+");
	fwrite("\n", sizeof(char), 1, fp);
	fwrite(buffer, sizeof(char), strlen(buffer), fp);
	fclose(fp);
}