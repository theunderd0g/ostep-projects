#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

FILE * out ; 
void exiterr(char *msg)
{
    puts(msg);
    exit(1);
}
void compressFile(char *filename);

int main(int argc,char **argv)
{
    if(argc == 1) 
       exiterr("wzip: file1 [file2 ...]");

    for(int argi = 1; argi < argc; ++argi)
        compressFile(argv[argi]);

}

void write(int freq , char lett)
{
    printf(">> %d %c\n",freq,lett);
    //fwrite(&freq,4,1,stdout);
    //fwrite(&lett,1,1,stdout);
    fwrite(&freq,4,1,out);
    fwrite(&lett,1,1,out);

}

void compressFile(char *filename)
{

    FILE * file = fopen(filename,"r");
    out =  fopen("bitest","wb");
    if(!file)
        exiterr("wzip : cannot open file");
    char charc,c;
    int  count = 0;
    bool first = true;
    while( (c = getc(file)) != EOF)
    {
        if (first)
        {
            charc = c;
            ++count;
            first = false;
        }
        else
        {
            if(c == charc) ++count;
            else
            {
                write(count,charc);
                count  = 1;
                charc  = c;
            }
        }
    }
    write(count,charc);
}

