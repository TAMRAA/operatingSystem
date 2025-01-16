a=30
b=20

if [ $a == $b ]
then
    echo "a is equal to b :)"
elif [ $a -gt $b ] ## -gt => greater than
then
    echo "a greater than b :)"
else
    echo "a is less than b :)"
fi
