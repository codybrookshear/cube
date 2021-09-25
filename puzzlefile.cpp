#include "puzzlefile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void PuzzleFile::loadFile(char *filename)
{
    // copy the wordFile into memory to make sure we don't waste
    // time reading from disk repeatedly

    FILE *f = fopen(filename, "rb");
    fseek(f, 0, SEEK_END);
    fsize = ftell(f);
    fseek(f, 0, SEEK_SET);
    
    buf = (char*)malloc(fsize + 1);
    size_t bytesRead = fread(buf, fsize, 1, f);
    fclose(f);
    assert(bytesRead == 1);


    buf[fsize] = 0;

    // convert all newlines to null chars
    for (int i = 0; buf[i] != '\0'; i++)
    {
        if ((buf[i] == '\r') || (buf[i] == '\n'))
            buf[i] = '\0';
    }

	curPos = 0;
    line = buf;
}

char* PuzzleFile::getNext()
{
    // keep moving the pointer forward as long as it's not null
	while (*line)
	{
		++line;
		++curPos;
		if (curPos >= fsize)
		{
			line[0] = '\0';  // end of file reached. set to null.
		}
	}
	while ((curPos <= fsize) && !(*line))
	{
		++line; // go past 2nd null
		++curPos;
	}

	if (curPos >= fsize)
	{
		line[0] = '\0';  // end of file reached. set to null.
	}

    return line;
}
  
char* PuzzleFile::getFirst()
{
	curPos = 0;
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
