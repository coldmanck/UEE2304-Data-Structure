#include <stdio.h>
#include "HW3_ADT/stacksADT.h"

// specify the last move orientation
enum LastMove {east, south, west, north};
enum LastMove LASTMOVE;

const int SIZE_ROW = 10;
const int SIZE_COL = 12;
bool MAZE[10][12] = {
	{1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,1,1,0,1,0,1,0,1},
	{1,1,1,0,1,0,0,0,0,0,0,1},
	{1,1,0,0,0,0,1,1,1,1,0,1},
	{1,1,0,1,1,1,1,1,1,1,0,0},
	{1,1,0,1,0,1,1,1,1,1,1,1},
	{1,1,0,0,0,1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1,1,0,1,0,1},
	{1,1,0,0,0,0,0,1,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1}
	};
bool ifDeadRoad[10][12] = {0};

int main(){
	// print the map
	for(int i = 0; i < SIZE_ROW; i++){
		for(int j = 0; j < SIZE_COL; j++)
			printf("%d ", MAZE[i][j]);
		printf("\n");
	}
	
	STACK* visitedStack;			// places has been traversed
	STACK* alternativeStack;		// paths other than decided path at branch point
	STACK* alternativeOrientStack;	// save orientation when saving the other path
	int* dataPtr;
	visitedStack = createStack();
	alternativeStack = createStack();
	alternativeOrientStack = createStack();
	
	int curRow, curCol = 0;
	printf("1 -> Wall, 0 -> Space.\n");
	while(1){
		printf("input where to start (e.g. '2 3' means row 2, col 3): ");
		scanf("%d %d", &curRow, &curCol);
		curRow--; curCol--;
		if(MAZE[curRow][curCol] == 1)
			printf("Error. Please input space coordinate. Retry.\n");
		else
			break;
	}

	// Firstly, preprocess the first point, there're 16 possibie ways
	// east, south, west, north
	if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol + 1] == 0 && 
	   MAZE[curRow + 1][curCol] == 0 && MAZE[curRow][curCol - 1] == 0){
		int* dataPtr3 = (int*)malloc(sizeof(int));
		*dataPtr3 = (curRow - 1) * 10 + curCol;
		pushStack(alternativeStack, dataPtr3);

		enum LastMove alterMove1 = 3;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);
		
		int* dataPtr4 = (int*)malloc(sizeof(int));
		*dataPtr4 = (curRow + 1) * 10 + curCol;
		pushStack(alternativeStack, dataPtr4);

		enum LastMove alterMove2 = 1;
		int* alterMovePtr2 = (int*)malloc(sizeof(int));
		*alterMovePtr2 = (int) alterMove2;
		pushStack(alternativeOrientStack, alterMovePtr2);

		int* dataPtr5 = (int*)malloc(sizeof(int));
		*dataPtr5 = curRow * 10 + (curCol - 1);
		pushStack(alternativeStack, dataPtr5);

		enum LastMove alterMove3 = 2;
		int* alterMovePtr3 = (int*)malloc(sizeof(int));
		*alterMovePtr3 = (int) alterMove3;
		pushStack(alternativeOrientStack, alterMovePtr3);

		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curCol += 1;
		LASTMOVE = 0; 
	}
	// north, east, south
	else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol + 1] == 0 && MAZE[curRow + 1][curCol] == 0){
		int* dataPtr3 = (int*)malloc(sizeof(int));
		*dataPtr3 = (curRow - 1) * 10 + curCol;
		pushStack(alternativeStack, dataPtr3);

		enum LastMove alterMove1 = 3;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);
		
		int* dataPtr4 = (int*)malloc(sizeof(int));
		*dataPtr4 = (curRow + 1) * 10 + curCol;
		pushStack(alternativeStack, dataPtr4);

		enum LastMove alterMove2 = 1;
		int* alterMovePtr2 = (int*)malloc(sizeof(int));
		*alterMovePtr2 = (int) alterMove2;
		pushStack(alternativeOrientStack, alterMovePtr2);

		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curCol += 1;
		LASTMOVE = 0;
	}
	// east, south, west
	else if(MAZE[curRow][curCol - 1] == 0 && MAZE[curRow][curCol + 1] == 0 && MAZE[curRow + 1][curCol] == 0){
		int* dataPtr3 = (int*)malloc(sizeof(int));
		*dataPtr3 = curRow * 10 + (curCol - 1);
		pushStack(alternativeStack, dataPtr3);

		enum LastMove alterMove1 = 2;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);
				
		int* dataPtr4 = (int*)malloc(sizeof(int));
		*dataPtr4 = (curRow + 1) * 10 + curCol;
		pushStack(alternativeStack, dataPtr4);

		enum LastMove alterMove2 = 1;
		int* alterMovePtr2 = (int*)malloc(sizeof(int));
		*alterMovePtr2 = (int) alterMove2;
		pushStack(alternativeOrientStack, alterMovePtr2);

		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curCol += 1;
		LASTMOVE = 0;
	}
	// north, west, south
	else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol - 1] == 0 && MAZE[curRow + 1][curCol] == 0){
			int* dataPtr3 = (int*)malloc(sizeof(int));
			*dataPtr3 = curRow * 10 + (curCol - 1);
			pushStack(alternativeStack, dataPtr3);

			enum LastMove alterMove1 = 2;
			int* alterMovePtr1 = (int*)malloc(sizeof(int));
			*alterMovePtr1 = (int) alterMove1;
			pushStack(alternativeOrientStack, alterMovePtr1);
					
			int* dataPtr4 = (int*)malloc(sizeof(int));
			*dataPtr4 = (curRow - 1) * 10 + curCol;
			pushStack(alternativeStack, dataPtr4);

			enum LastMove alterMove2 = 3;
			int* alterMovePtr2 = (int*)malloc(sizeof(int));
			*alterMovePtr2 = (int) alterMove2;
			pushStack(alternativeOrientStack, alterMovePtr2);

			dataPtr = (int*)malloc(sizeof(int));
			*dataPtr = -1;
			pushStack(visitedStack, dataPtr);

			curRow += 1;
			LASTMOVE = 1;
	}
	// east, north, west
	else if(MAZE[curRow][curCol - 1] == 0 && MAZE[curRow][curCol + 1] == 0 && MAZE[curRow - 1][curCol] == 0){
		int* dataPtr3 = (int*)malloc(sizeof(int));
		*dataPtr3 = curRow * 10 + (curCol - 1);
		pushStack(alternativeStack, dataPtr3);

		enum LastMove alterMove1 = 2;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);
				
		int* dataPtr4 = (int*)malloc(sizeof(int));
		*dataPtr4 = (curRow - 1) * 10 + curCol;
		pushStack(alternativeStack, dataPtr4);

		enum LastMove alterMove2 = 3;
		int* alterMovePtr2 = (int*)malloc(sizeof(int));
		*alterMovePtr2 = (int) alterMove2;
		pushStack(alternativeOrientStack, alterMovePtr2);

		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curCol += 1;
		LASTMOVE = 0;
	}
	// north, east
	else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol + 1] == 0){
		int* dataPtr3 = (int*)malloc(sizeof(int));
		*dataPtr3 = (curRow - 1) * 10 + curCol;
		pushStack(alternativeStack, dataPtr3);
		
		enum LastMove alterMove1 = 3;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);

		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curCol += 1;
		LASTMOVE = 0;
	} 
	// north, south
	else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow + 1][curCol] == 0){
		int* dataPtr4 = (int*)malloc(sizeof(int));
		*dataPtr4 = (curRow - 1) * 10 + curCol;
		pushStack(alternativeStack, dataPtr4);

		enum LastMove alterMove1 = 3;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);

		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curRow += 1;
		LASTMOVE = 1;
	} 
	// east, south
	else if(MAZE[curRow + 1][curCol] == 0 && MAZE[curRow][curCol + 1] == 0){
		int* dataPtr4 = (int*)malloc(sizeof(int));
        *dataPtr4 = (curRow + 1) * 10 + curCol;
        pushStack(alternativeStack, dataPtr4);

		enum LastMove alterMove1 = 1;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);
		
		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curCol += 1;
		LASTMOVE = 0;
	}
	// north, west
	else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol - 1] == 0){
		int* dataPtr3 = (int*)malloc(sizeof(int));
		*dataPtr3 = (curRow - 1) * 10 + curCol;
		pushStack(alternativeStack, dataPtr3);

		enum LastMove alterMove1 = 3;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);
		
		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curCol -= 1;
		LASTMOVE = 2;
	} 
	// west, south
	else if(MAZE[curRow + 1][curCol] == 0 && MAZE[curRow][curCol - 1] == 0){
		int* dataPtr4 = (int*)malloc(sizeof(int));
        *dataPtr4 = curRow * 10 + (curCol - 1);
        pushStack(alternativeStack, dataPtr4);

		enum LastMove alterMove1 = 2;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);
		
		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curRow += 1;
		LASTMOVE = 1;
	}
	// east, west
	else if(MAZE[curRow][curCol - 1] == 0 && MAZE[curRow][curCol + 1] == 0){
		int* dataPtr3 = (int*)malloc(sizeof(int));
		*dataPtr3 = curRow * 10 + (curCol - 1);
		pushStack(alternativeStack, dataPtr3);

		enum LastMove alterMove1 = 2;
		int* alterMovePtr1 = (int*)malloc(sizeof(int));
		*alterMovePtr1 = (int) alterMove1;
		pushStack(alternativeOrientStack, alterMovePtr1);
		
		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = -1;
		pushStack(visitedStack, dataPtr);

		curCol += 1;
		LASTMOVE = 0;
	}
	else{ 
		if(MAZE[curRow][curCol + 1] == 0){
			curCol += 1;
			LASTMOVE = 0;
		}
		else if(MAZE[curRow + 1][curCol] == 0){
			curRow += 1;
			LASTMOVE = 1;
		}
		else if(MAZE[curRow][curCol - 1] == 0){
			curCol -= 1;
			LASTMOVE = 2;
		}
		else if(MAZE[curRow - 1][curCol] == 0){
			curRow -= 1;
			LASTMOVE = 3;
		}
		
		dataPtr = (int*)malloc(sizeof(int));
		*dataPtr = curRow * 10 + curCol;
		pushStack(visitedStack, dataPtr);
	}	

	// Start the traverse
	while(!(curRow == 4 && curCol == 11)){
		switch(LASTMOVE){
			/*
				LASTMOVE = 0 -> last move is east-orient
						   1 -> last move is south-orient
						   2 -> last move is west-orient
						   3 -> last move is north-orient
				In default, mouse prefer go east first. If it cannot, then try south. Similarly, it will try west, north
				if there's obstacle.
			*/
			case 0:
				// if north, east, south is space (where can be traversed)
				if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol + 1] == 0 && MAZE[curRow + 1][curCol] == 0){
					// save the north branch into alternativeStack
					int* dataPtr3 = (int*)malloc(sizeof(int));
					*dataPtr3 = (curRow - 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr3);
					
					// also save the north branch's orientation (which is 3) into alternativeOrientStack
					enum LastMove alterMove1 = 3;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
					
					// save the south branch into alternativeStack
					int* dataPtr4 = (int*)malloc(sizeof(int));
					*dataPtr4 = (curRow + 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr4);
					
					// also save the south branch's orientation (which is 1) into alternativeOrientStack
					enum LastMove alterMove2 = 1;
					int* alterMovePtr2 = (int*)malloc(sizeof(int));
					*alterMovePtr2 = (int) alterMove2;
					pushStack(alternativeOrientStack, alterMovePtr2);
					
					// save the branch point into visitedStack and set the value '-1' as token
					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);
					
					// move east, also set orient to east ('0')
					curCol += 1;
					LASTMOVE = 0;
				} 
				// north, east
				else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol + 1] == 0){
					int* dataPtr3 = (int*)malloc(sizeof(int));
					*dataPtr3 = (curRow - 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr3);
					
					enum LastMove alterMove1 = 3;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol += 1;
					LASTMOVE = 0;
				} 
				// north, south
				else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow + 1][curCol] == 0){
					int* dataPtr4 = (int*)malloc(sizeof(int));
					*dataPtr4 = (curRow - 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove1 = 3;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curRow += 1;
					LASTMOVE = 1;
				} 
				// east, south
				else if(MAZE[curRow + 1][curCol] == 0 && MAZE[curRow][curCol + 1] == 0){
					int* dataPtr4 = (int*)malloc(sizeof(int));
                    *dataPtr4 = (curRow + 1) * 10 + curCol;
                    pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove1 = 1;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
					
					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol += 1;
					LASTMOVE = 0;
				}
				else{ 
					if(MAZE[curRow][curCol + 1] == 0 && LASTMOVE != 2){
						curCol += 1;
						LASTMOVE = 0;
					}
					else if(MAZE[curRow + 1][curCol] == 0 && LASTMOVE != 3){
						curRow += 1;
						LASTMOVE = 1;
					}
					else if(MAZE[curRow][curCol - 1] == 0 && LASTMOVE != 0){
						curCol -= 1;
						LASTMOVE = 2;
					}
					else if(MAZE[curRow - 1][curCol] == 0 && LASTMOVE != 1){
						curRow -= 1;
						LASTMOVE = 3;
					}
					else{
						int* branchPoint = popStack(visitedStack);
						do{	
							curCol = *branchPoint % 10;
							curRow = *branchPoint / 10;
							printf("%d row,  %d col (Backtracking)\n", curRow + 1, curCol + 1);
							branchPoint = popStack(visitedStack);	
						} while (*branchPoint != -1);

						int* newBranch = popStack(alternativeStack);
						curCol = *newBranch % 10;
						curRow = *newBranch / 10;
						int* temp = popStack(alternativeOrientStack);
						LASTMOVE = (enum LastMove) *temp;
					}

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = curRow * 10 + curCol;
					pushStack(visitedStack, dataPtr);
				}

				break;
			case 1:
				// east, south, west
				if(MAZE[curRow][curCol - 1] == 0 && MAZE[curRow][curCol + 1] == 0 && MAZE[curRow + 1][curCol] == 0){
					int* dataPtr3 = (int*)malloc(sizeof(int));
					*dataPtr3 = curRow * 10 + (curCol - 1);
					pushStack(alternativeStack, dataPtr3);

					enum LastMove alterMove1 = 2;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
							
					int* dataPtr4 = (int*)malloc(sizeof(int));
					*dataPtr4 = (curRow + 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove2 = 1;
					int* alterMovePtr2 = (int*)malloc(sizeof(int));
					*alterMovePtr2 = (int) alterMove2;
					pushStack(alternativeOrientStack, alterMovePtr2);

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol += 1;
					LASTMOVE = 0;
				} 
				// east, west
				else if(MAZE[curRow][curCol - 1] == 0 && MAZE[curRow][curCol + 1] == 0){
					int* dataPtr3 = (int*)malloc(sizeof(int));
					*dataPtr3 = curRow * 10 + (curCol - 1);
					pushStack(alternativeStack, dataPtr3);

					enum LastMove alterMove1 = 2;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
					
					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol += 1;
					LASTMOVE = 0;
				} 
				// south, west
				else if(MAZE[curRow][curCol - 1] == 0 && MAZE[curRow + 1][curCol] == 0){
					int* dataPtr4 = (int*)malloc(sizeof(int));
					*dataPtr4 = curRow * 10 + (curCol - 1);
					pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove1 = 2;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curRow += 1;
					LASTMOVE = 1;
				} 
				// east, south
				else if(MAZE[curRow + 1][curCol] == 0 && MAZE[curRow][curCol + 1] == 0){
					int* dataPtr4 = (int*)malloc(sizeof(int));
                    *dataPtr4 = (curRow + 1) * 10 + curCol;
                    pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove1 = 1;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
					
					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol += 1;
					LASTMOVE = 0;
				}
				else{ 
					if(MAZE[curRow][curCol + 1] == 0 && LASTMOVE != 2){
						curCol += 1;
						LASTMOVE = 0;
					}
					else if(MAZE[curRow + 1][curCol] == 0 && LASTMOVE != 3){
						curRow += 1;
						LASTMOVE = 1;
					}
					else if(MAZE[curRow][curCol - 1] == 0 && LASTMOVE != 0){
						curCol -= 1;
						LASTMOVE = 2;
					}
					else if(MAZE[curRow - 1][curCol] == 0 && LASTMOVE != 1){
						curRow -= 1;
						LASTMOVE = 3;
					}
					else{
						int* branchPoint = popStack(visitedStack);
						do{
							curCol = *branchPoint % 10;
							curRow = *branchPoint / 10;
							printf("%d row,  %d col (Backtracking)\n", curRow + 1, curCol + 1);
							branchPoint = popStack(visitedStack);
						} while (*branchPoint != -1);
						
						int* newBranch = popStack(alternativeStack);
						curCol = *newBranch % 10;
						curRow = *newBranch / 10;
						int* temp = popStack(alternativeOrientStack);
						LASTMOVE = (enum LastMove) *temp;
					}

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = curRow * 10 + curCol;
					pushStack(visitedStack, dataPtr);
				}

				break;
			case 2:
				// north, west, south
				if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol - 1] == 0 && MAZE[curRow + 1][curCol] == 0){
					int* dataPtr3 = (int*)malloc(sizeof(int));
					*dataPtr3 = curRow * 10 + (curCol - 1);
					pushStack(alternativeStack, dataPtr3);

					enum LastMove alterMove1 = 2;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
							
					int* dataPtr4 = (int*)malloc(sizeof(int));
					*dataPtr4 = (curRow - 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove2 = 3;
					int* alterMovePtr2 = (int*)malloc(sizeof(int));
					*alterMovePtr2 = (int) alterMove2;
					pushStack(alternativeOrientStack, alterMovePtr2);

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curRow += 1;
					LASTMOVE = 1;
				} 
				// north, west
				else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol - 1] == 0){
					int* dataPtr3 = (int*)malloc(sizeof(int));
					*dataPtr3 = (curRow - 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr3);

					enum LastMove alterMove1 = 3;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
					
					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol -= 1;
					LASTMOVE = 2;
				} 
				// north south
				else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow + 1][curCol] == 0){
					int* dataPtr4 = (int*)malloc(sizeof(int));
					*dataPtr4 = (curRow - 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove1 = 3;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curRow += 1;
					LASTMOVE = 1;
				} 
				// west, south
				else if(MAZE[curRow + 1][curCol] == 0 && MAZE[curRow][curCol - 1] == 0){
					int* dataPtr4 = (int*)malloc(sizeof(int));
                    *dataPtr4 = curRow * 10 + (curCol - 1);
                    pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove1 = 2;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
					
					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curRow += 1;
					LASTMOVE = 1;
				}
				else{ 
					if(MAZE[curRow][curCol + 1] == 0 && LASTMOVE != 2){
						curCol += 1;
						LASTMOVE = 0;
					}
					else if(MAZE[curRow + 1][curCol] == 0 && LASTMOVE != 3){
						curRow += 1;
						LASTMOVE = 1;
					}
					else if(MAZE[curRow][curCol - 1] == 0 && LASTMOVE != 0){
						curCol -= 1;
						LASTMOVE = 2;
					}
					else if(MAZE[curRow - 1][curCol] == 0 && LASTMOVE != 1){
						curRow -= 1;
						LASTMOVE = 3;
					}
					else{
						int* branchPoint = popStack(visitedStack);
						do{
							curCol = *branchPoint % 10;
							curRow = *branchPoint / 10;
							printf("%d row,  %d col (Backtracking)\n", curRow + 1, curCol + 1);
							branchPoint = popStack(visitedStack);	
						} while (*branchPoint != -1);

						int* newBranch = popStack(alternativeStack);
						curCol = *newBranch % 10;
						curRow = *newBranch / 10;
						int* temp = popStack(alternativeOrientStack);
						LASTMOVE = (enum LastMove) *temp;
					}

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = curRow * 10 + curCol;
					pushStack(visitedStack, dataPtr);
				}
				
				break;
			case 3:
				// east, north, west
				if(MAZE[curRow][curCol - 1] == 0 && MAZE[curRow][curCol + 1] == 0 && MAZE[curRow - 1][curCol] == 0){
					int* dataPtr3 = (int*)malloc(sizeof(int));
					*dataPtr3 = curRow * 10 + (curCol - 1);
					pushStack(alternativeStack, dataPtr3);

					enum LastMove alterMove1 = 2;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
							
					int* dataPtr4 = (int*)malloc(sizeof(int));
					*dataPtr4 = (curRow - 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove2 = 3;
					int* alterMovePtr2 = (int*)malloc(sizeof(int));
					*alterMovePtr2 = (int) alterMove2;
					pushStack(alternativeOrientStack, alterMovePtr2);

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol += 1;
					LASTMOVE = 0;
				} 
				// east, north
				else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol + 1] == 0){
					int* dataPtr3 = (int*)malloc(sizeof(int));
					*dataPtr3 = (curRow - 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr3);

					enum LastMove alterMove1 = 3;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
					
					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol += 1;
					LASTMOVE = 0;
				} 
				// north, west
				else if(MAZE[curRow - 1][curCol] == 0 && MAZE[curRow][curCol - 1] == 0){
					int* dataPtr4 = (int*)malloc(sizeof(int));
					*dataPtr4 = (curRow - 1) * 10 + curCol;
					pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove1 = 3;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol -= 1;
					LASTMOVE = 2;
				} 
				// west, east
				else if(MAZE[curRow][curCol - 1] == 0 && MAZE[curRow][curCol + 1] == 0){
					int* dataPtr4 = (int*)malloc(sizeof(int));
                    *dataPtr4 = curRow * 10 + (curCol - 1);
                    pushStack(alternativeStack, dataPtr4);

					enum LastMove alterMove1 = 2;
					int* alterMovePtr1 = (int*)malloc(sizeof(int));
					*alterMovePtr1 = (int) alterMove1;
					pushStack(alternativeOrientStack, alterMovePtr1);
					
					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = -1;
					pushStack(visitedStack, dataPtr);

					curCol += 1;
					LASTMOVE = 0;
				}
				else{ 
					if(MAZE[curRow][curCol + 1] == 0 && LASTMOVE != 2){
						curCol += 1;
						LASTMOVE = 0;
					}
					else if(MAZE[curRow + 1][curCol] == 0 && LASTMOVE != 3){
						curRow += 1;
						LASTMOVE = 1;
					}
					else if(MAZE[curRow][curCol - 1] == 0 && LASTMOVE != 0){
						curCol -= 1;
						LASTMOVE = 2;
					}
					else if(MAZE[curRow - 1][curCol] == 0 && LASTMOVE != 1){
						curRow -= 1;
						LASTMOVE = 3;
					}
					else{
						int* branchPoint = popStack(visitedStack);
						do{
							curCol = *branchPoint % 10;
							curRow = *branchPoint / 10;
							printf("%d row,  %d col (Backtracking)\n", curRow + 1, curCol + 1);
							branchPoint = popStack(visitedStack);
						} while (*branchPoint != -1);

						int* newBranch = popStack(alternativeStack);
						curCol = *newBranch % 10;
						curRow = *newBranch / 10;
						int* temp = popStack(alternativeOrientStack);
						LASTMOVE = (enum LastMove) *temp;
					}

					dataPtr = (int*)malloc(sizeof(int));
					*dataPtr = curRow * 10 + curCol;
					pushStack(visitedStack, dataPtr);
				}

				break;
			default:
				printf("Something is going wrong.\n");	
		}

		printf("%d row,  %d col\n", curRow + 1, curCol + 1);
	}

	printf("Over!\n");
	
	return 0;
}
