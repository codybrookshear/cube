#pragma once

#include "PathManager.h"

/*! number of cubies in the Puzzle. every line in a Puzzle file is this long */
//static const int NUM_CUBES = 64;

class PuzzleModel
{
public:
	PuzzleModel();
	~PuzzleModel();
	bool findWord(char* word);
	void load(char* cubeLine);
private:
	bool findWordStartingAtCube(char* word, int cube);
	bool expandPaths(char ch, int chIndex);

	char cubes[NUM_CUBES + 1];
	PathManager pathManager;
};

