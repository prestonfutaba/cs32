bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {
    
    char traversed = '~';

    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = traversed;

    bool isDone = false;

    // South
    if (maze[sr + 1][sc] == '.') 
    {
        isDone = pathExists(maze, nRows, nCols, sr + 1, sc, er, ec);
    }
    // West
    if (!isDone && maze[sr][sc - 1] == '.')
    {
        isDone = pathExists(maze, nRows, nCols, sr, sc - 1, er, ec);
    }
    //North
    if (!isDone && maze[sr - 1][sc] == '.')
    {
        isDone = pathExists(maze, nRows, nCols, sr - 1, sc, er, ec);
    }
    // East
    if (!isDone && maze[sr][sc + 1] == '.')
    {
        isDone = pathExists(maze, nRows, nCols, sr, sc + 1, er, ec);
    }
    return isDone;
}
