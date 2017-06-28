#!/bin/bash

g++ gen.cpp -ogen.e --std=c++0x -O2
g++ sol.cpp -osol.e --std=c++0x -O2
./gen.e
for i in `seq 1 6`; do
    for j in `echo {a..z}`; do
        n=`printf %02d $i`;
        FILE="test/$n.$j.in"
        if [ -f $FILE ]; then
            echo Output for $n.$j...
            ./sol.e < test/$n.$j.in > test/$n.$j.out 2>/dev/null;
        fi
    done
done
