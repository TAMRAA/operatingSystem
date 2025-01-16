#!/bin/bash
n=1

while read line;     # Read a line
do
        # num of Line: content of the line
        echo "$n: $line"
        let n=n+1
done <$1           # Take $1 and provide it as input to the While loop => Redirection

n=1

 # Read a word only
for str in "cat $1";
do
    echo "$n: $str"
    let n=n+1
done

# Word-by-word processing
for str in $(cat $1);
do
    echo "$n: $str"
    let n=n+1
done