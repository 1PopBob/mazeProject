/* 
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);
bool checkDuplicate(Location, int*, Location*);
bool addToExplored(Location, int*, Location*);
void addToPredecessor();

// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result;
    int *r = &rows, *c = &cols;
    char** mymaze=NULL;

    if(argc < 2)
    {
       cout << "Please provide a maze input file" << endl;
       return 1;
    }

    mymaze = read_maze(argv[1], r, c);// <---TASK: COMPLETE THIS FOR CHECKPOINT 1

    if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
    }


     //================================
    // When working on Checkpoint 4, you will call maze_search here.
    // But for Checkpoint 1, just assume we found the path.

    result = maze_search(mymaze, rows, cols); // <--- TASK: CHANGE THIS FOR CHECKPOINT 4

    // examine value returned by maze_search and print appropriate output
    if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
    }
    else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
    }
    else { // result == -1
      cout << "Invalid maze." << endl;
    }

     //================================
    // ADD CODE BELOW
    // to delete all memory that read_maze allocated: CHECKPOINT 2
    for(int i = 0; i < rows; i++)
    {
        delete[] mymaze[i];
    }
    delete[] mymaze;

    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols) 
{
    // *** You complete **** CHECKPOINT 4
    Queue q(rows*cols);
    Location next;
    Location current;
    Location *explored = new Location[rows*cols];
    Location **predecessor = new Location*[rows];
    for(int i = 0; i < rows; i++)
    {
        predecessor[i] = new Location[cols];
    }

    // find starting position in maze
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            if(maze[i][j] == 'S')
            {
                next.row = i;
                next.col = j;
                q.add_to_back(next);
                explored[0] = next;
                break;
            }
        }
    }

    int exploredIndex = 1;
    int* size = &exploredIndex;
    while(!q.is_empty())
    {
        current = q.remove_from_front();
        // north: -1 row AND -1 col
        // west: -1 col
        // south: +1 row AND +1 col
        // east: +1 col

        if(current.row - 1 >= 0 && current.col - 1 >= 0)
        {
            next.row = current.row - 1;
            next.col = current.col - 1;
            addToExplored(next, size, explored);
            q.add_to_back(next);
        }
        if(current.col - 1 >= 0)
        {
            next.col = current.col - 1;
            addToExplored(next, size, explored);
            q.add_to_back(next);
        }
        if(current.row + 1 < rows && current.col + 1 < cols)
        {
            next.row = current.row + 1;
            next.col = current.col + 1;
            addToExplored(next, size, explored);
            q.add_to_back(next);
        }
        if(current.col + 1 < cols)
        {
            next.col = current.col + 1;
            addToExplored(next, size, explored);
            q.add_to_back(next);
        }
    }
    return 0;
}

bool addToExplored(Location next, int* size, Location* explored)
{
    bool add = checkDuplicate(next, size, explored);
    if(add)
    {
        explored[*size] = next;
        (*size)++;
    }
    return add;
}

bool checkDuplicate(Location next, int* size, Location *explored)
{
    bool duplicate = false;
    for(int i = 0; i <= *size; i++)
    {
        Location temp = explored[i];
        if(temp.row == next.row && temp.col == next.col)
        {
            duplicate = true;
        }
    }
    return duplicate;
}
