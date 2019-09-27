/*    Source code:  connectMain.c
           Author:  Vanessa Velez-Santos
       Student ID:  4129302  
       Assignment:  Program #4 Connect 4
   
            Course:  COP 4338 - Programming III  
           Section:  U03 
        Instructor:  William Feild  
          Due Date:  October 23, at the beginning of class
 
 	I hereby certify that this collective work is my own
 	and none of it is the work of any other person or entity.
 	______________________________________ [Signature]
   
         Language:  C
          
                  Compile/Run  
      With makefile: make
                     ./a.out

      Backup without a makefile: 
                                gcc connectMain.c gameplay.c   
                                ./a.out
+------------------------------------------------------------- 
  Description: Game of connect 4, where the RED and YELLOW
               players will be prompted to enter numebrs 1 to
               42 on a grid until there is a tie, or 4 red markers
               are consecuitve or 4 yellow markers are consecutive.

               As players enter VALID input into the grid, the grid is
               updated and numbers are replaced with the respective 
               markers.

  Process:     Grid numbers are assigned to the array for connect4.
               The original, untouched grid is displayed once, and then
               the first user, RED, is prompted for a move.

               This move is validated and checked to see if it is in range,
                if the spot isn't already full from another marker,
               or if there is a marker under the location it in order
               be able to place a marker above that spot. With the exception
               of the final row.

               The game's status is then checked to see if there is a win based
               off 2 conditions: A tie or 4 consecutive markers from either player
               in the horizontal, vertial, or diagonal of the grid.

               If the game is done, display the winner with how they won, or the tie,
               but if it isn't done, repeat the entire process again.

  Required Features Not Included: Problems checking for winner. Does not count for diagonal win properly, horizontal or vertical win for yellow.

  Does not display HOW the user won
                
  Known Bugs: User enters something that isn't a number
              will cause problems with scanf
*/
#include "gameplay.h"

int main() 
{
  int connect4Grid[GRID_SIZE];
  int currentPlayer = RED; //default starting player
  bool gameFinished = false,
       validMove    = false;
  int moveMade = 0; //default is no move made

  assignLocations(connect4Grid); //give values to grid location
  displayGrid(connect4Grid);     //display original grid

  do
  {      
    moveMade = selectMove(currentPlayer);
    validMove = moveIsValid(moveMade,connect4Grid);

    if(validMove == true)//if move is valid, set turn to opposing player for next move
    {
      makePlay(moveMade, currentPlayer, connect4Grid);
      currentPlayer = setTurn(currentPlayer);
      gameFinished  = updateGameStatus(connect4Grid);
    }
    else 
    {
      puts("\n Invalid Move. \n Enter a number from 1 to 42 AND that isn't taken by a marker. \n There must be a marker underneath your selection if it isn't the bottom row. \n");
    }
    displayGrid(connect4Grid); 
  }while(!gameFinished);
  
  return NO_ERROR;
}