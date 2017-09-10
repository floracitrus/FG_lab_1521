// Interface to ADT for Numbers bit-strings
// COMP1521 17s2 Week02 Lab Exercise
// Written by John Shepherd, July 2017

#ifndef QUEUE_H
#define QUEUE_H

typedef struct NumbersRep *Numbers;

// make a new zero'd Numbers with N bits
Numbers makeNumbers(int N);
// release space used by Numbers
void  freeNumbers(Numbers b);
// bit-wise AND of two Numbers a, b
void andNumbers(Numbers a, Numbers b, Numbers res);
// bit-wise OR of two Numbers a, b
void orNumbers(Numbers a, Numbers b, Numbers res);
// bit-wise negation of Numbers a
void invertNumbers(Numbers a, Numbers res);
// left shift by N bit positions
void leftShiftNumbers(Numbers b, int N, Numbers res);
// right shift by N bit positions
void rightShiftNumbers(Numbers b, int N, Numbers res);
// copy value from one Numbers object to another
void setNumbersFromNumbers(Numbers from, Numbers to);
// set Numbers from a string of 0's and 1's
void setNumbersFromString(Numbers b, char *str);
// display Numbers as sequence of 0's and 1's
void showNumbers(Numbers b);

#endif
