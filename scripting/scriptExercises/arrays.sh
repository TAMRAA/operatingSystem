#!/bin/bash
# Example of use of the BASH arrays (and associative arrays)
 
# Classical array
echo "Classical array"

vett2[3]=pasta
vett2[6]=bread

echo ${vett2[3]}  # Prints pasta
echo ${#vett2[*]} # Prints 2
echo ${vett2[*]}  # Prints bread pasta
echo ${!vett2[*]} # Prints 3 6
 
 
# Associative array
echo -e "\nAssociative array"
declare -a vett1
 
vett1[stefano]=3

#nome=giulia
vett1[$nome]=pippo
 
echo ${vett1[stefano]}  # Prints 3
echo ${vett1["giulia"]} # Prints pippo
echo ${#vett1[*]}       # Prints 2
echo ${vett1[*]}        # Prints pippo 3
echo ${!vett1[*]}       # Prints giulia stefano
 
sum=0
for name in ${!vett1[*]}
do
    let sum=${vett1[$name]}+$sum
done
echo "Sum: $sum"
 
unset vett1
echo ${#vett1[*]} # Prints 0 (because vett1 does not exist)