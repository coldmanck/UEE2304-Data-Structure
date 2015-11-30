#include <stdio.h>
#include "HW3_ADT/stacksADT.h"

const char closMiss[ ] = "Close brace missing at line";
const char openMiss[ ] = "Open brace missing at line";
void checkBraces(char*);

int main (void){
	checkBraces("12.c");
	checkBraces("HW3_3.12_input.txt");

	return 0;
}

void checkBraces(char* fileID){
	STACK* stack;
	char   token;
	int*  dataPtr;		// To store line number in the stack
	//char   fileID[25];
	FILE*  fpIn;
	int    lineCount = 1;

	stack = createStack ();
	//printf ("Enter file ID for file to be parsed: ");
	//scanf  ("%s", fileID);
	
	fpIn = fopen (fileID, "r");
	if (!fpIn)
	    printf("Error opening %s\n", fileID), exit(100);
	
	printf("Checking %s... ", fileID);
	while ((token = fgetc (fpIn)) != EOF ){
	    if (token == '\n')
	       lineCount++;
	    if (token == '{' ){		// detect opening brace
			dataPtr = &lineCount;
	        pushStack (stack, dataPtr);	// push line number
	    }
	    else{
	        if (token == '}'){	// detect closing brace
	            if (emptyStack (stack)){
					// if wrong, print unmatched closing brace
	                printf ("%s %d\n", openMiss, lineCount);	
	                return;
	            }
	            else
	               popStack (stack);
	        }
	    }
	}

	if (!emptyStack (stack)){
	    printf ("%s %d\n", closMiss, lineCount);
	    return;
	}

	destroyStack (stack);
	printf ("Parsing is OK: %d Lines parsed.\n", lineCount);
}
