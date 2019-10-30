#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void ierror(char *msg)
{
	puts(msg);
	exit(1);
}


int main(int argc,char **argv)
{

	FILE * fileptr;
	char c;
	for(int idx=1;idx<argc;++idx)
	{
   		fileptr = fopen(argv[idx],"r");	
		if(fileptr == NULL) ierror("wcat: cannot open file");
		c = getc(fileptr);
		while(c != EOF)
		{
			printf("%c",c);
			c = getc(fileptr);
		}
		fclose(fileptr);
	}
}
