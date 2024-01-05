#pragma once
#include "PathfinderInterface.h"
#include <sstream>
#include <fstream>
#include <cstdlib>
class Pathfinder :
	public PathfinderInterface
{
private:
	int maze[5][5][5] = { { { 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 1 }, { 1, 1, 1, 1, 1 } } };
	vector<string> path;
	const int CELL_MAX = 4;
public:
	Pathfinder();
	~Pathfinder();
	string getMaze();

	void createRandomMaze();
	
	bool importMaze(string file_name);

	bool findPath(int x, int y, int z);
	
	vector<string> solveMaze();
};

