#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "0110761_4_25.h"

const int INTERVAL = 1440;
const int PROCESS_MSG = 40;
const int ARRIVAL_MSG = 30;
const double LOST_MSG_RATE = 0.25;

int main(){

	int msgTotalAmount = 0;
	int msgSent = 0;
	int msgInQueue = 0;
	int msgSentEachAttempt[1440] = {0};
	int requeueTimes = 0;
	int msgInQueueTotal = 0;
	double msgInQueueAvg = 0.0;
	srand(time(NULL));

	QUEUE* q = createQueue();

	for(int i = 0; i < INTERVAL; i++){
		int msgSentBefore = msgSent;
		
		// Enqueue
		for(int j = 0; j < ARRIVAL_MSG; j++){
			int* data; 
			*data = i * 10 + j;
			enqueue(q, data);
			msgInQueue++;
		}

		// Dequeue and send
		for(int j = 0; j < PROCESS_MSG; j++){
 			if(emptyQueue(q))
 				break;

			int lost = rand()%4;
			int* data = new int;
			
			if(lost == 3){
				dequeue(q, (void**) &data);
				enqueue(q, data);
				requeueTimes++;
			}
			else{
				dequeue(q, (void**) &data);
				msgSent++;
				msgInQueue--;
			}

			msgTotalAmount++;
			
		}

		msgSentEachAttempt[i] = msgSent - msgSentBefore;
		printf("MSG sent each attempt: %d\n", msgSentEachAttempt[i]);
		msgInQueueTotal += msgInQueue;
	}

	printf("-------- Final Report --------\n");
	printf("Total process time: 24 hours = 1440 minutes\n");
	printf("Total messages processed: %d\n", msgTotalAmount);
	printf("Average number of messages sent per minute: %lf\n", (double)msgSent / INTERVAL);
	printf("Average number of messages in the queue in a minute: %lf\n", (double)msgInQueueTotal / INTERVAL);
	printf("Average number of times messages had to be requeued: %lf\n", (double)requeueTimes / msgTotalAmount);

	return 0;
}