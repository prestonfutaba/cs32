#include <iostream>
#include <string>
#include <stack>

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
	stack<Coord> coordStack;

	coordStack.push(Coord(sr, sc));
	maze[sr][sc] = '-'; // updated maze with starting coord (sr,rc) to indicate algorithm encountered it

	while (!coordStack.empty()) // while stack is not empty
	{
		Coord current = coordStack.top(); 
		coordStack.pop(); //pop top coord off stack, our current coord
		
		int currRow = current.r(); // access the current coord at top of stack
		int currCol = current.c();
		//cout << "(" << currRow << ", " << currCol << ") ";

		if (currRow == er && currCol == ec) // check if current coord (first) is the end coord
			return true;

		if (maze[currRow + 1][currCol] == '.') // EAST
		{
			coordStack.push(Coord(currRow + 1, currCol)); // can move so push coord onto stack
			maze[currRow + 1][currCol] = '-'; // update maze index with - to indicate encounter with algorithm
		}

		if (maze[currRow][currCol - 1] == '.') // NORTH
		{
			coordStack.push(Coord(currRow, currCol - 1));
			maze[currRow][currCol - 1] = '-';
		}

		if (maze[currRow - 1][currCol] == '.') // WEST
		{
			coordStack.push(Coord(currRow - 1, currCol));
			maze[currRow - 1][currCol] = '-';
		}

		if (maze[currRow][currCol + 1] == '.') // SOUTH
		{
			coordStack.push(Coord(currRow, currCol + 1));
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
