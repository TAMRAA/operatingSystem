#!/bin/bash

# Version 1 => dealing with the arguments

# the number of arguments less than 1
if [ $# -lt 1 ]; then
    echo "Run: script dir file1 file2 ... fileN"
    exit 1
fi

# the directory !exist 
# This whole code can be substituted by => mkdir -p $1 => if exist do nothing => if not create new dir :)
if [ ! -d $1 ]; then
    echo "Creating new directory..."
    mkdir $1
    echo "$1 is created successfully :)"
fi

# $* => all the elements => $1 ... $n
for i in $*
do
    # not in first argument
    if [ $i != $1 ];
    then
        echo -n "$i in $1 (y/n)? "
        read choice
    fi

    if [ "$choice" = "y" ]; then
        # copy file into directory
        cp $i $1
    fi
done
exit 0


# Version 2 => Solving first argument problem

dir=$1

shift # Shifting to the left cancel out the directory name

for i in $*;
do
    echo -n "$i in $dir (y/n)?:  "
    read choice
    
    if [ $choice = "y"]; then
        if cp $i $dir
        then
            echo "Copy done for $dir/$i"
        else
            echo "Error copying $i"
        fi
    fi
done

exit 0