#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>
#include "0110761_9_29.h"

int compare (void*, void*);
int heapInsert2 (HEAP* heap, void*  dataPtr);
int _reheapUp2 (HEAP* heap, int childLoc);
int createHeap(HEAP* heap, int* dataPtr, int size);

int main(){
	srand(time(NULL));

	HEAP* heap;
	int*  dataPtr;
	int process_count;

	process_count = createHeap(heap, dataPtr, 100);
	printf("End of heap of size 100 creation. Total process times = %d\n", process_count);

	process_count = createHeap(heap, dataPtr, 200);
	printf("End of heap of size 200 creation. Total process times = %d\n", process_count);

	process_count = createHeap(heap, dataPtr, 500);
	printf("End of heap of size 500 creation. Total process times = %d\n", process_count);
	
	process_count = createHeap(heap, dataPtr, 1000);
	printf("End of heap of size 1000 creation. Total process times = %d\n", process_count);

	return 0;
}

int compare (void* arg1, void* arg2){
//	Local Declarations 
	int arguOne;
	int arguTwo;
	
//	Statements 
	arguOne = *(int*)arg1;
	arguTwo = *(int*)arg2;

	if (arguOne < arguTwo)
	    return -1;
	else if (arguOne == arguTwo)
	    return  0;
	else
	    return +1;
}

int heapInsert2 (HEAP* heap, void* dataPtr)
{
//	Statements 
	int count = 0;
	if (heap->size == 0)                 // Heap empty
	   {
	    heap->size                = 1;
	    heap->last                = 0;
	    heap->heapAry[heap->last] = dataPtr;
	    return true;
	   } // if
	if (heap->last == heap->maxSize - 1)
	  return false;
	++(heap->last); 
	++(heap->size);
	heap->heapAry[heap->last] = dataPtr;
	return _reheapUp2 (heap, heap->last);
}	// heapInsert 

int  _reheapUp2  (HEAP* heap, int childLoc)
{
//	Local Definitions 
	int    parent;
	void** heapAry;
	void*  hold;
	int count = 1;

//	Statements 
	// if not at root of heap -- index 0 
	if (childLoc)
	   {
	    heapAry = heap->heapAry;
	    parent = (childLoc - 1)/ 2;
	    if (heap->compare(heapAry[childLoc], 
	                      heapAry[parent]) > 0)
	        // child is greater than parent -- swap 
	        {
	         hold             = heapAry[parent]; 
	         heapAry[parent]  = heapAry[childLoc];
	         heapAry[childLoc] = hold;
	         count += _reheapUp2 (heap, parent);
	       } // if heap[] 
	   } // if newNode 
	return count;
}	// reheapUp 

int createHeap(HEAP* heap, int* dataPtr, int size){
	heap = heapCreate (size, compare);
	if (!heap)
	   printf("Can't create heap in main\n"), exit (100);

	// Fill half the heap with random numbers 
	int process_count = 0;
	for (int bldLooper = 0; bldLooper <= size / 2 - 1; bldLooper++){
	     dataPtr  = (int*)malloc(sizeof (int));
	     if (!dataPtr)
	        printf("Overflow in main\n"), exit (101);
	     
	     *dataPtr = rand() % size + 1;
	     process_count += heapInsert2 (heap, dataPtr);
	}

	return process_count;
}
