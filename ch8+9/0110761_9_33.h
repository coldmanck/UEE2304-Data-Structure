#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

typedef struct
{
   void** heapAry;
   int    last;
   int    size;
   int    (*compare) (void* argu1, void* argu2);
   int    maxSize;
} HEAP;

HEAP* heapCreate (int maxSize,
            int (*compare) (void* arg1, void* arg2));
bool  heapInsert  (HEAP* heap, void*  dataPtr);
bool  heapDelete  (HEAP* heap, void** dataOutPtr);

static void _reheapUp   (HEAP* heap, int childLoc);
static void _reheapDown (HEAP* heap, int root);

HEAP* heapCreate (int maxSize,
                  int  (*compare) (void* argu1, void* argu2))
{
//	Local Definitions
	HEAP* heap;

//	Statements 
	heap = (HEAP*)malloc(sizeof (HEAP));
	if (!heap)
	   return NULL;

	heap->last    = -1;
	heap->compare = compare;

	// Force heap size to power of 2 -1
	heap->maxSize = (int) pow (2, ceil(log2(maxSize))) - 1;
	heap->heapAry = (void**) calloc(heap->maxSize, sizeof(void*));
	return heap;
}	// createHeap 

bool heapInsert (HEAP* heap, void* dataPtr)
{
//	Statements 
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
	_reheapUp (heap, heap->last);
	return true;
}	// heapInsert

void  _reheapUp  (HEAP* heap, int childLoc)
{
//	Local Definitions 
	int    parent;
	void** heapAry;
	void*  hold;

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
	        _reheapUp (heap, parent);
	       } // if heap[] 
	   } // if newNode 
	return;
}	// reheapUp 

bool heapDelete (HEAP* heap, void** dataOutPtr)
{
//	Statements 
	if (heap->size == 0)
	    // heap empty 
	    return false;
	*dataOutPtr = heap->heapAry[0];
	heap->heapAry[0]  = heap->heapAry[heap->last];
	(heap->last)--;
	(heap->size)--;
	_reheapDown (heap, 0);
	return true;
}	// heapDelete 

void _reheapDown (HEAP* heap, int root)
{
//	Local Definitions 
	void* hold;
	void* leftData;
	void* rightData;
	int   largeLoc;
	int   last;
	
//	Statements 
	last = heap->last;
	if ((root * 2 + 1) <= last)         // left subtree
	    // There is at least one child 
	   {
	    leftData   = heap->heapAry[root * 2 + 1];
	    if ((root * 2 + 2) <= last)  // right subtree 
	       rightData = heap->heapAry[root * 2 + 2];
	    else
	       rightData = NULL;
	       
	    // Determine which child is larger 
	    if ((!rightData) 
	         || heap->compare (leftData, rightData) > 0)
	       {
	        largeLoc = root * 2 + 1;
	       } // if no right key or leftKey greater
	    else
	       {
	        largeLoc = root * 2 + 2;
	       } // else 
	    // Test if root > larger subtree 
	    if (heap->compare (heap->heapAry[root], 
	        heap->heapAry[largeLoc]) < 0)
	        {
	         // parent < children 
	         hold                = heap->heapAry[root]; 
	         heap->heapAry[root] = heap->heapAry[largeLoc];
	         heap->heapAry[largeLoc] = hold;
	         _reheapDown (heap, largeLoc);
	        } // if root < 
	} // if root 
	return;
}	// reheapDown 