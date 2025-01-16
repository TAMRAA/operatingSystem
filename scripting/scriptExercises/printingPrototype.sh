#!/bin/bash
# Read a file word-by-word
# Read line-by-line
# Read character-by-character
 

# Word by word
for i in $(cat $1) ;
do
    echo "WORD: $i"
done

echo

# done > file_out.txt  # If I would like to redirect the output
# on the file "file_out.txt"
 
 
# Line by line
 
# Line by line
while read line;
do
  echo "LINE: $line"
done < $1

echo


# done < $1 > file_out.txt      
# If I would like to redirect the output on the file "file_out.txt"
 
# Character by character
while read -n 1 i ;
do
      echo "CHAR: $i"
done < $1

echo

