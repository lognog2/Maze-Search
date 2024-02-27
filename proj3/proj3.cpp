#include <iostream>
#include "Stack.h"

using namespace std;
using namespace cop4530;

int bit(int val, int place);

int main()
{
    //first 2 values in file
    int inRows = 0, inCols = 0;
    cin >> inRows;
    cin >> inCols;
    const int numRows = inRows;
    const int numCols = inCols;
    //cout << "rows: " << numRows << ", cols: " << numCols;

    //puts next int in file on top of stack
    Stack<int> maze;
    do
    {
        cin >> ws;
        int hold;
        cin >> hold;
        maze.push(hold);
        //cout << " " << hold;

    } while (cin.peek() != EOF);
    maze.pop(); //remove extra 0 at end

    //last 4 of stack are start and goal coords (backwards in stack)
    const int goal_col = maze.top();
    maze.pop();
    const int goal_row = maze.top();
    maze.pop();
    const int start_col = maze.top();
    maze.pop();
    const int start_row = maze.top();
    maze.pop();
    
    //cout << "\nstart: " << "(" << start_row << ", " << start_col << ")\n";
    //cout << "goal: " << "(" << goal_row << ", " << goal_col << ")\n";
    //maze should be ordered in stack from bottom right on top, to top left on bottom

    //map maze to 2d array
    //allocate arrays
    int** mazecode = new int*[numRows];
    for(int i = 0; i < numRows; i++)
        mazecode[i] = new int[numCols];

    char** path = new char*[numRows];
    for(int i = 0; i < numRows; i++)
        path[i] = new char[numCols];

    //outer loop is row, inner is column
    //starts in bottom right, goes left then up to right side of next row
    for (int i = numRows - 1; i >= 0; i--)
    {
        for (int j = numCols - 1; j >= 0; j--)
        {
            mazecode[i][j] = maze.top();
            path[i][j] = ' ';
            maze.pop();
        }
    }

    //debugging
    /*for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            cout << mazecode[i][j] << " ";
            if (mazecode[i][j] < 10)
                cout << " ";
        }
        cout << endl;
    }*/

    //depth first search
    Stack<int> findRow;
    Stack<int> findCol;
    findRow.push(start_row);
    findCol.push(start_col);
    bool goalFound = false;
    //int repeats = 0;
    int x, y, spot;
    while (!findRow.empty() && !findCol.empty())
    {
        if (findRow.top() == goal_row && findCol.top() == goal_col)
        {
            goalFound = true;
            break;
        }
        x = findRow.top();
        y = findCol.top();
        spot = mazecode[x][y]; //value at current coord
        //cout << "coords: " << "(" << findRow.top() << ", " << findCol.top() << ")\n";
        //cout << "spot: " << spot << "\n";

        //check walls for opening
        bool opening = false;
        if (bit(spot, 1) == 0 && path[x-1][y] == ' ') //north
        {
            //cout << "found opening north\n";
            path[x][y] = '^';
            opening = true;
            findRow.push(x - 1);
            findCol.push(y);
        }
        else if (bit(spot, 2) == 0 && path[x][y+1] == ' ') //east
        {
            //cout << "found opening east\n";
            path[x][y] = '>';
            opening = true;
            findRow.push(x);
            findCol.push(y + 1);
        }
        else if (bit(spot, 4) == 0 && path[x+1][y] == ' ') //south
        {
            //cout << "found opening south\n";
            path[x][y] = 'V';
            opening = true;
            findRow.push(x + 1);
            findCol.push(y);
        }
        else if (bit(spot, 8) == 0 && path[x][y-1] == ' ') //west
        {
            //cout << "found opening west\n";
            path[x][y] = '<';
            opening = true;
            findRow.push(x);
            findCol.push(y - 1);
        }

        //backtrack: if no opening, go back a coordinate
        if (!opening)
        {
            //cout << "backtracking\n";
            path[x][y] = 'X';
            findRow.pop();
            findCol.pop();
        }
        //if (++repeats > 100) break;
    }

    if (goalFound)
    {
        //reverse order of find stacks and output
        Stack<int> outRow;
        Stack<int> outCol;
        int size = findRow.size();
        for (int i = 0; i < size; i++)
        {
            outRow.push(findRow.top());
            findRow.pop();
            outCol.push(findCol.top());
            findCol.pop();
        }
        while (!outRow.empty())
        {
            cout << "(" << outRow.top() << "," << outCol.top() << ")\n";
            outRow.pop();
            outCol.pop();
        }
        
    } else cout << "Could not find a route\n";

    path[start_row][start_col] = 'S';
    path[goal_row][goal_col] = 'F';
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            cout << path[i][j] << " ";
        }
        cout << endl;
    }

    //deallocate mazecode
    for(int i = 0; i < numRows; i++)
        delete[] mazecode[i];
    delete[] mazecode;

    for(int i = 0; i < numRows; i++)
        delete[] path[i];
    delete[] path;

    return (EXIT_SUCCESS);
} //end main

//finds a bit value of a decimal number. val is decimal and place (8, 4, 2, 1) is which bit to return
//complexity is O(1)
int bit(int val, int place)
{
    return ((val / place) % 2);
} //end bit