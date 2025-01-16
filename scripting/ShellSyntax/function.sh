Hello(){
    echo "Hello $1 $2"
    return 10
}

number_one(){
    echo "This is a first function"
    number_two
}

number_two(){
    echo "This is second function"
}

Hello Abdallah Tamra
ret=$?

echo "Return Value = $ret :)"


number_one