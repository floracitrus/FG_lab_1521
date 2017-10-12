#!/bin/bash

make clean > /dev/null
make -f Makefile.debug > /dev/null

./vmsim lru 5 4 < trace1 > out-lru-5-4-trace1.out
./vmsim fifo 5 4 < trace1 > out-fifo-5-4-trace1.out
./vmsim lru 8 4 < trace2 > out-lru-8-4-trace2.out
./vmsim fifo 8 4 < trace2 > out-fifo-8-4-trace2.out

if [[ $# -ne 0 ]]
then
    diff -y out-lru-5-4-trace1.txt out-lru-5-4-trace1.out
    diff -y out-fifo-5-4-trace1.txt out-fifo-5-4-trace1.out
    diff -y out-lru-8-4-trace2.txt out-lru-8-4-trace2.out
    diff -y out-fifo-8-4-trace2.txt out-fifo-8-4-trace2.out
fi

if [[ $# -eq 0 ]]
then
    diff out-lru-5-4-trace1.txt out-lru-5-4-trace1.out | wc -l
    diff out-fifo-5-4-trace1.txt out-fifo-5-4-trace1.out | wc -l
    diff out-lru-8-4-trace2.txt out-lru-8-4-trace2.out | wc -l
    diff out-fifo-8-4-trace2.txt out-fifo-8-4-trace2.out | wc -l
fi

rm *.out
