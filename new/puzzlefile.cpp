#include "puzzlefile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//  char *fileBuf;
//  char *fileBufSize;
//  char *line;

void PuzzleFile::loadFile(char *filename)
{
    // copy the wordFile into memory to make sure we don't waste
    // time reading from disk repeatedly

    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);  //same as rewind(f);
    
    buf = (char*)malloc(fsize + 1);
    size_t bytesRead = fread(buf, fsize, 1, f);
    fclose(f);

    buf[fsize] = 0;
    
    printf("%s\n", buf);

    // convert all newlines to null chars
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if (buf[i] == '\n')
            buf[i] = '\0';
    }

    line = buf;

    printf("%s\n", line);
    //while (*line)
    //{
    //    printf("%s\n", getNext());
    //}
}

char* PuzzleFile::getNext()
{
    //line = line + strlen(line);
    //char *nextLine = strchr(line, '\0');

    // keep moving the pointer forward as long as it's not null
    while (*line)
	++line;

    if (line >= &(buf[fsize-1]))
	line = 0;
    else
	++line;

    return line;
}
  
char* PuzzleFile::getFirst()
{
    line = buf;
    return line;
}

char* PuzzleFile::getCurrent()
{
    return line;
}

PuzzleFile::~PuzzleFile()
{
   free(buf);
}
