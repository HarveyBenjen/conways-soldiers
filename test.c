#include "sold.h"

void testAll()
{
   static Board boards[NUMBOARDS];
   Board temp;
   int parent = 0, child = 1, count = 0;
   temp.parentIndex = 0;
   assert(setBoard(boards[0].current)==1);
   assert(copyBoard(boards[0].current, temp.current)==1);
   assert(searchBoards(boards, temp.current, 1)==0);
   assert(clearBoard(temp.current)==1);

   assert(moveUp(boards, parent, &child, &count, 0, 4)==1);
   assert(moveLeft(boards, parent, &child, &count, 0, 0)==1);
   assert(moveRight(boards, parent, &child, &count, 0, 0)==1);
   assert(generateList(boards, 3, 0)==1);
}
