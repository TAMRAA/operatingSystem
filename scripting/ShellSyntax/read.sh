# A simple app :)

echo -e "What's your name?"
read name

echo -e "What's your surname?"
read surname

echo -e "Welcome $name $surname to my simple app :)"

echo -e "Do you want to perform a simple check on who you are?\n=> (yes/no)"
read answer

if [ $answer == "yes" ]
    then
        times=$(who | grep $name | wc -l)
        echo "User $name has $times login(s) :)"
elif [ $answer == "no" ]
    then
        echo "Exiting app..."
        echo "Thanks for using my app <3"
else
        echo "Wrong input :/"
fi
