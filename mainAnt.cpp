/*********************************************************************
** Author: Karen Berba
** Date: 1/13/19
** Description:

mainAnt.cpp

The mainAnt function contains a separate menu function that asks the user if
they would like to start/quit the Langston Ant Simulation. After starting the
simulation, the user is prompted to enter how large the board is, the amount of
steps they want the simulation to run for, where to place the ant, and when the
game ends, whether they want to play again/quit. Each input is checked with a
separate input validation function.

Link to Langston Ant Description:
https://en.wikipedia.org/wiki/Langton%27s_ant

How to run:
Compile Ant.cpp and mainAnt.cpp together.

***** NOTE: Works best on a 70x70 board at 11000 steps ****

*********************************************************************/

#include "Ant.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
#include <limits>


using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;


// function prototypes
/*
source(s):
  C++ Early Objects 9th Edition (Gaddis, Walters, Muganda)
  Chapter 6.9 - Program 6-14 (page 351)
*/
int menu();
int inputValidation();

// main
int main() {
  int menuChoice;
  int rows;
  int columns;
  int stepsCount = 0;
  int maxSteps;
  int antStartX;
  int antStartY;
  int currentX;
  int currentY;
  char prevSpace;
  char prevSpaceColor;
  Direction currentDirection;

  cout << "Welcome to the Langston Ant program!" << endl;

  // menu to prompt user to start or quit program
  menuChoice = menu();

  // if user chooses to quit program
  if (menuChoice == 2) {
    cout << "Thank you. Goodbye!" << endl;
    return 0;
  }

  // if menuChoice is 1 (start) loop until user chooses to quit
  while (menuChoice == 1) {
    // prompt user for size of board
    // *** number of rows
    // *** number of columns
    cout << endl;
    cout << "---------------------------------------" << endl;
    cout << "Please choose the size of your board." << endl;
    cout << endl;
    cout << "How many rows would you like to have?" << endl;
    // cin >> rows;
    rows = inputValidation();   // inputs validation
    cout << "How many columns would you like to have?" << endl;
    // cin >> columns;
    columns = inputValidation(); // inputs validation

    // prompt for number of steps
    cout << "Please choose the number of steps you would like the simulation to run: " << endl;
    // cin >> maxSteps;
    maxSteps = inputValidation(); // inputs validation

    // prompt for ant's starting position (x, y)
    cout << "Please choose the ant's starting x coordinate: " << endl;
    // cin >> antStartX;
    antStartX = inputValidation();
    cout << "Now choose the ant's starting y coordinate: " << endl;
    // cin >> antStartY;
    antStartY = inputValidation();


    // call on Ant class to make Ant object ***********
    Ant antObj(antStartX, antStartY, rows, columns);


    // create a local copy of the board
    char** matrix = antObj.getBoard();


    // loop until you reach the max step
    for (int i = 0; i < maxSteps; i++) {
      // get ant's location
      currentX = antObj.getXCoord();
      currentY = antObj.getYCoord();

      // get the current space's color
      char prevSpaceColor = antObj.getColor(currentX, currentY);

      // if it is the first move, note the color
      if (i == 0) {
        cout << "Ant is placed. " << endl;
        antObj.displayBoard();

        // REMOVE AFTER TESTING
        // get ant's current direction
        currentDirection = antObj.getAntDirection();
        cout << "Ant's current direction is: " << currentDirection << endl;
      }

      // for white space - turn right and change space to black
      if (prevSpaceColor == ' ') {
        // turn right (change direction)
        antObj.whiteTurnRight();

        // change color to black
        antObj.setColor(currentX, currentY, '#');

        // get ant's current direction
        currentDirection = antObj.getAntDirection();

        // move ant forward based on current direction faced
        antObj.moveAnt(currentDirection);

        // REMOVE AFTER TESTING
        cout << "Ant's current direction is: " << currentDirection << endl;
      }

      // for black space - turn left and change space to white
      if (prevSpaceColor == '#') {
        // turn right (change direction)
        antObj.blackTurnLeft();

        // change color to black
        antObj.setColor(currentX, currentY, ' ');

        // get ant's current direction
        currentDirection = antObj.getAntDirection();

        // move ant forward based on current direction faced
        antObj.moveAnt(currentDirection);

        // REMOVE AFTER TESTING
        cout << "Ant's current direction is: " << currentDirection << endl;
      }
    }



    // free dynamically allocated memory
    /* source(s):

    https://stackoverflow.com/questions/30720594/deleting-a-dynamically-allocated-2d-array/30720628

    https://stackoverflow.com/questions/936687/how-do-i-declare-a-2d-array-in-c-using-new

    */
    for (int i = 0; i < rows; i++) {
      delete[] matrix[i];  // deletes the columns
    }
    delete[] matrix;  // deletes the rows


    // asks if user wants to play again
    cout << endl;
    cout << "---------------------------------------" << endl;
    cout << "Play again? " << endl;
    menuChoice = menu();

    // if user chooses to quit program
    if (menuChoice == 2) {
      cout << endl;
      cout << "---------------------------------------" << endl;
      cout << "Thank you for playing Langston's Ant Simulation. Goodbye!" << endl;
      return 0;
    }

  }

  return 0;
}



/*********************************************************************
**
int menu()

Desription:
A menu with the options to start or quit the simulation. Has no parameters.

Arguments:
No arguments.

Restrictions:
Can only accept numbers that are the option choices (e.g. 1 or 2).

Returns:
The option the user chose from the menu as an integer.


*********************************************************************/
/*
source(s):
  C++ Early Objects 9th Edition (Gaddis, Walters, Muganda)
  Chapter 6.9 - Program 6-14 (page 351)

  http://www.cplusplus.com/forum/beginner/229334/

*/
int menu() {
  int choice;       // holds the user's menu choice

  do {
    // displays the menu
    cout << "\n Options Menu\n\n";
    cout << "(1) START\n";
    cout << "(2) QUIT\n\n";

    // user chooses from the menu options
    cout << "Please choose an option from the menu: " << endl;
    cin >> choice;

    // input validation
    while (choice < 1 || choice > 2) {
      cout << "That is not a valid choice. Choose either: (1) START, or (2) QUIT. Please re-enter a valid number. " << endl;
      cin >> choice;
    }
    cout << "You have chosen: ";

    switch (choice) {
      case 1: cout << "(1) START" << endl;
              break;
      case 2: cout << "(2) QUIT " << endl;
              break;
    }

  } while (choice < 1 || choice > 2);

  return choice;
}


/*********************************************************************
**
int inputValidation()

Desription:
Checks to see if the user has inputted a number.
Will keep looping until a valid number has been entered. Has no parameters.

Arguments:
No arguments.

Restrictions:
No restrictions.

Returns:
Returns the number the user enters.


*********************************************************************/
/*
source(s):

https://stackoverflow.com/questions/19018294/c-to-check-if-user-input-is-a-number-not-a-character-or-a-symbol

https://www.hackerearth.com/practice/notes/validating-user-input-in-c/

https://stackoverflow.com/questions/9612839/is-there-a-way-to-check-if-a-variable-is-a-whole-number-c

https://www.programiz.com/cpp-programming/library-function/cmath/floor

https://stackoverflow.com/questions/20446373/cin-ignorenumeric-limitsstreamsizemax-n-max-not-recognize-it

https://stackoverflow.com/questions/4798936/numeric-limits-was-not-declared-in-this-scope-no-matching-function-for-call-t

*/
int inputValidation()
{
    int input;
    // takes in user input
    cin >> input;

    // if the user enters a non-numeric value
    while(cin.fail() || input <= 0) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
      cout << "That is not a valid choice. Please re-enter a valid number: " << endl;
      cin >> input;
      cout << endl;
    }

    return input;
}
