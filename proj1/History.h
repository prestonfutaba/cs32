#ifndef HISTORY_H
#define HISTORY_H

#include "globals.h"
class History
{
public:
	//Constructor
	History(int nRows, int nCols);

	bool record(int r, int c);
	void display() const;

private:
	int m_rows;
	int m_cols;
	char board[MAXROWS][MAXCOLS];
};

#endif