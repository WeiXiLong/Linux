#!/bin/bash 

echo -e "This program will calculate pi value.\n"
echo -e "You should input a float number to calculate pi value. \n"
read -p "The scale number (10 ~ 10000)? " checking

num=${checking:-"10"}
echo -e "Starting calcuate pi value. Be patient."
time echo "scale=$num; 4*a(1)" | bc -lq
