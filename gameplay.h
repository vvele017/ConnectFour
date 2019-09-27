/*    Header File:  gameplay.h
           Author:  Vanessa Velez-Santos
       Student ID:  4129302  
       Assignment:  Program #4 Connect 4 */
#include <stdio.h>
#include <stdbool.h>//for use of bool
#include <string.h> //for use of string copy

#define NO_ERROR 0
#define GRID_SIZE 42
#define GRID_START 1
#define GRID_SEPARATOR '|'
#define ROWS 6
#define DIAGONAL_RIGHT 5
#define DIAGONAL_LEFT 7
#define FIRST_ROW 36 //the last number that will ma
#define COLUMNS 7
#define ALIGNMENT 4
#define TYPE "d"
#define RED -1     //numeric values representing 
#define YELLOW -2   // the color markers to use on grid
#define P1 "Red player"     //easier to display and change 
#define P2 "Yellow player" //the display names for players

void assignLocations(int[]);
void displayGrid();
int selectMove(int);
int setTurn(int);
bool moveIsValid(int, int[]);
void makePlay(int,int, int[]);
bool updateGameStatus(int[]);

