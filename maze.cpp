/* 
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
// #include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

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

    //cout << argv[1] << endl;

    mymaze = read_maze(argv[1], r, c);// <---TASK: COMPLETE THIS FOR CHECKPOINT 1

    if (mymaze == NULL) {
      cout << "Error, input format incorrect." << endl;
      return 1;
    }


     //================================
    // When working on Checkpoint 4, you will call maze_search here.
    // But for Checkpoint 1, just assume we found the path.

    result = 1; // <--- TASK: CHANGE THIS FOR CHECKPOINT 4


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
  
  
  
  
  
  
  
  return 0; // DELETE this stub, it's just for Checkpoint 1 to compile.
}
