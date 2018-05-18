#!/bin/sh

[[ "$#" -lt 1 ]] && exit

spin -a "$1"
gcc -o pan pan.c
./pan -a -m2000 -X
rm pan* *.tmp *.trail &> /dev/null
