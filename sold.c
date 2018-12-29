#include "sold.h"

int main(int argc, const char* argv[])
{
   int x=0, y=0;
   Board* boards = (Board*)malloc(sizeof(Board)*NUMBOARDS);
   testAll();

   if(argc!=3)
   {
      printf("\nYou did not enter the proper cell coordinates.\n");
   }
   else
   {
      sscanf(argv[1], "%d", &x);
      sscanf(argv[2], "%d", &y);
   }
   if(IMPOSSIBLE)
   {
      printf("\nThat move is not possible.\nProgram Terminated\n\n");
   }
   else
   {
      generateList(boards, y, x);
   }
   return 0;
}

int setBoard(int arr[HT][WD])
{
   int r, c;

   for (r=0; r<HT; ++r)
   {
      for(c=0; c<WD; ++c)
      {
         arr[r][c] = EMPTY;
      }
   }
   for(r=(HT-1); r>=(HT/2); --r)
   {
      for(c=0; c<WD; ++c)
      {
         arr[r][c] = FULL;
      }
   }
   return TRUE;
}

int copyBoard(int b1[HT][WD], int b2[HT][WD])
{
   int r, c;
   for (r=0; r<HT; ++r)
   {
      for(c=0; c<WD; ++c)
      {
         b2[r][c] = b1[r][c];
      }
   }
   return TRUE;
}

int searchBoards(Board array[], int board[HT][WD], int childIndex)
{
   int r, c, i, match=0;

   for(i=1; i<childIndex; ++i)
   {
      for (r=0; r<HT; ++r)
      {
         for(c=0; c<WD; ++c)
         {
            if(array[i].current[r][c] == board[r][c])
            {
               match += 1;
            }
         }
      }
      if(match == (HT*WD))
      {
         return TRUE;
      }
      match = 0;
   }
   return FALSE;
}

int clearBoard(int arr[HT][WD])
{
   int r, c;
   for (r=0; r<HT; ++r)
   {
      for(c=0; c<WD; ++c)
      {
         arr[r][c] = EMPTY;
      }
   }
   return TRUE;
}

int moveUp(Board array[], int parent, int* child, int* count, int r, int c)
{
   copyBoard(array[parent].current, array[*child].current);
   array[*child].current[r][c] = EMPTY;
   array[*child].current[r-1][c] = EMPTY;
   array[*child].current[r-2][c] = FULL;
   if((searchBoards(array, array[*child].current, *child)) == 1)
   {
      clearBoard(array[*child].current);
      return FALSE;
   }
   else
   {
      array[*child].parentIndex = parent;
      *child+=1;
      *count+=1;
      printf("Board Number: %d\n", *count);
      return TRUE;
   }
}

int moveLeft(Board array[], int parent, int* child, int* count, int r, int c)
{
   copyBoard(array[parent].current, array[*child].current);
   array[*child].current[r][c] = EMPTY;
   array[*child].current[r][c-1] = EMPTY;
   array[*child].current[r][c-2] = FULL;
   if((searchBoards(array, array[*child].current, *child)) == 1)
   {
      clearBoard(array[*child].current);
      return FALSE;
   }
   else
   {
      array[*child].parentIndex = parent;
      *child+=1;
      *count+=1;
      printf("Board Number: %d\n", *count);
      return TRUE;
   }
}

int moveRight(Board array[], int parent, int* child, int* count, int r, int c)
{
   copyBoard(array[parent].current, array[*child].current);
   array[*child].current[r][c] = EMPTY;
   array[*child].current[r][c+1] = EMPTY;
   array[*child].current[r][c+2] = FULL;
   if((searchBoards(array, array[*child].current, *child)) == 1)
   {
      clearBoard(array[*child].current);
      return FALSE;
   }
   else
   {
      array[*child].parentIndex = parent;
      *child+=1;
      *count+=1;
      printf("Board Number: %d\n", *count);
      return TRUE;
   }
}

int printBoard(int arr[HT][WD])
{
   int i, j;
   printf("\n");
   for (i=0; i<HT; ++i)
   {
      for(j=0; j<WD; ++j)
      {
         if(arr[i][j] == FULL)
         {
            printf("X");
         }
         else
         {
            printf("-");
         }
      }
      printf("\n");
   }
   printf("\n");
   return TRUE;
}

int printResult(Board array[], int parent, int child)
{
   printBoard(array[child].current);
   while(parent>0)
   {
      printBoard(array[parent].current);
      parent = array[parent].parentIndex;
   }
   printBoard(array[parent].current);
   return TRUE;
}

int generateList(Board array[], int y, int x)
{
   int r, c, n, parIndex = 0, childInd = 1, up=0, left=0, right=0, count=0;
   Board temp;
   setBoard(array[parIndex].current);
   setBoard(array[childInd].current);
   setBoard(temp.current);
   while(array[childInd-1].current[y][x] != FULL)
   {
      for(r=0;r<HT; ++r)
      {
         for(c=0; c<WD; ++c)
         {
            up=0;
            left=0;
            right=0;
            n=0;
            while((n<NUM_OF_DIRECTIONS) &&
            (array[childInd-1].current[y][x] != FULL) &&
            (array[parIndex].current[r][c] == FULL))
            {
               if((r-2)>=0 && up!=1)   /*look up*/
               {
                  if((array[parIndex].current[r-1][c])==FULL &&
                  (array[parIndex].current[r-2][c])==EMPTY)
                  {
                     moveUp(array, parIndex, &childInd, &count, r, c);
                     up = 1;
                  }
               }
               if((c-2)>=0 && left!=1)   /*look left*/
               {
                  if((array[parIndex].current[r][c-1])==FULL &&
                  (array[parIndex].current[r][c-2])== EMPTY)
                  {
                     moveLeft(array, parIndex, &childInd, &count, r, c);
                     left = 1;
                  }
               }
               if((c+2)<=(WD-1) && right!=1)   /*look right*/
               {
                  if((array[parIndex].current[r][c+1])==FULL &&
                  (array[parIndex].current[r][c+2])== EMPTY)
                  {
                     moveRight(array, parIndex, &childInd, &count, r, c);
                     right = 1;
                  }
               }
               ++n;
            }
         }
      }
      ++parIndex;
   }
   parIndex--;
   childInd--;
   printf("\nParent Index: %d\n", parIndex);
   printf("Child Index: %d\n", childInd);
   printResult(array, parIndex, childInd);
   return TRUE;
}
