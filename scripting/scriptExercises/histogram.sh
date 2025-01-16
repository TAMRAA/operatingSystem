#!/bin/bash

for n in $(cat $1);
do
    i=1
    while [ $i -le $n ];
    do
        echo -n "*"
        let i=i+1
    done
    echo
done

exit 0
