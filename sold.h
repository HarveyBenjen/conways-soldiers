#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#define HT 8
#define WD 7
#define EMPTY 0
#define FULL 1
#define FALSE 0
#define TRUE 1
#define NUMBOARDS 100000000000
#define NUM_OF_DIRECTIONS 4
#define IMPOSSIBLE ((x<2 && y<2)||(x==3 && y==0)||(x>4 && y<2)||(y>3)|| \
                   (x>6)||(x<0))

struct board
{
   int current[HT][WD];
   int parentIndex;
};
typedef struct board Board;

int setBoard(int arr[HT][WD]);
int copyBoard(int b1[HT][WD], int b2[HT][WD]);
int searchBoards(Board array[], int board[HT][WD], int childIndex);
int clearBoard(int arr[HT][WD]);
int moveUp(Board array[], int parent, int* child, int* count, int r, int c);
int moveLeft(Board array[], int parent, int* child, int* count, int r, int c);
int moveRight(Board array[], int parent, int* child, int* count, int r, int c);
int printBoard(int arr[HT][WD]);
int printResult(Board array[], int parent, int child);
int generateList(Board arr[], int y, int x);
void testAll();
