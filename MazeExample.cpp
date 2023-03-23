#include <iostream>
#include <fstream>
#include <ostream>
#include <string>

using namespace std;

/*
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@S@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@       @                     @         @     @             @         @
@ @@@ @ @ @@@@@@@ @@@@@ @@@@@ @ @@@@@@@@@ @ @@@ @ @@@ @@@@@@@ @@@@@ @@@
@   @ @ @ @     @ @   @     @   @         @     @   @ @       @   @   @
@ @@@ @ @@@ @@@ @ @ @ @@@@@ @@@@@ @@@@@@@@@@@@@@@ @ @ @ @@@@@@@@@ @@@ @
@ @   @     @   @ @ @       @             @     @ @ @ @   @     @   @ @
@@@ @@@@@@@@@ @@@@@ @@@@@@@@@ @@@@@@@@@@@@@ @@@ @ @ @@@@@ @@@ @ @ @ @ @
@ @       @ @ @     @       @   @   @       @ @ @ @           @   @ @ @
@ @@@@@@@ @ @ @@@ @@@ @@@@@ @@@ @ @ @ @@@@@@@ @ @@@@@@@ @@@@@@@@@@@@@ @
@       @ @ @   @         @     @ @   @   @     @     @ @     @   @   @
@@@@@@@ @ @ @@@ @@@@@@@@@@@@@@@@@ @@@@@ @@@ @@@@@ @@@ @@@ @@@ @ @ @ @ @
@         @                       @               @       @     @   @ @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@F@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/


void
SolveMaze(int row, int col, char maze[][100], int rowSz, int colSz, bool &foundEnd, string currDir, string &finalDir) {
    // Recursive function to find a path from the starting point to the ending point in the maze.
    // Arguments:
    // row, col: the current row and column of the algorithm
    // maze: the 2D array representing the maze
    // rowSz, colSz: the number of rows and columns in the maze
    // foundEnd: a reference to a boolean variable that indicates whether the ending point has been found
    // currDir: a string representing the current direction the algorithm is moving in
    // finalDir: a reference to a string that will store the final path from the starting point to the ending point

    // Base case: if the ending point has been found, return immediately
    if (foundEnd) {
        return;
    }

    // Base case: if the current position is out of bounds, return immediately
    if (row < 0 || col < 0 || row >= rowSz || col >= colSz) {
        return;
    }

    if (maze[row][col] == '.' || maze[row][col] == '@') {
        return;
    }

    if (maze[row][col] == 'F') {
        finalDir = currDir;
        foundEnd = true;
        return;
    }

    maze[row][col] = '.';
    SolveMaze(row - 1, col, maze, rowSz, colSz, foundEnd, currDir + "U", finalDir); // N
    SolveMaze(row + 1, col, maze, rowSz, colSz, foundEnd, currDir + "D", finalDir); // S
    SolveMaze(row, col + 1, maze, rowSz, colSz, foundEnd, currDir + "R", finalDir); // E
    SolveMaze(row, col - 1, maze, rowSz, colSz, foundEnd, currDir + "L", finalDir); // W
}

int main() {
    ifstream mazeFile("maze.txt");
    char maze[100][100]; // make larger than required

    // Initialize the maze
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++) {
            maze[i][j] = ' ';
        }

    int row = 0;
    int startRow, startCol;

    // Read the file line by line an initialize the maze
    string line;
    while (getline(mazeFile, line)) {
        cout << line << endl;
        for (int i = 0; i < (int) line.length(); i++) {
            maze[row][i] = line[i];
            if (maze[row][i] == 'S') {
                startRow = row;
                startCol = i;
                maze[row][i] = ' ';
            }
        }
        row++;
    }

    cout << "Start Position: (" << startRow << "," << startCol << ")" << endl;

    // figure out the number of rows and columns
    int rowSz = row;
    int colSz = line.length();

    bool foundEnd = false;

    string finaldir = "";
    string currDir = "";
    SolveMaze(startRow, startCol, maze, rowSz, colSz, foundEnd, currDir, finaldir);

    cout << "Directions: " << finaldir << endl;

    // Print out the maze with the path shown
    for (int i = 0; i < rowSz; i++) {
        for (int j = 0; j < colSz; j++) {
            cout << maze[i][j];
        }
        cout << endl;
    }

    return 0;
}
