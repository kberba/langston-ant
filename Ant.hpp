/*********************************************************************
** Author: Karen Berba
** Date: 1/13/19
** Description:

Ant.hpp

Header file for Ant

Ant Class:
The Ant class keeps track of the ant's location (x and y coordinates) and
direction (N, E, S, W), as well as contains the function to move the ant on
the board. The Ant class also builds the board using a dynamic 2D
array, and contains board functions to display and initialize the board.

*********************************************************************/

// include guards
#ifndef ANT_HPP
#define ANT_HPP

// declare the enumerated type
enum Direction { NORTH = 1, EAST, SOUTH, WEST };

// Ant class declaration
class Ant
{
  private:
    int xCoord;
    int yCoord;
    char color;
    char antSign;
    int rowSize;
    int columnSize;
    Direction antDirection;
    char** matrix;

  public:
    // setters
    void setXCoord(int);
    void setYCoord(int);
    void setColor(int, int, char);
    void setRows(int);
    void setColumns(int);

    // getters
    char getAntSign();
    int getXCoord();
    int getYCoord();
    char getColor(int, int);
    int getRows();
    int getColumns();
    Direction getAntDirection();
    char** getBoard();

    // other functions
    void initialBoard(int, int);
    void displayBoard();
    void moveAnt(Direction);
    void whiteTurnRight();
    void blackTurnLeft();

    // constructor
    Ant(int x, int y, int r, int c);
};

#endif
