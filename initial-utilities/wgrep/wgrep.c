#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
char *term;
int lenterm ;

void exiterror(char *msg,int status)
	{
		puts(msg);
		exit(1);
	}
bool matchword(char *word)
{
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
	int lidx = 0;
	char word[strlen(line)];
	while(line[lidx] != '\0')
	{
		if(line[lidx] == ' '|| line[lidx] == '\t' || line[lidx] == '\n')
		{
			lidx++;
			word[cidx] = '\0';
			if(matchword(word) ) return true;
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
	FILE * file ; 
	if( strcmp("stdin",filename) ) // if filename != stdin 
		file = fopen(filename,"r");
	else 
		file = stdin;
	if(file == NULL) exiterror("wgrep: cannot open file",1);
	while((readl = getline(&line,&si,file)) != -1)
		if (processline(line))
			printf("%s",line);
	fclose(file);
}

int main(int argc,char **argv)
{
	if(argc <= 1) exiterror("wgrep: searchterm [file ...]" , 1);
	term    = argv[1];
	lenterm = strlen(term);
	if(argc == 2) read("stdin");
	else
	{
		for(int argitr=2;argitr<argc;argitr++)
			read(argv[argitr]);
	}
}
