# Write a bash script that displays the content of
# 1) All files of the current directory
# 2) With ".c" extension
# 3) That include string "POSIX"

# find the files with .c Extension
for file in $(ls *.c);

do
    # grab without output the file that has "POSIX" string
    grep --quiet "POSIX" $file
    
    # Return is true
    if [ $? -eq 0 ]
    then
        cat $file
    fi

done

exit 0