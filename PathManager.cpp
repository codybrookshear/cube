#include "PathManager.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

PathManager::PathManager()
{
}

PathManager::~PathManager()
{
}

void PathManager::load(char * cubeLine)
{
	strcpy(cubes, cubeLine);
}

bool PathManager::expandPaths(char c)
{
	// mark valid = false as we go if path not valid.
	bool expandedOneOrMore = false;

	for (int p = 0; p < ARBITRARY_NUM_PATHS; p++)
	{
		if (paths[p].valid && !paths[p].newPath)
		{
			if (expandPath(p, c))
				expandedOneOrMore = true;
		}
	}

	head++;
	expireNewPaths();
	//printValidPaths();
	return expandedOneOrMore;
}

void PathManager::printValidPaths()
{
	for (int i = 0; i < ARBITRARY_NUM_PATHS; i++)
	{
		if (paths[i].valid)
		{
			printf("path[%d]: ", i);
			for (int j = 0; j < head; j++)
			{
				printf("%d, ", paths[i].list[j]);
			}
			printf("\n");

		}
	}
}

void PathManager::expireNewPaths()
{
	for (int p = 0; p < ARBITRARY_NUM_PATHS; p++)
	{
		paths[p].newPath = false;
	}

}

bool PathManager::expandPath(int p, char c)
{

	bool firstTime = true;

	// get a pointer to our current path to be expanded
	Path *pathPtr = &paths[p];

	// assume it's invalid, until proven valid
	pathPtr->valid = false;

	// t = the index of the cube at the end of this path
	int t = pathPtr->list[head];

	// touchPtr = list of other cubes this cube touches
	TouchList *touchPtr = &(touches[t]);

	Path *dupPathPtr = NULL;

	int cubeVal;

	for (int i = 0; i < MAX_TOUCHES; i++)
	{
		if (touchPtr->list[i] == BK)
			break;

		cubeVal = cubes[touchPtr->list[i]];
		if (cubeVal == c)
		{
			// TODO match. add it to this "firstTime" list, or expand into a new valid one.

			if (!pathPtr->valid)
			{
				//printf("expand existing path[%d] \n", p);
				pathPtr->list[head + 1] = touchPtr->list[i];
				pathPtr->valid = true;
			}
			else
			{
				int newPath = duplicatePath(pathPtr);
				dupPathPtr = &paths[newPath];
				//printf("expand new path[%d] \n", newPath);
				dupPathPtr->list[head + 1] = touchPtr->list[i];
				dupPathPtr->valid = true;
				dupPathPtr->newPath = true;
			}
		}
	}

	//head++;
	return pathPtr->valid;
}

int PathManager::duplicatePath(Path* pathPtr)
{
	int newPath = getFirstInvalidPath();

	if (newPath <= 0)
		return newPath;

	// copy contents
	for (int i = 0; i <= head; i++)
	{
		paths[newPath].list[i] = pathPtr->list[i];
	}

	return newPath;
}

int PathManager::getFirstInvalidPath()
{
	for (int i = 0; i < ARBITRARY_NUM_PATHS; i++)
	{
		if (!paths[i].valid) 
		{
			//printf("getFirstInvalidPath %d\n", i);
			return i;
		}
	}

	assert(false);  // should never run out of paths!
	return -1;
}

void PathManager::startAt(int cube)
{
	//printf("starting at cube %d\n", cube);
	erasePaths();
	head = 0;
	paths[0].list[0] = cube;
	paths[0].valid = true;
}

void PathManager::erasePaths()
{
	for (int i = 0; i < ARBITRARY_NUM_PATHS; i++)
	{
		paths[i].valid = false;
	}
}

