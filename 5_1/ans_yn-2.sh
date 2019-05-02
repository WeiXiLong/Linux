#!/bin/bash 

read -p "Please input (Y/N): " yn

if [ "$yn" == "Y" ] || [ "$yn" == "y" ]; then
  echo "ok,continue"
  exit 0
fi 

if [ "$yn" == "N" ] || ["$yn" == "b" ]; then 
  echo "Oh,interrupt"
  exit 0
fi 

echo "I don't know what your choice is " && exit 0
