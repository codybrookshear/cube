#include "PuzzleModel.h"
#include <stdio.h>
#include <string.h>



PuzzleModel::PuzzleModel()
{
}


PuzzleModel::~PuzzleModel()
{
}

bool PuzzleModel::findWord(char * word)
{
	for (int cube = 0; cube < NUM_CUBES; cube++)
	{
		// can the word be found starting from this cube?
		if (findWordStartingAtCube(word, cube))
			return true;
	}
	return false;
}

void PuzzleModel::load(char * cubeLine)
{
	strcpy(cubes, cubeLine);
	//printf("cubes: %s\n", cubes);
}

bool PuzzleModel::findWordStartingAtCube(char * word, int cube)
{
	// aka followWordPaths
	
	if (word[0] == cubes[cube])
	{
		//printf("find %s, ", word);
		pathManager.load(cubes);
		pathManager.startAt(cube);
	}
	else
	{
		return false;
	}
	
	size_t wordLen = strlen(word);

	for (int i = 1; i < wordLen; i++)
	{
		// see if we can reach word[i], starting at cube, in cubes
		char c = word[i];
		bool expanded = pathManager.expandPaths(c);
		if (!expanded)
			return false;
	}

	// if we made it here, every letter was expanded.
	return true;
}



