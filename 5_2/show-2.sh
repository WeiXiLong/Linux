#!/bin/bash 

function print1(){
  echo -n "Your choice is $1"
}

echo "This program will print your selection! "
case $1 in
  "one")
      print1  1 ; 
      ;;
  "two")
      print1;echo $1 | tr 'a-z' 'A-Z'
      ;;
  "three")
      print1;echo $1 | tr 'a-z' 'A-Z'
      ;;
    *)
      echo "Usage $0 {one|two|three}"
      ;;
esac
