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

    // Base case: if the current position has already been visited or is a wall, return immediately
    if (maze[row][col] == '.' || maze[row][col] == '@') {
        return;
    }

    // Base case: if the current position is the ending point,
    // store the final direction and set foundEnd to true
    if (maze[row][col] == 'F') {
        finalDir = currDir;
        foundEnd = true;
        return;
    }

    // Mark the current position as visited with a dot (".")
    maze[row][col] = '.';

    // Recursively call the SolveMaze function for each of the four directions (up, down, left, and right)
    SolveMaze(row - 1, col, maze, rowSz, colSz, foundEnd, currDir + "U", finalDir); // N
    SolveMaze(row + 1, col, maze, rowSz, colSz, foundEnd, currDir + "D", finalDir); // S
    SolveMaze(row, col + 1, maze, rowSz, colSz, foundEnd, currDir + "R", finalDir); // E
    SolveMaze(row, col - 1, maze, rowSz, colSz, foundEnd, currDir + "L", finalDir); // W
}

int main() {
    // Open the maze file for reading
    ifstream mazeFile("maze.txt");

    // Make larger than required
    char maze[100][100];

    // Initialize the 2D array to store the maze
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++) {
            maze[i][j] = ' ';
        }

    int row = 0;
    int startRow, startCol;

    // Read the file line by line and initialize the maze
    string line;
    while (getline(mazeFile, line)) {
        cout << line << endl;
        for (int i = 0; i < (int) line.length(); i++) {
            // Fill the current row of the maze array with the characters from the current line
            maze[row][i] = line[i];

            if (maze[row][i] == 'S') {
                // If the starting point is found, store its coordinates and mark it as an empty space
                startRow = row;
                startCol = i;
                maze[row][i] = ' ';
            }
        }
        // Move to the next row of the maze array
        row++;
    }

    cout << "Start Position: (" << startRow << "," << startCol << ")" << endl;
    // Output the starting position to the console for visualization

    // figure out the number of rows and columns
    int rowSz = row;
    int colSz = line.length();

    bool foundEnd = false;

    string finaldir = "";
    string currDir = "";

    // Call the SolveMaze function to find the path from the starting point to the ending point
    SolveMaze(startRow, startCol, maze, rowSz, colSz, foundEnd, currDir, finaldir);

    // Output the final path to the console for visualization
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
