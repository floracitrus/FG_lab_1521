#ifndef QUEUE_H
#define QUEUE_H
 
typedef struct QueueRep *Queue;
 
// create a new empty Queue
Queue makeQueue();
// delete memory associated with a Queue
void freeQueue(Queue);
 // insert a new item at the tail of the Queue
 void enterQueue(Queue, int);
 // remove/return the item at the head of the Queue
 int leaveQueue(Queue);
 // return the number of items currently in the Queue
 int lengthQueue(Queue);
  
#endif