#!/bin/sh

g++ gen.cpp -ogen.e --std=c++0x -O2
g++ sol.cpp -osol.e --std=c++0x -O2
./gen.e
for i in `seq 1 3`; do
    for j in a b c d e f g h i; do
        n=`printf %02d $i`;
        echo Output for $n.$j...
        ./sol.e < test/$n.$j.in > test/$n.$j.out;
    done
done
