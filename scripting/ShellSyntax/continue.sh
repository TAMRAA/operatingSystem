NUMS="1 2 3 4 5 6 7"
for NUM in $NUMS
do
    Q=`expr $NUM % 2`

    # Q == 0 ?
    if [ $Q -eq 0 ]
    then
        echo "Number is even number :)"
        continue
    fi
    echo "Number is odd Number"

done

