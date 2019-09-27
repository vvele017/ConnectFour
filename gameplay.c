/*    Source code:  gameplay.c
           Author:  Vanessa Velez-Santos
       Student ID:  4129302  
       Assignment:  Program #4 Connect 4 */
#include "gameplay.h" 

/* Function: assignLocation
   --------------------
 purpose:  Assign the numbers to the array that 
           pertain to the locations on the connect
           4 grid. 

 parameters: Original empty array

 returns: Nothing */ 
void assignLocations(int list[])
{
  int location = 1;
  int index;

  for(index = 0; index < GRID_SIZE; index++)
  {
    list[index] = location;
    location++;
  }
}

/* Function: displayGrid
   --------------------
 purpose:   Display the connect 4 grid to the user 

 parameters: Array with available grid number locations
             for players to enter as a move.

 returns: Nothing */ 
void displayGrid(int list[])
{
  int gridSpot = 0;
  int columnCounter = 1;
  int marker = 0;

  for(gridSpot = 0; gridSpot < GRID_SIZE; gridSpot++)
  {
    
    printf(" %c ",GRID_SEPARATOR);
    marker = list[gridSpot]; 

    if(marker == RED)
    {
      printf("%*.c",ALIGNMENT,'R');
    }
    else if(marker == YELLOW)
    {
       printf("%*.c",ALIGNMENT,'Y');
    }
    else
    {
      printf("%*.d",ALIGNMENT, marker);
    }

    columnCounter++;

    if(columnCounter == COLUMNS)
    {
      printf(" %c \n",GRID_SEPARATOR);
      columnCounter = 1; //reset
    }
  }
}

/* Function: selectMove
   --------------------
 purpose:  Displays who's turn it is currently.
           Allows the user to select a move from the grid.

 parameters: Player color by number, 0 for red, 1 for yellow

 returns: The number from the grid they chose 
          which will need to be validated */ 
int selectMove(int color)
{
  //Below is used to help display the string only
  char player[] = P2;
  int playerMove = YELLOW;
  if(color == RED) 
  {
    strcpy(player, P1);
  }
  
  printf("\n \t %s , your turn! \n Select a number on the grid: ", player);
  scanf("%d",&playerMove);

  return playerMove;
}

/* Function: setTurn
   --------------------
 purpose: Alternates player turns depending on who
          went last. If it was red, which is 0, player
          variable swaps to yellow, which is 1. 

 parameters: Player who went last.

 returns: Current player in turn as an integer */ 
int setTurn(int player)
{
  if(player == RED)
  {
    player = YELLOW; //sets player to yellow
  }
  else
  {
    player = RED;// sets player to red
  }

  return player;
}

/* Function: moveIsValid
   --------------------
 purpose:  To check if the user's move was valid.
           Default is invalid input. Will change to 
           valid only if the user enters a choice from 1 to 42
           and if it isn't taken by a marker already.

 parameters: Move made by the user and the grid locations
             with all current markers.

 returns: True if the move is a valid playable one.
          False if otherwise       */ 
bool moveIsValid(int moveMade, int grid[])
{
  bool valid = false,
       integerInput = false,//user entered a number?
       legalBounds  = false,//number from GRID_START to GRID_SIZE entered?
       markerPlaced = true, //marker already placed in location?
       canStack     = false;//is there a marker placed underneath to stack? 
  int gridLocation = moveMade - 1,
      columnBelow  = RED; 

  //check if bounds are good
  if(moveMade >= GRID_START && moveMade <= GRID_SIZE)
  {
    legalBounds = true;
    if(moveMade < 37)
    {
      columnBelow = grid[gridLocation + ROWS];
    }
  }
  //check if a marker has been placed already 
  if( (grid[gridLocation] != RED && grid[gridLocation] != YELLOW ) )
  {
      markerPlaced = false; 
  }
  //if there is a marker underneath, we can add a marker to the current location
  if( columnBelow == RED || columnBelow == YELLOW )
  {
    canStack = true;
  }

  //if ALL conditions met, the input is fully valid
  if(legalBounds && !markerPlaced && canStack)
  {
    valid = true;
  }

  return valid;
}

/* Function: makePlay
   --------------------
 purpose:  To store in the connect 4 grid the choice the
           user made and replace the number with the 
           integer representation for RED and YELLOW.

 parameters: the move number made,
             the current player color stored as an int,
             the grid for connect 4

 returns: Nothing        */ 
void makePlay(int move,int player, int grid[])
{
  int markerNumber = RED;
  if(player == YELLOW)
  {
    markerNumber = YELLOW;
  }

  grid[ move - 1 ] = markerNumber; 
}

/* Function: updatedGameStatus
   --------------------
 purpose: Determine the game's status and see if 
          the game is over due to a tie, red winning,
          or yellow winning.

 parameters: Connect 4 grid

 returns: Game's active or done status */ 
bool updateGameStatus(int grid[])
{
  enum status {active = 0,
               gameover = 1} game;
  game = active;
  int index,
      currentMarker = 0,
      markerCount = 0, //count how many markers have been placed
      redHorizontal = 0, redVertical = 0, redDiagonalRight = 0,redDiagonalLeft = 0,
      yellowHorizontal = 0, yellowVertical = 0, yellowDiagonalRight = 0,yellowDiagonalLeft = 0;
  bool yellowWon = false,
       redWon    = false;
  int oneAbove = 0, nextTo = 0, accrossRight = 0, accrossLeft = 0;
  
  for(index = GRID_SIZE; index >= 0; index--) 
  {
    currentMarker = grid[index];
    oneAbove = grid[index - ROWS]; //checks marker directly above
    nextTo   = grid[index - 1];    // checks marker to the left of current one
    accrossRight  = grid[index - DIAGONAL_RIGHT]; //checks marker accross rightside from current one
    accrossLeft   = grid[index - DIAGONAL_LEFT];//marker across left side from current one

    //for RED marker
    if(oneAbove == RED)
    {
      redVertical++;
    }
    else
    {
      redVertical = 0;
    }

    if(nextTo == RED)
    {
      redHorizontal++;
    }
    else
    {
      redHorizontal = 0;
    }

    if(accrossRight == RED)
    {
      redDiagonalRight++;
    }
    else
    {
      redDiagonalRight = 0;
    }
    if(accrossLeft == RED)
    {
      redDiagonalLeft++;
    }
    else
    {
      redDiagonalLeft = 0;
    }

    //for the YELLOW marker
    if(oneAbove == YELLOW)
    {
      yellowVertical++;
    }
    else
    {
      yellowVertical = 0;
    } 

    if(nextTo ==  YELLOW)
    {
      yellowHorizontal++;
    }
    else
    {
      yellowHorizontal = 0;
    }

    if(accrossRight == YELLOW)
    {
      yellowDiagonalRight++;
    }
    else
    {
      yellowDiagonalRight = 0;
    }
    
    if(accrossLeft == YELLOW)
    {
      yellowDiagonalLeft++;
    }
    else
    {
      yellowDiagonalLeft = 0;
    }
  
    if(redHorizontal == 4 || redVertical == 4 || redDiagonalLeft == 4 || redDiagonalRight == 4)
    {
      redWon = true;
    }
    else if (yellowHorizontal == 4 || yellowVertical == 4 || yellowDiagonalLeft == 4 || yellowDiagonalRight == 4)
    {
      yellowWon = true;
    }

    if(currentMarker == RED || currentMarker == YELLOW)
    {
      markerCount++;
    }
  }

  if(yellowWon)
  {
    game = gameover;
    puts("\n \t YELLOW WON \n");
  }
  else if(redWon)
  {
    game = gameover;
    puts("\n \t RED WON \n");
  }
  else if(markerCount == GRID_SIZE) //tie. all spots filled
  {
    game = gameover; 
    puts("\n \t Tie! No one wins! \n");   
  }

  return game;
}
