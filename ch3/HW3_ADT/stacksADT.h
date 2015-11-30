//	Header file for stack ADT.

#include <stdlib.h>
#include <stdbool.h>

#include "P3-06.h"		/* Stack ADT Definitions */

/*	ADT Prototype Declarations */
STACK* createStack  (void);
bool   pushStack    (STACK* stack, void* dataInPtr);
void*  popStack     (STACK* stack);
void*  stackTop     (STACK* stack);
bool   emptyStack   (STACK* stack);
bool   fullStack    (STACK* stack);
int    stackCount   (STACK* stack);
STACK* destroyStack (STACK* stack);

#include "P3-07.h"		/* Create Stack */
#include "P3-08.h"		/* Push Stack */
#include "P3-09.h"		/* Pop Stack */
#include "P3-10.h"		/* Retrieve Stack Top */
#include "P3-11.h"		/* Empty Stack */
#include "P3-12.h"		/* Full Stack */
#include "P3-13.h"		/* Stack Count */
#include "P3-14.h"		/* DestroyStack */
