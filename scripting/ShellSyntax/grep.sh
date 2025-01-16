#!/bin/bash

# Searching for files that contains sh
ls -l | grep "sh"

# Searching for files that doesn't contain sh => Invert logic
ls -l | grep -v "sh"

# Prints only the names of files with matching lines (letter "sh")
ls -l | grep -n "sh"

# Prints only the count of matching lines => Returns 5
ls -l | grep -c "sh"

# Matches either upper or lowercase
ls -l | grep -i "sh"


