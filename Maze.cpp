#include <iostream>
#include <array>
#include <string>

using namespace std;
//General Variables
const int UP = 0, DOWN = 1, RIGHT = 2, LEFT = 3;
const int exit_x = 10, exit_y = 4;
const size_t array_size = 12;
string maze_string =
"############"
"#...#......#"
"..#.#.####.#"
"###.#....#.#"
"#....###.#.."
"####.#.#.#.#"
"#..#.#.#.#.#"
"##.#.#.#.#.#"
"#........#.#"
"######.###.#"
"#......#...#"
"############";

typedef array<array<char, array_size>, array_size> Maze;

//Void function to initialize the maze as an array
void setMaze(Maze &maze) {
	for (size_t i{ 0 }; i < maze.size(); ++i)
		for (size_t j{ 0 }; j < maze[i].size(); ++j) {
			maze[i][j] = maze_string[i*maze[i].size() + j];
		}
}
//Function to print the maze (array)
void printMaze(Maze &maze) {
	for (size_t i{ 0 }; i < maze.size(); ++i) {
		for (size_t j{ 0 }; j < maze[i].size(); ++j) {
			cout << maze[i][j] << "  ";
		}
		cout << endl;
	}
	
}

//Checks if the position at x and y is valid
bool validMove(Maze &maze, int x, int y)
{
	return maze[y][x] != '#';
}

bool solved = false;

//Checks if the maze has been solved and prints last X on exit
bool isSolved(Maze &maze, int x, int y) {
	if (y == exit_y && x == exit_x)
	{
		maze[4][11] = 'X';
		printMaze(maze);
		solved = true;
	}
	return solved;
}

//Traverse function that will print the current location in the maze, check if the maze has been solved, choose the validity of the next move
//and lastly, it will prioritize certain movements depending on the situation.
void mazeTraverse(Maze &maze, int x, int y, int direction) {
	maze[y][x] = 'X';
	printMaze(maze);
	cout << endl;
	if (isSolved(maze, x, y)) {
		return;
	}
//Recursive switch statements that will return the next position
	switch (direction) {
	case UP:
		if (maze[y - 1][x] != '#')
			mazeTraverse(maze, x, y - 1, direction);
		break;
	case DOWN:
		if (maze[y + 1][x] != '#')
			mazeTraverse(maze, x, y + 1, direction);
		break;
	case RIGHT:
		if (maze[y][x + 1] != '#')
			mazeTraverse(maze, x + 1, y, direction);
		break;
	case LEFT:
		if (maze[y][x - 1] != '#')
			mazeTraverse(maze, x - 1, y, direction);
		break;
	}

	if (isSolved(maze, x, y)) {
		return;
	}

//Recursive switch statements that will check the validity of the next move and prioritize which action to take
	switch (direction) {
	case RIGHT:
		if (validMove(maze, x, y + 1)) {
			mazeTraverse(maze, x, y + 1, DOWN);
		}
		else if (validMove(maze, x + 1, y)) {
			mazeTraverse(maze, x + 1, y, RIGHT);
		}
		else if (validMove(maze, x, y - 1)) {
			mazeTraverse(maze, x, y - 1, UP);
		}
		else if (validMove(maze, x - 1, y)) {
			mazeTraverse(maze, x - 1, y, LEFT);
		}
		break;
	
	case UP:
		if (validMove(maze, x + 1, y)) {
			mazeTraverse(maze, x + 1, y, RIGHT);
		}
		else if (validMove(maze, x, y - 1)) {
			mazeTraverse(maze, x, y - 1, UP);
		}
		else if (validMove(maze, x - 1, y)) {
			mazeTraverse(maze, x - 1, y, LEFT);
		}
		else if (validMove(maze, x, y + 1)) {
			mazeTraverse(maze, x, y + 1, DOWN);
		}
		break;
	case DOWN:
		if (validMove(maze, x - 1, y)) {
			mazeTraverse(maze, x - 1, y, LEFT);
		}
		else if (validMove(maze, x, y + 1)) {
			mazeTraverse(maze, x, y + 1, DOWN);
		}
		else if (validMove(maze, x + 1, y)) {
			mazeTraverse(maze, x + 1, y, RIGHT);
		}
		else if (validMove(maze, x, y - 1)) {
			mazeTraverse(maze, x, y - 1, UP);
		}
		break;
	case LEFT:
		if (validMove(maze, x, y - 1)) {
			mazeTraverse(maze, x, y - 1, UP);
		}
		else if (validMove(maze, x - 1, y)) {
			mazeTraverse(maze, x - 1, y, LEFT);
		}
		else if (validMove(maze, x, y + 1)) {
			mazeTraverse(maze, x, y + 1, DOWN);
		}
		else if (validMove(maze, x + 1, y)) {
			mazeTraverse(maze, x + 1, y, RIGHT);
		}
	}
}



//Main
int main()
{
	Maze maze;
	setMaze(maze);
	mazeTraverse(maze, 0, 2, RIGHT);
}