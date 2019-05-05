#!/bin/bash 

read -p "Please input a number, I will count for 1 + 2 + ... + you+input " nu
s=0
for(( i = 1; i <= $nu; ++i ))
do 
  s=$(($s + $i))
done 

echo "The result of '1 + 2 + 3  + ... +$nu' is ==> $s  "
