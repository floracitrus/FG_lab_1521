//
//  Bits.c
//  BitOps
//
//  Created by Flora Li on 6/8/17.
//  Copyright © 2017 Flora Li. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Bits.h"

// assumes that an unsigned int is 32 bits
#define BITS_PER_WORD 32

// A bit-string is an array of unsigned ints (each a 32-bit Word)
// The number of bits (hence Words) is determined at creation time
// Words are indexed from right-to-left
// words[0] contains the most significant bits
// words[nwords-1] contains the least significant bits
// Within each Word, bits are indexed right-to-left
// Bit position 0 in the Word is the least significant bit
// Bit position 31 in the Word is the most significant bit

typedef unsigned int Word;

struct BitsRep {
    int nwords;   // # of Words
    Word *words;  // array of Words
};

// make a new empty Bits with space for at least nbits
// rounds up to nearest multiple of BITS_PER_WORD
Bits makeBits(int nbits)
{
    Bits new;
    new = malloc(sizeof(struct BitsRep));
    assert(new != NULL);
    int  nwords;
    if (nbits%BITS_PER_WORD == 0)
        nwords = nbits/BITS_PER_WORD;
    else
        nwords = 1+nbits/BITS_PER_WORD;
    new->nwords = nwords;
    // calloc sets to all 0's
    new->words = calloc(nwords, sizeof(Word));
    assert(new->words != NULL);
    return new;
}

// release space used by Bits
void  freeBits(Bits b)
{
    assert(b != NULL && b->words != NULL);
    free(b->words);
    free(b);
}

// form bit-wise AND of two Bits a,b
// store result in res Bits
void andBits(Bits a, Bits b, Bits res)
{
    for (int i = 0; i < res->nwords; i++)
        res->words[res->nwords - 1 - i] = a->words[a->nwords - 1 - i] &
        b->words[b->nwords - 1 - i];
}

// form bit-wise OR of two Bits a,b
// store result in res Bits
void orBits(Bits a, Bits b, Bits res)
{
    for (int i = 0; i < res->nwords; i++)
        res->words[res->nwords - 1 - i] = a->words[a->nwords - 1 - i] |
        b->words[b->nwords - 1 - i];
}

// form bit-wise negation of Bits a,b
// store result in res Bits
void invertBits(Bits a, Bits res)
{
    for (int i = 0; i < res->nwords; i++)
        res->words[i] = ~a->words[i];
}

// left shift Bits
void leftShiftBits(Bits b, int shift, Bits res)
{
    Word mask = 0;
    mask = ~mask;
    Word mask2 = 0;
    mask2 = ~mask2;
    mask2 >>=(BITS_PER_WORD-shift);
    for (int i = 0; i < b->nwords; i++){
        mask >>= shift;
        Word temp = b->words[i] & mask2;
        res->words[i] = b->words[i] & mask;
        res->words[i] = (shift<<res->words[i])|(shift >> ((-b->words[i])&mask));
    }
    
}


    /*Word mask = 0;
    mask = ~mask;
    for (int i = 0; i < b->nwords; i++) {
        mask >>= shift;
        res->words[i] = b->words[i] & mask;
        res->words[i] <<= shift;
    }
    */
    for (int i = 0; i < b->nwords; i++)
        res->words[i] = b->words[i] << shift;
}

// right shift Bits
void rightShiftBits(Bits b, int shift, Bits res)
{
    for (int i = 0; i < b->nwords; i++)
        res->words[i] = b->words[i] >> shift;
}

// copy value from one Bits object to another
void setBitsFromBits(Bits from, Bits to)
{
    for (int i = 0; i < from->nwords; i++)
        to->words[i] = from->words[i];
}

// assign a bit-string (sequence of 0's and 1's) to Bits
// if the bit-string is longer than the size of Bits, truncate higher-order bits
void setBitsFromString(Bits b, char *bitseq)
{
    for (int i = 0; i < b->nwords; i++) b->words[i] = 0;
    for (int i = b->nwords; i > 0; i--) {
        int end = strlen(bitseq) - (b->nwords - i) * BITS_PER_WORD - 1;
        Word power = 1;
        for (int j = 0; j < BITS_PER_WORD; j++) {
            if (end - j >= 0) {
                b->words[i - 1] += (bitseq[end - j] - '0') * power;
                power <<= 1;//it just means 1 2 4 8 16 with each shift left
            } else break;
        }
    }
}

// display a Bits value as sequence of 0's and 1's
void showBits(Bits b)
{
    for (int i = 0; i < b->nwords; i++) {
        Word mask = 1;
        for (int j = 0; j < BITS_PER_WORD; j++) {
            if (b->words[i] & (mask << (BITS_PER_WORD - j - 1)))
                printf("1");
            else
                printf("0");
        }
    }
}

