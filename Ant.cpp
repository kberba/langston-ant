/*********************************************************************
** Author: Karen Berba
** Date: 1/13/19
** Description:

Ant.cpp

Ant Class:
The Ant class keeps track of the ant's location (x and y coordinates) and
direction (N, E, S, W), as well as contains the function to move the ant on
the board. The Ant class also builds the board using a dynamic 2D
array, and contains board functions to display and initialize the board.


*********************************************************************/

#include "Ant.hpp"
#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;

/*********************************************************************
**
SETTERS

Description:
Setters for xCoord, yCoord, color, rowSize, and columnSize.

Arguments:
x-coordinate integer, y-coordinate integer, row integer, column integer,
space color character, row size integer, and column size integer.

Restrictions:
Only integers except for setColor, which needs two integer values for row and
column, and a character for space color.

Returns:
Does not return anything.


*********************************************************************/
void Ant::setXCoord(int xc) {
  xCoord = xc;
}

void Ant::setYCoord(int yc) {
  yCoord = yc;
}

void Ant::setColor(int r, int c, char spaceColor) {
  matrix[r][c] = spaceColor;
  color = matrix[r][c];
}

void Ant::setRows(int r) {
  rowSize = r;
}

void Ant::setColumns(int c) {
  columnSize = c;
}


/*********************************************************************
**
GETTERS

Description:
Getters for antSign, xCoord, yCoord, color, rowSize, columnSize, antDirection,
and matrix.


Arguments:
No arguments for all except getColor, which takes in two integers for row and column.

Restrictions:
Only restrictions are for getColor, which must be integers.

Returns:
Returns antSign, xCoord, yCoord, color, rowSize, columnSize, antDirection,
and matrix.


*********************************************************************/
char Ant::getAntSign() {
  return antSign;
}

int Ant::getXCoord() {
  return xCoord;
}

int Ant::getYCoord() {
  return yCoord;
}

char Ant::getColor(int r, int c) {
  color = matrix[r][c];
  return color;
}

int Ant::getRows() {
  return rowSize;
}

int Ant::getColumns() {
  return columnSize;
}

Direction Ant::getAntDirection() {
  return antDirection;
}

char** Ant::getBoard() {
  return matrix;
}


/*********************************************************************
**
CONSTRUCTOR
Ant::Ant(int x, int y, int rows, int columns)

Description:
Creates an Ant object. Dynamically allocates memory space for the board (matrix).
Sets the ant's starting coordinates, sign, and initial direction.

Arguments:
x-coordinate, y-coordinate, number of rows, number of columns.

Restrictions:
Only takes in integers.

Returns:
Does not return anything.


*********************************************************************/
Ant::Ant(int x, int y, int rows, int columns) {
  // set rows and columns
  rowSize = rows;
  columnSize = columns;

  // dynamically allocating 2D array
  /* source(s):

  https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

  */
  matrix = new char*[rowSize];  // rows
  for (int i = 0; i < rowSize; i++) {
    matrix[i] = new char[columnSize]; // columns
  }

  // fill the initial board with white spaces
  initialBoard(rowSize, columnSize);

  // set ant's starting coordinates
  setXCoord(x);
  setYCoord(y);

  // ant's character sign
  antSign = '*';

  // set ant's initial direction
  antDirection = NORTH;

}


/*********************************************************************
**
void Ant::initialBoard(int numOfRows, int numOfColumns)

Description:
Fills the initial board with white spaces.

Arguments:
Number of rows and number of columns.

Restrictions:
Only takes in integers.

Returns:
Does not return anything.


*********************************************************************/
void Ant::initialBoard(int numOfRows, int numOfColumns) {
  // fills the initial board with white spaces
  for (int aRow = 0; aRow < numOfRows; aRow++) {
    for (int aCol = 0; aCol < numOfColumns; aCol++) {
      matrix[aRow][aCol] = ' ';
    }
    cout << endl;
  }
}



/*********************************************************************
**
void Ant::displayBoard()

Description:
Displays the board, and prints '*' for the ant's current location.

Arguments:
No arguments.

Restrictions:
No restrictions.

Returns:
Does not return anything.


*********************************************************************/
/*
source(s):

C++ Early Objects 9th Edition (Gaddis, Walters, Muganda)
Chapter 8.10 - Program 8-22 (page 557)

http://www.cplusplus.com/forum/beginner/81437/

*/
void Ant::displayBoard() {
  int rows = getRows();
  int columns = getColumns();

  // iterates through the board
  for (int aRow = 0; aRow < rows; aRow++) {
    cout << '|';                // forms outside border
    for (int aColumn = 0; aColumn < columns; aColumn++) {
      // if ant is located at these coordinates, print '*'
      if (xCoord == aRow && yCoord == aColumn) {
        cout << setw(1) << '*' << " ";
      } else {
          // else, just print the current space (e.g. ' ' or '#')
          cout << setw(1) << matrix[aRow][aColumn] << " ";
      }
    }
    cout << setw(1) << '|';     // forms outside border
    cout << endl;
  }
  cout << endl;

}



/*********************************************************************
**
void Ant::moveAnt(char** matrix)

Description:
Moves ant based on current direction faced. If at the edge, skips the forward
step, makes another turn and then continues on.

Arguments:
Current direction (enum).

Restrictions:
Only takes in an enum value.

Returns:
Does not return anything.

*********************************************************************/
void Ant::moveAnt(Direction currDirect) {
  int sumX;
  int sumY;
  // moves ant forward based on current direction faced
  switch(currDirect) {
    case NORTH:
      sumX = getXCoord() - 1;
      sumY = getYCoord();

      // if at the edge, skips the forward step, makes another turn and then continues on
      if (sumX < 0) {
        sumX += 1;  // adds 1 to bring ant back to the board
        antDirection = EAST;  // changes direction to East
      }

      // set ant's location
      setXCoord(sumX);
      setYCoord(sumY);
      break;
    case EAST:
      sumX = getXCoord();
      sumY = getYCoord() + 1;

      // if at the edge, skips the forward step, makes another turn and then continues on
      if (sumY > (columnSize - 1)) {
        sumY -= 1;  // subtracts 1 to bring ant back to the board
        antDirection = WEST;  // changes direction to West
      }

      // set ant's location
      setXCoord(sumX);
      setYCoord(sumY);
      break;
    case SOUTH:
      sumX = getXCoord() + 1;
      sumY = getYCoord();

      // if at the edge, skips the forward step, makes another turn and then continues on
      if (sumX > (rowSize - 1)) {
        sumX -= 1;  // subtracts 1 to bring ant back to the board
        antDirection = NORTH;
      }

      // set ant's location
      setXCoord(sumX);
      setYCoord(sumY);
      break;
    case WEST:
      sumX = getXCoord();
      sumY = getYCoord() - 1;

      // if at the edge, skips the forward step, makes another turn and then continues on
      if (sumY < 0) {
        sumY += 1;
        antDirection = EAST;
      }

      // set ant's location
      setXCoord(sumX);
      setYCoord(sumY);
      break;
  }

  // displays the board after move is made
  displayBoard();
}


/*********************************************************************
**
void Ant::whiteTurnRight()

Description:
Changes the direction of the ant to the right.

Arguments:
No arguments.

Restrictions:
No restrictions.

Returns:
Does not return anything.

*********************************************************************/
/*
source(s):

https://stackoverflow.com/questions/3019153/how-do-i-use-an-enum-value-on-a-switch-statement-in-c

*/
void Ant::whiteTurnRight() {
  // changes the direction of the ant to the right
  switch(antDirection) {
    case NORTH:
      antDirection = EAST;
      break;
    case EAST:
      antDirection = SOUTH;
      break;
    case SOUTH:
      antDirection = WEST;
      break;
    case WEST:
      antDirection = NORTH;
      break;
  }
}


/*********************************************************************
**
void Ant::blackTurnLeft()

Description:
Changes the direction of the ant to the left.

Arguments:
No arguments.

Restrictions:
No restrictions.

Returns:
Does not return anything.


*********************************************************************/
/*
source(s):

https://stackoverflow.com/questions/3019153/how-do-i-use-an-enum-value-on-a-switch-statement-in-c

*/
void Ant::blackTurnLeft() {
  // changes the direction of the ant to the left
  switch(antDirection) {
    case NORTH:
      antDirection = WEST;
      break;
    case WEST:
      antDirection = SOUTH;
      break;
    case SOUTH:
      antDirection = EAST;
      break;
    case EAST:
      antDirection = NORTH;
      break;
  }
}
