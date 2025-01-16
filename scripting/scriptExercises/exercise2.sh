#!/bin/bash
i=0
while [ 0 ];
do
    echo -n "Input $i: "
    read v

if [ "$v" -eq "0" ] ;
then

break;
fi

vet[$i]=$v
let i=i+1

done