#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
	m_rows = nRows;
	m_cols = nCols;
	for (int r = 0; r < nRows; r++)
	{
		for (int c = 0; c < nCols; c++)
		{
			board[r][c] = 64;
		}
	}
}

bool History::record(int r, int c)
{
	if (r > m_rows || r < 1 || c > m_cols || c < 1)
		return false;
	board[r - 1][c - 1]++;
	return true;
}

void History::display() const
{
	int r;
	int c;

	clearScreen();
	for (r = 0; r < m_rows; r++)
	{
		for (c = 0; c < m_cols; c++)
		{
			if (board[r][c] == 64)
				cout << '.';
			else
				cout << board[r][c];
		}
		cout << endl;
	}
	cout << endl;
}