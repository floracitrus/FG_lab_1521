// PageTable.c ... implementation of Page Table operations
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017

#include <stdlib.h>
#include <stdio.h>
#include "Memory.h"
#include "Stats.h"
#include "PageTable.h"
// Symbolic constants

#define NOT_USED 0
#define IN_MEMORY 1
#define ON_DISK 2

// PTE = Page Table Entry
typedef struct PTE PTE;
typedef struct QRep *Queue;

struct PTE {
   char status;      // NOT_USED, IN_MEMORY, ON_DISK
   char modified;    // boolean: changed since loaded
   int  frame;       // memory frame holding this page
   int  accessTime;  // clock tick for last access
   int  loadTime;    // clock tick for last time loaded
   int  nPeeks;      // total number times this page read
   int  nPokes;      // total number times this page modified
   int pageNo;       // the page number this page table maintained
   PTE *next;        // the next pointer
   PTE *prev;        // the previous pointer
};

typedef struct QRep {
   PTE * head;       // a queue representation
   PTE * tail;       // with head and tail
}QRep;

// The virtual address space of the process is managed
//  by an array of Page Table Entries (PTEs)
// The Page Table is not directly accessible outside
//  this file (hence the static declaration)

static PTE *PageTable;      // array of page table entries
static int nPages;         // # entries in page table
static int replacePolicy;  // how to do page replacement

static Queue fifoQueue;     // the first in first out queue;
static Queue lruQueue;      // the least recently used queue;


Queue newQueue()
{
   Queue q = malloc(sizeof(QRep));
   q->head = NULL;
   q->tail = NULL;
   return q;
}

// Forward refs for private functions
//find the victim
static int findVictim(int);

//append queue node(PTE) at tail
void QueueAppend(Queue, PTE*) ;

//leave the queue node(PTE) from head
int QueueLeave(Queue);

//delete from the middle of list and then append to tail
void reOrder(Queue, PTE*);

// initPageTable: create/initialise Page Table data structures
void initPageTable(int policy, int np)
{
   PageTable = malloc(np * sizeof(PTE));
   if (PageTable == NULL) {
      fprintf(stderr, "Can't initialise Memory\n");
      exit(EXIT_FAILURE);
   }
   replacePolicy = policy;
   nPages = np;
   fifoQueue = newQueue();
   lruQueue = newQueue();

   for (int i = 0; i < nPages; i++) {
      PTE *p = &PageTable[i];
      p->status = NOT_USED;
      p->modified = 0;
      p->frame = NONE;
      p->accessTime = NONE;
      p->loadTime = NONE;
      p->nPeeks = p->nPokes = 0;
      p->pageNo = i;
      p->prev = NULL;
      p->next = NULL;
   }
}

// requestPage: request access to page pno in mode
// returns memory frame holding this page
// page may have to be loaded
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

int requestPage(int pno, char mode, int time)
{
   if (pno < 0 || pno >= nPages) {
      fprintf(stderr,"Invalid page reference\n");
      exit(EXIT_FAILURE);
   }
   PTE *p = &PageTable[pno];
   int fno; // frame number
   switch (p->status) {
   case NOT_USED:
   case ON_DISK:
      countPageFault();
      fno = findFreeFrame();
      if (fno == NONE) {
         int vno = findVictim(time);
#ifdef DBUG
         printf("Evict page %d\n",vno);
#endif
         PTE *victim_p = &PageTable[vno];
         
         // if victim page modified, save its frame
         if(victim_p->modified != 0)
            saveFrame(fno);
         
         // collect frame# (fno) for victim page
         fno = victim_p->frame;
         
         // update PTE for victim page
         // - new status
         // - no longer modified
         // - no frame mapping
         // - not accessed, not loaded
         victim_p->status = ON_DISK;
         victim_p->modified = 0;
         victim_p->frame = NONE;
         victim_p->accessTime = NONE;
         victim_p->loadTime = NONE;

      }
      printf("Page %d given frame %d\n",pno,fno);
      
      // load page pno into frame fno
      loadFrame(fno, pno, time);
      
      // update PTE for page
      // - new status
      // - not yet modified
      // - associated with frame fno
      // - just loaded
      p->status = IN_MEMORY;
      p->modified = 0;
      p->frame = fno;
      p->loadTime = time;
      
      //lru queue
      if(replacePolicy == REPL_LRU)
         QueueAppend(lruQueue, p);
     
      //fifo queue
      if(replacePolicy == REPL_FIFO)
         QueueAppend(fifoQueue, p);
      
      break;
   case IN_MEMORY:
      countPageHit();
      //if in memory then the lruQueue need to reOrder
      //and put the latest used to the tail
      if(replacePolicy == REPL_LRU)
         reOrder(lruQueue,p);

      break;
   default:
      fprintf(stderr,"Invalid page status\n");
      exit(EXIT_FAILURE);
   }
   if (mode == 'r')
      p->nPeeks++;
   else if (mode == 'w') {
      p->nPokes++;
      p->modified = 1;
   }
   p->accessTime = time;
   return p->frame;
}

// findVictim: find a page to be replaced
// uses the configured replacement policy
static int findVictim(int time)
{
   int victim = 0;
   switch (replacePolicy) {
   case REPL_LRU:
      // TODO: implement LRU strategy
      victim = QueueLeave(lruQueue);
      printf("victim is %d\n",victim);
      break;
   case REPL_FIFO:
      // TODO: implement FIFO strategy
      victim = QueueLeave(fifoQueue);
      printf("victim is %d\n",victim);
      break;
   case REPL_CLOCK:
      return 0;
   }
   return victim;
}


//tail is the latest used
void QueueAppend(Queue q, PTE* new)
{
   if(q->head == NULL){
      q->head = new;
   }
   if(q->tail != NULL){
      q->tail->next = new;
      new->prev = q->tail;
   }
   q->tail = new;
}

//leave the queue from head
int QueueLeave(Queue q)
{  
   //assert(q->head!=NULL)
   PTE * old = q->head;
   int pno = old->pageNo;

   q->head = old->next;
   q->head->prev = NULL;
   old->next = NULL;

   if(q->head == NULL)
      q->tail = NULL;
   return pno;

}
//reOrder the queue to satisfied O(1) complexity
void reOrder(Queue q, PTE * new)
{
   
   //if this queue only have one, then do nothing
   if(new == q->head && new == q->tail)
      return;
   
   if(new != q->tail){
      
      PTE* prev = new->prev;
      PTE* next = new->next;
      if(prev!=NULL)
         prev->next = next;
      else
         q->head = next;

      if(next!=NULL)
         next->prev = prev;
      q->tail->next = new;
      new->prev = q->tail;
      q->tail = new;
      new->next = NULL;
   }
}

// showPageTableStatus: dump page table
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

void showPageTableStatus(void)
{
   char *s;
   printf("%4s %6s %4s %6s %7s %7s %7s %7s\n",
          "Page","Status","Mod?","Frame","Acc(t)","Load(t)","#Peeks","#Pokes");
   for (int i = 0; i < nPages; i++) {
      PTE *p = &PageTable[i];
      printf("[%02d]", i);
      switch (p->status) {
      case NOT_USED:  s = "-"; break;
      case IN_MEMORY: s = "mem"; break;
      case ON_DISK:   s = "disk"; break;
      }
      printf(" %6s", s);
      printf(" %4s", p->modified ? "yes" : "no");
      if (p->frame == NONE)
         printf(" %6s", "-");
      else
         printf(" %6d", p->frame);
      if (p->accessTime == NONE)
         printf(" %7s", "-");
      else
         printf(" %7d", p->accessTime);
      if (p->loadTime == NONE)
         printf(" %7s", "-");
      else
         printf(" %7d", p->loadTime);
      printf(" %7d", p->nPeeks);
      printf(" %7d", p->nPokes);
      printf("\n");
   }
}
