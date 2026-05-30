#!/bin/bash
# count number of files in your PATH
IFS=:
count=0
for directory in $PATH
do
   if [ ! -d "$directory" ]; then
       echo "$directory - directory not found"
       continue
   fi
   count=0
   for item in "$directory"/*
   do
       [ -e "$item" ] && count=$(( count + 1 ))
   done
   echo "$directory - $count"
done