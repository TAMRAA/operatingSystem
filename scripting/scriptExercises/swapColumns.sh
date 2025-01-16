#!/bin/bash
# app that flip the content of a file

file="tmp"

while read var1 var2;
do
    echo "$var2 $var1"
done <$1 >$file

mv -f $file $1

exit 0
