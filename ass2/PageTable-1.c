// PageTable.c ... implementation of Page Table operations
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017

#include <stdlib.h>
#include <stdio.h>
#include "Memory.h"
#include "Stats.h"
//#include <assert.h>
#include "PageTable.h"
// Symbolic constants

#define NOT_USED 0
#define IN_MEMORY 1
#define ON_DISK 2

// PTE = Page Table Entry
typedef struct PTE PTE;
//typedef struct QRep *Queue;

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


// The virtual address space of the process is managed
//  by an array of Page Table Entries (PTEs)
// The Page Table is not directly accessible outside
//  this file (hence the static declaration)

static PTE *PageTable;      // array of page table entries
static int nPages;         // # entries in page table
static int replacePolicy;  // how to do page replacement

static PTE *head;      // head of queue
static PTE *tail;      // tail of queue


// Forward refs for private functions
//find the victim
static int findVictim(int);

//append queue node pointer (PTE*) at tail
void QueueAppend(PTE*) ;

//leave the queue node pointer (PTE*) from head
int QueueLeave();

//delete from the middle of list and then append to tail
void reOrder(PTE*);

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

   head = NULL;
   tail = NULL;

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
      QueueAppend(p);

      break;
   case IN_MEMORY:
      countPageHit();
      //if in memory then the lruQueue need to reOrder
      //and put the latest used to the tail
      if(replacePolicy == REPL_LRU)
         reOrder(p);

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
      victim = QueueLeave();

      //printf("victim is %d\n",victim);
      break;
   case REPL_FIFO:
      // TODO: implement FIFO strategy
      victim = QueueLeave();

      //printf("victim is %d\n",victim);
      break;
   case REPL_CLOCK:
      return 0;
   }
   return victim;
}


//tail is the latest used in lru situation
void QueueAppend(PTE* new)
{
   if(head == NULL){
      head = new;
   }
   if(tail != NULL){
      tail->next = new;
      new->prev = tail;
   }
   tail = new;
}

//leave the queue from head
int QueueLeave()
{

   PTE * old = head;
   int pno = old->pageNo;

   head = old->next;
   head->prev = NULL;
   old->next = NULL;

   if(head == NULL)
      tail = NULL;
   return pno;

}
//reOrder the queue to satisfied O(1) complexity
void reOrder(PTE * new)
{
   if(tail == NULL && head == NULL)
      return;
   //if this queue only have one, then do nothing
   if(new == head && new == tail)
      return;

   if(new != tail){
      PTE* prev = new->prev;
      PTE* next = new->next;
      if(prev!=NULL)
         prev->next = next;
      else
         head = next;

      if(next!=NULL)
         next->prev = prev;
      tail->next = new;
      new->prev = tail;
      tail = new;
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

