#include "Pathfinder.h"


Pathfinder::Pathfinder()
{
}


Pathfinder::~Pathfinder()
{
}

string Pathfinder::getMaze()
{
	stringstream output;
	for (int i = 0; i < CELL_MAX; i++)
	{
		output << endl << endl; //may need to put if statements here
		for (int j = 0; j < CELL_MAX; j++)
		{
			output << endl;
			for (int k = 0; k < CELL_MAX; k++)
			{
				output << maze[i][j][k] << " ";
			}
		}
	}
	return output.str();
}

void Pathfinder::createRandomMaze()
{
	for (int i = 0; i < CELL_MAX; i++)
	{ 
		for (int j = 0; j < CELL_MAX; j++)
		{
			for (int k = 0; k < CELL_MAX; k++)
			{
				maze[i][j][k] = rand() % 2;
			}
		}
	}
	maze[0][0][0] = 1;
	maze[4][4][4] = 1; //to ensure an entrance and exit point
}

bool Pathfinder::importMaze(string file_name)
{
	stringstream ss;
	int input;
	vector<int> input_check;
	ifstream my_file;
	my_file.open(file_name);

	if (!my_file.is_open())
	{
		return false; //invalid file name
	}
	while (my_file >> input)
	{
		my_file >> input;
		input_check.push_back(input);
	}
	if ((input_check[0] != 1 && input_check[0] != 0) ||
		(input_check[input_check.size() - 1] != 1 && input_check[input_check.size() - 1] != 0) ||
		input_check.size() != 125) //may need to fix size
	{
		return false; //does not have correct parameters
	}

	my_file.close();
	my_file.open(file_name);

	for (int i = 0; i < CELL_MAX; i++)
	{
		for (int j = 0; j < CELL_MAX; j++)
		{
			for (int k = 0; k < CELL_MAX; k++)
			{
				my_file >> input;
				maze[i][j][k] = input;
			}
		}
	}
	return true;
}

//returns true if finds a valid path through maze, false if otherwise.
bool Pathfinder::findPath(int x, int y, int z)
{
	path.clear();
	if (x < 0 || y < 0 || z < 0 || x > CELL_MAX || y > CELL_MAX || z > CELL_MAX)
	{
		return false; //out of bounds
	}
	else if (maze[z][y][x] != 1)
	{
		return false; //blocked (0) or visited (2)
	}
	else if (z == CELL_MAX && y == CELL_MAX && x == CELL_MAX)
	{
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")"; //MIGHT need to change order here...
		path.push_back(ss.str());
		return true; //end of the maze
	}
	else
	{
		maze[z][y][x] = 2;
		if (findPath(x + 1, y, z) ||
			findPath(x - 1, y, z) ||
			findPath(x, y + 1, z) ||
			findPath(x, y - 1, z) ||
			findPath(x, y, z + 1) ||
			findPath(x, y, z - 1))
		{
			stringstream ss;
			ss << "(" << x << ", " << y << ", " << z << ")"; //MIGHT need to change order here...
			path.push_back(ss.str());
			return true; //move back up recursion
		}
		else
		{
			maze[z][y][x] = 2;
			return false; // Dead end
		}
	}
}

vector<string> Pathfinder::solveMaze()
{
	findPath(0, 0, 0); //starts at the first cell
	for (int i = 0; i < path.size() / 2; i++) //this will invert vector since the path will come out backwards from recursion
	{
		string temp;
		temp = path[path.size() - i];
		path[path.size() - i] = path[i];
		path[i] = temp;
	}
	return path;
}

