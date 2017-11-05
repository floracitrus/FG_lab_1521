#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"
 
#define MAXQ 6
 
struct QueueRep {
	int nitems;
 	int head;
 	int tail;
 	int items[MAXQ];
};

Queue makeQueue(){
 	Queue q;
	q = malloc(sizeof(struct QueueRep));
 	assert(q != NULL);
 	q->nitems = q->head = q->tail = 0;
 	return q;
}
  
 void freeQueue(Queue q)
 {
   assert(q != NULL);
   free(q);
 }
void enterQueue(Queue q, int item){
   assert(q->nitems < MAXQ);
   if (q->nitems != 0){
      q->tail =  (q->tail+1)%MAXQ;
   }
   q->items[q->tail] = item;
   q->nitems++;
}  

 //void enterQueue(Queue q, int item)
 //{
 //  assert(q->nitems < MAXQ);
 //  if (q->nitems != 0)
 //  q->tail = (q->tail + 1) % MAXQ; 
 //  //q->tail is the number of the last array so q->tail+1 but also notice that should be included in modulus //Max number of Queue
 //  q->items[q->tail] = item;
 //  
 //  q->nitems++;
 //}
  
 int leaveQueue(Queue q)
 {
   assert(q->nitems > 0);
   int old = q->items[q->head];
   q->head = (q->head + 1) % MAXQ;
   q->nitems--;
   return old;
 }

//void enqueue(struct circqueue *q,int x) {
//
//   if(isfullqueue(q))
//      printf("queue overflow\n");
//   else{
//      q->rear=(q->rear+1)%q->capacity;
//      q->array[q->rear]=x;
//      if(q->front==-1) {
//         q->front=q->rear;
//      }
//   }
//}
//
//int dequeue(struct circqueue *q) {
//   int data=0;
//
//   if(isemptyqueue(q)) {
//      printf("queue underflow");
//      return 0;
//   }
//   else {
//      data=q->array[q->front];
//      if(q->front==q->rear)
//         q->front=q->rear=-1;
//      else
//         q->front=(q->front+1)%q->capacity;
//   }
//
//   return data;
//}
 int lengthQueue(Queue q)
 {
   return q->nitems;
 }
  
 void showQueue(Queue q)
 {
   int n; // counter
   int i; // index
   printf("H");
   i = q->head;
   for (n = 0; n < q->nitems; n++) {
      printf(" %d", q->items[i]);
      i = (i + 1) % MAXQ;
   }
   printf(" T");
   printf(" h=%d, t=%d, n=%d\n", q->head, q->tail, q->nitems);
 }
int main(void){
   Queue q=makeQueue();
   enterQueue(q, 6);
   enterQueue(q, 5);
   enterQueue(q, 4);
   enterQueue(q, 3);
   enterQueue(q, 2);
   enterQueue(q, 1);
   showQueue(q);
   leaveQueue(q);
   showQueue(q);
   leaveQueue(q);
   showQueue(q);
   enterQueue(q, 0);
   showQueue(q);
   leaveQueue(q);
   showQueue(q);

}


/** sliding array
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"
 
#define MAXQ 6
 
struct QueueRep {
   int nitems;
   int head;
   int tail;
   int items[MAXQ];
};
 
Queue makeQueue()
{
   Queue q;
   q = malloc(sizeof(struct QueueRep));
   assert(q != NULL);
   q->nitems = q->head = q->tail = 0;
   return q;
}
 
void  freeQueue(Queue q)
{
   assert(q != NULL);
   free(q);
}
 
void  enterQueue(Queue q, int item)
{
   assert(q->nitems < MAXQ);
   if (q->nitems != 0) q->tail++;
   q->items[q->tail] = item;
   q->nitems++;
}
 
int   leaveQueue(Queue q)
{
   assert(q->nitems > 0);
   int old = q->items[q->head];
   for (int i = 0; i < q->nitems-1; i++)
      q->items[i] = q->items[i+1];
   q->tail--;
   q->nitems--;
   return old;
}
 
int   lengthQueue(Queue q)
{
   return q->nitems;
}
 
void showQueue(Queue q)
{
   int n; // counter
   int i; // index
   printf("H");
   i = q->head;
   for (n = 0; n < q->nitems; n++) {
      printf(" %d", q->items[i]);
      i = (i + 1) % MAXQ;
   }
   printf(" T");
   printf("   h=%d, t=%d, n=%d\n", q->head, q->tail, q->nitems);
}
 


**/


