#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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
FILE * file;
//void write(int freq , char lett)
//{
//    printf("\n>>%d %c\n", freq, lett);
//    printf("%c" , (char ) freq >> 8*3 );
//    printf("%c" , (char ) freq >> 8*2 );
//    printf("%c" , (char ) freq >> 8*1 );
//    printf("%c" , (char ) freq >> 8*0 );
//    printf("%c" , lett );
//}

void post(int freq, char lett)
{
    fwrite(&freq ,4,1,stdout );
    fwrite(&lett ,1,1,stdout );
}

void compressFile(char *filename)
{
    char curr , last = '\0' ;
    int  freq  = 0;
    bool first = true ;
    file = fopen(filename , "r");
    if( file == NULL ) exiterr("cannot open file");
    while( (curr = fgetc(file)) != EOF )
    {
        if ( first )
        {
            freq++;
            last = curr;
            first= false;
        }
        else
        {
            if (last == curr)
                freq++;
            else
            {
                post(freq, last);
                freq = 1;
                last = curr;
            }
        }
    }
    post(freq , last);
}

