#include <stdio.h>
#include "HW3_ADT/stacksADT.h"

bool** drawMaze(int, int);
const int SIZE_ROW = 10;
const int SIZE_COL = 12;
	

int main(){
	bool** maze = drawMaze();
	
	for(int i = 0; i < SIZE_ROW; i++){
		for(int j = 0; j < SIZE_COL; j++)
			printf("%d ", maze[i][j]);
		printf("\n");
	}
	
	STACK* visitedStack; 
	STACK* alternativeStack;
	int* dataPtr1;
	int* dataPtr2;

	visitedStack = createStack();
	alternativeStack = createStack();

	


	return 0;
}

bool** drawMaze(){
	bool maze[SIEZ_ROW][SIZE_COL] = {
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

	return maze;
}
