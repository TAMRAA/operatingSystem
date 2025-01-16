#!/bin/bash

# Takes two integers n1 and n2 from cmd
# otherwise reads them from stdin

if [ $# -lt 2 ];
then
    echo -n "Insert n1 and n2 in order =>  "
    read n1 n2
else
    n1=$1
    n2=$2
fi

let print=0

for i in $(seq 1 $n1) # Outer loop for rows
do
    for j in $(seq 1 $n2) # Inner loop for columns
    do
        # Print value on the same line
        printf "%d " $print
        print=$((print + 1))
    done
    # Newline after each row
    echo
done
