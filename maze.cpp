/* 
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

int maze_search(char**, int, int);
bool checkDuplicate(Location, const int*, Location*);
bool addToExplored(Location, int*, Location*);
void backtracking(Location**, char**, Location, int);

int main(int argc, char* argv[]) {
    int rows, cols, result;
    int *r = &rows, *c = &cols;
    char** mymaze=NULL;

    if(argc < 2)
    {
       cout << "Please provide a maze input file" << endl;
       return 1;
    }

    mymaze = read_maze(argv[1], r, c);

    if (mymaze == NULL)
    {
      cout << "Error, input format incorrect." << endl;
      return 1;
    }

    result = maze_search(mymaze, rows, cols);

    // examine value returned by maze_search and print appropriate output
    if (result == 1)
    {
      print_maze(mymaze, rows, cols);
    }
    else if (result == 0)
    {
      cout << "No path could be found!" << endl;
    }
    else
    {
      cout << "Invalid maze." << endl;
    }

    // free up memory
    for(int i = 0; i < rows; i++)
    {
        delete[] mymaze[i];
    }
    delete[] mymaze;

    return 0;
}

// Finds the shortest path and returns:
// 1 if successful
// 0 if no path exists
//-1 if invalid maze (not exactly one S and one F)
// If path is found fills it in with '*' characters
int maze_search(char** maze, int rows, int cols) 
{
    Queue q(rows*cols);
    Location next;
    Location current;
    Location finish;
    Location *explored = new Location[rows*cols];
    Location **predecessor = new Location*[rows];
    int s = 0;
    int f = 0;

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
                s++;
            }
            if(maze[i][j] == 'F')
            {
                finish.row = i;
                finish.col = j;
                f++;
            }
        }
    }
    // check for valid starting and end positions
    if(s != 1 || f != 1)
    {
        return -1;
    }

    int exploredIndex = 1;
    int* size = &exploredIndex;
    // if no finish cell is found queue will keep removing from front until empty
    while(!q.is_empty())
    {
        current = q.remove_from_front();
        // north: -1 row
        // west: -1 col
        // south: +1 row
        // east: +1 col

        // north
        // when checking a position in the maze we must make sure it exists
        if(current.row - 1 >= 0)
        {
            next.row = current.row - 1;
            next.col = current.col;
            // Don't want walls apart of the path
            if(maze[next.row][next.col] != '#')
            {
                // false actually means it was added to explored
                if(!addToExplored(next, size, explored))
                {
                    q.add_to_back(next);
                    predecessor[next.row][next.col] = current;
                }
            }
            if(next.row == finish.row && next.col == finish.col)
            {
                break;
            }
        }
        // west
        if(current.col - 1 >= 0)
        {
            next.row = current.row;
            next.col = current.col - 1;
            if(maze[next.row][next.col] != '#')
            {
                if(!addToExplored(next, size, explored))
                {
                    q.add_to_back(next);
                    predecessor[next.row][next.col] = current;
                }
            }
            if(next.row == finish.row && next.col == finish.col)
            {
                break;
            }
        }
        // south
        if(current.row + 1 < rows)
        {
            next.row = current.row + 1;
            next.col = current.col;
            if(maze[next.row][next.col] != '#')
            {
                if(!addToExplored(next, size, explored))
                {
                    q.add_to_back(next);
                    predecessor[next.row][next.col] = current;
                }
            }
            if(next.row == finish.row && next.col == finish.col)
            {
                break;
            }
        }
        // east
        if(current.col + 1 < cols)
        {
            next.row = current.row;
            next.col = current.col + 1;
            if(maze[next.row][next.col] != '#')
            {
                if(!addToExplored(next, size, explored))
                {
                    q.add_to_back(next);
                    predecessor[next.row][next.col] = current;
                }
            }
            if(next.row == finish.row && next.col == finish.col)
            {
                break;
            }
        }
    }
    // the last explored location should be the finish cell
    Location valid = explored[exploredIndex - 1];
    if(valid.row != finish.row || valid.col != finish.col)
    {
        return 0;
    }
    backtracking(predecessor, maze, finish, *size);
    // free up memory
    delete[] explored;
    for(int i = 0; i < rows; i++)
    {
        delete[] predecessor[i];
    }
    delete[] predecessor;

    return 1;
}

bool addToExplored(Location next, int* size, Location* explored)
{
    bool add = checkDuplicate(next, size, explored);
    if(!add)
    {
        explored[*size] = next;
        (*size)++;
    }
    return add;
}

bool checkDuplicate(Location next, const int* size, Location *explored)
{
    bool duplicate = false;
    for(int i = 0; i < *size; i++)
    {
        Location temp = explored[i];
        if(temp.row == next.row && temp.col == next.col)
        {
            duplicate = true;
        }
    }
    return duplicate;
}

void backtracking(Location** predecessor, char** maze, Location finish, int size)
{
    // predecessor of the finish cell will tell us how to go back one step
    // then that cell's predecessor tells us how to go back another step
    Location back = finish;
    for(int i = 0; i < size; i++)
    {
        back = predecessor[back.row][back.col];
        if(maze[back.row][back.col] == 'S')
        {
            break;
        }
        else
        {
            maze[back.row][back.col] = '*';
        }
    }
}
