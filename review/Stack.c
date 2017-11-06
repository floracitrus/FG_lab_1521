// Stack.c ... Stack ADT implementation
// - uses linked list representation
// Written by JOhn Shepherd, July 2017

#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// internal data types
typedef struct _stackNode StackNode;

struct _stackNode {
   char val;         // value of item
   StackNode *next;  // ptr to next item
};

// concrete representation of Stack
struct _stackRep {
   StackNode *items;  // linked list
   int nitems;        // counter
};

// create a new stack
Stack makeStack(void)
{
   struct _stackRep *new;
   new = malloc(sizeof (struct _stackRep));
   if (new == NULL) {
      fprintf(stderr, "Out of memory\n");
      exit(EXIT_FAILURE);
   }
   new->items = NULL;
   new->nitems = 0;
   return new;   
}

// add new item to stack
void pushStack(Stack s, char item)
{
   StackNode * new;
   new = malloc(sizeof(StackNode));
   if (new == NULL) {
      fprintf(stderr, "Out of memory\n");
      return; // how would the user know
              // that the push() failed?
   }
   new->val = item;
   new->next = s->items;
   s->items = new;
   s->nitems++;
}

// remove top item from stack and return it
char popStack(Stack s)
{
   //assert(s->items != NULL);
   if (s->items == NULL) {
      fprintf(stderr, "Pop empty stack\n");
      return -1;
   }
   StackNode *old;
   old = s->items;
   s->items = old->next;
   int val = old->val;
   free(old);
   s->nitems--;
   return val;
}

// return true if stack is empty
int isEmptyStack(Stack s)
{
   return (s->items == NULL);
//OR
// return (s->nitems == 0);
}

// return number elements in stack
int sizeOfStack(Stack s)
{
   return s->nitems;
}

// free a stack
void freeStack(Stack s)
{
   StackNode *cur;
   cur = s->items;
   while (cur != NULL) {
      free(cur);
      cur = cur->next;
   }
   free(s);
}

//display contents of stack
void showStack(Stack s)
{
   StackNode *cur;
   cur = s->items;
   printf("Top");
   while (cur != NULL) {
      printf(" %c", cur->val);
      cur = cur->next;
   }
   printf("\n");
}





// All functions assume stack_t value is valid

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

// typedef struct stack *stack_t;

#define MAX 2048

struct stack {
    int elements[MAX];  // space to store stack items
    int top;            // index of next elem to use 
                        // also functions as a counter
};

// create a new stack
stack_t create(void)
{
     struct stack *new;
     new = malloc(sizeof (struct stack));
     if (new == NULL) {
         fprintf(stderr,"Out of memory\n");
         exit(EXIT_FAILURE);
     }
     new->top = 0;
     return new;
}

// add new item to stack
void push(stack_t stack, int item)
{
    assert(stack != NULL);
    if (stack->top == MAX) {
        fprintf(stderr,"Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->elements[stack->top] = item;
    stack->top++;
}

// remove top item from stack and return it
int pop(stack_t stack)
{
    int val;  // return value
    
    assert(stack != NULL);
    if (stack->top == 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    val = stack->elements[stack->top-1];
    stack->top--;
    return val;
}

// return true if stack is empty
int is_empty(stack_t stack)
{
    return (stack->top == 0);
}

// return top item from stack but don't remove it
int top(stack_t stack)
{ 
    if (stack->top == 0) {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    return stack->elements[stack->top-1];
}

// return number elements in stack
int size(stack_t stack)
{
    return (stack->top);
}

// free a stack
void destroy(stack_t stack)
{
    free(stack);
}

//display contents of stack
void show(stack_t stack)
{
     int i;
     printf("Stack:");
     for (i = 0; i < stack->top; i++) {
         printf(" %d",stack->elements[i]);
         if (i < stack->top-1) printf(",");
     }
     printf(" TOP\n");
}