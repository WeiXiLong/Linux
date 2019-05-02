#!/bin/bash 

echo -e "You SHOULD input 2 integer numbers,I will multipling them! \n"
read -p "First number: " firstnu
read -p "Second number: " secnu

total=$(($firstnu * $secnu))
echo -e "\nThe result of $firstnu x $secnu is ==> $total"
