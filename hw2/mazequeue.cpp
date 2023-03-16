#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Coord
{
public:
	Coord(int r, int c) : m_row(r), m_col(c) {}
	int r() const { return m_row; }
	int c() const { return m_col; }
private:
	int m_row;
	int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
	queue<Coord> coordQueue; // declare a queue of Coords

	coordQueue.push(Coord(sr, sc));
	maze[sr][sc] = '-'; // updated maze with starting coord (sr,rc) to indicate algorithm encountered it

	while (!coordQueue.empty()) // while queue is not empty
	{
		Coord current = coordQueue.front();
		coordQueue.pop(); //pop top coord off queue, our current coord

		int currRow = current.r(); // access the current coord at front of queue
		int currCol = current.c();
		//cout << "(" << currRow << ", " << currCol << ") ";

		if (currRow == er && currCol == ec) // check if current coord (first) is the end coord
			return true;

		if (maze[currRow + 1][currCol] == '.') // EAST
		{
			coordQueue.push(Coord(currRow + 1, currCol)); // can move so push coord onto queue
			maze[currRow + 1][currCol] = '-'; // update maze index with - to indicate encounter with algorithm
		}

		if (maze[currRow][currCol - 1] == '.') // NORTH
		{
			coordQueue.push(Coord(currRow, currCol - 1));
			maze[currRow][currCol - 1] = '-';
		}

		if (maze[currRow - 1][currCol] == '.') // WEST
		{
			coordQueue.push(Coord(currRow - 1, currCol));
			maze[currRow - 1][currCol] = '-';
		}

		if (maze[currRow][currCol + 1] == '.') // SOUTH
		{
			coordQueue.push(Coord(currRow, currCol + 1));
			maze[currRow][currCol + 1] = '-';
		}
	}

	return false;
}

int main()
{
	string maze[10] = {
		"XXXXXXXXXX",
		"X..X...X.X",
		"X.XXXX.X.X",
		"X.X.X..X.X",
		"X...X.XX.X",
		"XXX......X",
		"X.X.XXXX.X",
		"X.XXX....X",
		"X...X..X.X",
		"XXXXXXXXXX"
	};

	if (pathExists(maze, 10, 10, 5, 3, 8, 8))
		cout << "Solvable!" << endl;
	else
		cout << "Out of luck!" << endl;
}
