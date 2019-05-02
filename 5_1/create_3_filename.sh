#!/bin/bash 

#1. 让使用者输入文件名，并取得 fileuser 这个变量
echo -e "I will use 'touch' command to create 3 files"
read -p "Please input your filename: " fileuser

#2. 为了避免使用者随意按Enter,利用变量功能分析档名是否有设定？
filename=${fileuser:-"filename"}

#3. 开始利用date 指令来取得所需要的档名
date1=$(date --date='2 days ago' +%Y%m%d)
date2=$(date --date='1 days ago' +%Y%m%d)
date3=$(date +%Y%m%d)

file1=${filename}_${date1}
file2=${filename}_${date2}
file3=${filename}_${date3}

#4. 将档名创建
touch "${file1}"
touch "${file2}"
touch "${file3}"
