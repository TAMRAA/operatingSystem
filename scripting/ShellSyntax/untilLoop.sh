a=0

# This condition will become false until value reach 10
until [ ! $a -lt 11 ] 
do
    echo $a
    a=`expr $a + 1`
done

