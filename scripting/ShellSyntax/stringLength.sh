#!/bin/bash
# String length
echo -e "Input a word: "
read word
# echoing without newline | word count chars
l=$(echo -n $word | wc -c)
echo "Word $word is =>$l characters long"
exit 0