#include <iostream>
#include <fstream>
#include "mazeio.h"

using namespace std;

// Reads the maze from the given filename into a 2D dynamically allocated array.
// Returns the pointer to that array.
// Returns NULL if there is a problem, opening the file or reading in the integer sizes.
char** read_maze(char* filename, int* rows, int* cols) 
{
    ifstream inputFile(filename);
    // check if file can be opened
    if(inputFile.fail())
    {
        return NULL;
    }
    inputFile >> *rows >> *cols;
    //check if file contains two integers
    if(inputFile.fail())
    {
        return NULL;
    }
    char** maze = new char*[*rows];
    for(int i = 0; i < (*rows); i++)
    {
        maze[i] = new char[*cols];
    }

    for(int i = 0; i < *rows; i++)
    {
        char path;
        for(int j = 0; j < *cols; j++)
        {
            inputFile >> path;
            // checks for valid maze
            if(path != '.' && path != 'S' && path != 'F' && path != '#')
            {
                return NULL;
            }
            maze[i][j] = path;
        }
    }
    return maze;
}


// Print the maze contents to the screen in the
void print_maze(char** maze, int rows, int cols) 
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            cout << maze[i][j];
        }
        cout << endl;
    }
}

