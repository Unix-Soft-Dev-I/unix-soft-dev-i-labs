#!/bin/bash

# Assignment
# Write a script that detects if it is being executed as root
# print a message "You need to run this as root" if is not
# executed as root.

if [ `id -u` -eq 0 ]; 
then
    echo "Root is executing this program.."
else
    echo "You need to run this program as root"
fi
