#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

void exiterr(char *msg)
{
    puts(msg);
    exit(1);
}
void uncompressFile(char *filename);

int main(int argc,char **argv)
{
    if(argc == 1) 
       exiterr("wzip: file1 [file2 ...]");

    for(int argi = 1; argi < argc; ++argi)
        uncompressFile(argv[argi]);

}

void read(int *freq, char *lett,FILE * file)
{
    fread( freq , 4, 1, file);
    fread( lett , 1, 1, file);
}
void uncompressFile(char *filename)
{

    FILE * file = fopen(filename,"r");
    if(!file)
        exiterr("wzip : cannot open file");
    int  freq;
    char lett;
    bool eof = false;
    while( !eof )
    {
        read( &freq , &lett , file );
        printf("%d %c\n",freq,lett);
        if ( freq == EOF ) {eof = true; continue;}
        for(int count = 0;count < freq; ++count)
            printf("%c", lett);
    }
    
}

