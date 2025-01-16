# This is my libary of Bash Scripting Language Commands

# Example 1

# Understand the Script
# The given script performs the following actions:

# 1) Removes a directory (newDir) located one level up (../) relative to the script's location
# 2) Creates a new directory (newDir) in the same location
# 3) Copies all files (*) from the current directory to the newly created directory
# 4) Lists the contents of the newDir
# 5) Exits with a success code (exit 0)

rm -rf ./../newDir/  # -r   => Without -r, rm would only remove files and would fail to delete directories
mkdir ./../newDir/   # -f   => This option forces the removal of files and directories without prompting for confirmation, even if they are write-protected
cp * ../newDir/      # cp * => Copies all files (*) from the current directory to the newly created directory.
ls ../newDir/;
exit 0


# ARGUMENTS
$0 => is the script name 
$1 => indicate the arguments passed to the script on the command line
$2 => indicate the arguments passed to the script on the command line
$3 => indicate the arguments passed to the script on the command line
$* => Is the entire list (string) of arguments (excluding the script name)
$# => Is the number of parameters (excluding the script name)
$$ => Is the process PID


# EXAMPLE 2 => ARGUMENTS PASSING THROUGH COMMAND LINE PARAMETERS

#!/bin/bash => It tells the system to execute the script using the Bash shell,
# which is commonly found at /bin/bash on Unix-like systems.

# Using command line parameters

echo "Running process is $0"
echo "Parameters: $1 $2 $3 $4 etc..."
echo "Number of parameters $#"
echo "List of parameters $*"

shift 
#shift removes the first positional parameter ($1) and shifts the remaining parameters left
#$2 becomes $1
#$3 becomes $2
#$4 becomes $3

echo "Parameters: $1 $2 $3 $4 etc..."

shift

echo "Parameters: $1 $2 $3 $4 etc..."
exit 0


# Variables Example of Usage

clear
echo "Hello, $USER!"
echo
echo "List logged users"
w #or whof
echo "Set two local variables"
COLOR="black"; 
VALUE="9";

echo "String: $COLOR"
echo "Number: $VALUE"
echo
echo "Completed"

# Predefined Variables

$?  =>  Stores the return value of the last process => 0 on success => 1 otherwise

$SHELL => Current shell

$LOGNAME => Username used for login

$HOME => User home directory

$PATH => List of the directories, delimited by ':' used forr searching the executable files and commands

$PS1 => Main prompt (usually '$' for users, '#' for root)

$PS2 => Auxiliary prompt (usually '>' )

$IFS => Lists the characters that delimits the "words" in an input string (see read shell command )















