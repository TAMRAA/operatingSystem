#!/bin/bash

echo -n "Insert n => "
read n

i=1
while [ $i -lt $n ];
do
    echo "i = $i"
    i=$((i + 1))  # Using modern $(( )) for arithmetic
done

echo "Thanks for using my app :)"
