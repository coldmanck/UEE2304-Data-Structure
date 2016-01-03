#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#include "0110761_9_33.h"

const int maxQueue = 15;
typedef struct{
	char name[30];
    int mile;
    int year;
    int seq;
    int priority;
 } CUST;

int   compareCust (void* cust1, void* cust2);
void  processPQ   (HEAP* heap);
CUST* getCust(void);

int main(){

	FILE *fp;
	fp = fopen("passenger.txt", "r+");
	
	char name[30], mile[10], year[10], seq[10];

	HEAP* prQueue;
	prQueue = heapCreate(maxQueue, compareCust);
	bool result;

	printf("Start to process guests...\n"); 
	int numCusts = 0;
	while(fscanf(fp, "%s %s %s %s", name, mile, year, seq) == 4){
		// printf("%s, %s\n", name, phone);

		CUST* cust = (CUST*)malloc(sizeof (CUST));
		if (!cust)
			printf("Memory overflow in getCust\n"), exit (200);

		numCusts++;
		strcpy(cust->name, name);
		cust->mile = atoi(mile);
		cust->year = atoi(year);
		cust->seq = atoi(seq);
		cust->priority = cust->mile / 1000 + cust->year + cust->seq;

		result = heapInsert (prQueue, cust);
		if (!result){
			printf("Error inserting into heap\n");
			exit (101);
		}
	};
	fclose(fp);
	printf("Finish build priority queue. There're %d guests.\n", numCusts);

	printf("name\tpriority\n");
	CUST* cust2;
	do {
		result = heapDelete (prQueue, (void**)&cust2);
		numCusts--;
	    if (result && (numCusts >= 0)){
	        printf("%s\t%d\n", cust2->name, cust2->priority);
	    }
	    else 
	    	break;
	} while(true);

	return 0;
}

int compareCust (void* cust1, void* cust2){
	CUST c1, c2;

	c1 = *(CUST*)cust1;
	c2 = *(CUST*)cust2;
	
	if (c1.priority < c2.priority)
	    return -1;
	else if (c1.priority == c2.priority)
	    return 0;
	return +1;
}
