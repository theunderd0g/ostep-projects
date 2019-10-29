#include <stdio.h>
#include <string.h>
#include <stdbool.h>
char *term;
int lenterm ;

void exiterror(char *msg,int status)
	{
		puts(msg);
	}
bool matchword(char *word)
{
	/*puts(word);*/
	int wordidx = 0;
	int termidx = 0;
	while(term[termidx] != '\0')
		if(word[wordidx++] != term[termidx++])
			return false;
	return true;
}

bool processline(char * line)
{
	int cidx = 0;
	char lidx = 0;
	char word[strlen(line)];
	/*puts("as");*/
	while(line[lidx] != '\0')
	{
		/*printf("->%c\n" ,line[lidx]);*/
		if(line[lidx] == ' '|| line[lidx] == '\n')
		{
			lidx++;
			word[cidx] = '\0';
			if(matchword(word)) return true;
			cidx = 0;
		}
		else
			word[cidx++] = line[lidx++];
	}
	return matchword(word);
}
void read(char * filename)
{
	char *line;
	size_t  si = 0;
	ssize_t readl;
	FILE * file = fopen(filename,"r");
	if(file == NULL) exiterror("couldn't open file",1);
	while((readl = getline(&line,&si,file)) != -1)
		if (processline(line))
			puts(line);
		

	fclose(file);
}



int main(int argc,char **argv)
{
	lenterm = strlen(argv[1]);
	term    = argv[1];
	if(argc == 1) exiterror("wgrep [files..]" , 1);
	if(argc == 2) read("stdin");
	else
	{
		for(int argitr=2;argitr<argc;argitr++)
			read(argv[argitr]);
	}
	



}
