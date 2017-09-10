//
//  Numbers.c
//  BitOps
//
//  Created by Flora Li on 6/8/17.
//  Copyright © 2017 Flora Li. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Numbers.h"

// assumes that an unsigned int is 32 numbers
#define NUM_PER_WORD 32

// A bit-string is an array of unsigned ints (each a 32-bit Word)
// The number of numbers (hence Words) is determined at creation time
// Words are indexed from right-to-left
// words[0] contains the most significant numbers
// words[nwords-1] contains the least significant numbers
// Within each Word, numbers are indexed right-to-left
// Bit position 0 in the Word is the least significant bit
// Bit position 31 in the Word is the most significant bit

typedef unsigned int Word;

struct NumbersRep {
    int nwords;   // # of Words
    Word *words;  // array of Words
};

// make a new empty Numbers with space for at least nnumbers
// rounds up to nearest multiple of NUM_PER_WORD
Numbers makeNumbers(int nnumbers)
{
    Numbers new;
    new = malloc(sizeof(struct NumbersRep));
    assert(new != NULL);
    int  nwords;
    if (nnumbers%NUM_PER_WORD == 0)
        nwords = nnumbers/NUM_PER_WORD;
    else
        nwords = 1+nnumbers/NUM_PER_WORD;
    new->nwords = nwords;
    // calloc sets to all 0's
    new->words = calloc(nwords, sizeof(Word));
    assert(new->words != NULL);
    return new;
}

// release space used by Numbers
void  freeNumbers(Numbers b)
{
    assert(b != NULL && b->words != NULL);
    free(b->words);
    free(b);
}

// form bit-wise AND of two Numbers a,b
// store result in res Numbers
void andNumbers(Numbers a, Numbers b, Numbers res)
{
    for (int i = 0; i < res->nwords; i++)
        res->words[res->nwords - 1 - i] = a->words[a->nwords - 1 - i] &
        b->words[b->nwords - 1 - i];
}

// form bit-wise OR of two Numbers a,b
// store result in res Numbers
void orNumbers(Numbers a, Numbers b, Numbers res)
{
    for (int i = 0; i < res->nwords; i++)
        res->words[res->nwords - 1 - i] = a->words[a->nwords - 1 - i] |
        b->words[b->nwords - 1 - i];
}

// form bit-wise negation of Numbers a,b
// store result in res Numbers
void invertNumbers(Numbers a, Numbers res)
{
    for (int i = 0; i < res->nwords; i++)
        res->words[i] = ~a->words[i];
}

// left shift Numbers
void leftShiftNumbers(Numbers b, int shift, Numbers res)
{
    Word mask = 0;
    mask = ~mask;
    Word mask2 = 0;
    mask2 = ~mask2;
    mask2 >>=(NUM_PER_WORD-shift);
    for (int i = 0; i < b->nwords; i++){
        mask >>= shift;
        Word temp = b->words[i] & mask2;
        res->words[i] = b->words[i] & mask;
        res->words[i] = (shift<<res->words[i])|(shift >> ((-b->words[i])&mask));
    }
    
}


// right shift Numbers
void rightShiftNumbers(Numbers b, int shift, Numbers res)
{
    for (int i = 0; i < b->nwords; i++)
        res->words[i] = b->words[i] >> shift;
}

// copy value from one Numbers object to another
void setNumbersFromNumbers(Numbers from, Numbers to)
{
    for (int i = 0; i < from->nwords; i++)
        to->words[i] = from->words[i];
}

// assign a bit-string (sequence of 0's and 1's) to Numbers
// if the bit-string is longer than the size of Numbers, truncate higher-order numbers
void setNumbersFromString(Numbers b, char *numberseq)
{
    for (int i = 0; i < b->nwords; i++) b->words[i] = 0;
    for (int i = b->nwords; i > 0; i--) {
        int end = strlen(numberseq) - (b->nwords - i) * NUM_PER_WORD - 1;
        Word power = 1;
        for (int j = 0; j < NUM_PER_WORD; j++) {
            if (end - j >= 0) {
                b->words[i - 1] += (numberseq[end - j] - '0') * power;
                power <<= 1;//it just means 1 2 4 8 16 with each shift left
            } else break;
        }
    }
}

// display a Numbers value as sequence of 0's and 1's
void showNumbers(Numbers b)
{
    for (int i = 0; i < b->nwords; i++) {
        Word mask = 1;
        for (int j = 0; j < NUM_PER_WORD; j++) {
            if (b->words[i] & (mask << (NUM_PER_WORD - j - 1)))
                printf("1");
            else
                printf("0");
        }
    }
}

