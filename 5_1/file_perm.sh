#!/bin/bash 

#1. 让使用者输入档名，并且判断使用者是否真的有输入字符串
echo -e "Please input a filename,I will check the filename's type and permission. \n\n"
read -p "Input a filename :" filename
test -z $filename && echo "You MUST input a filename " && exit 0

#2. 判断文件是否存在？若不存在则显示讯息并结束脚本呢
test ! -e $filename && echo "The filename '$filename' DO NOT exist" && exit 0

#3. 开始判断文件类型和属性
test -f $filename && filetype="regular file"
test -d $filename && filetype="directory"
test -r $filename && perm="readable"
test -w $filename && perm="$perm writable"
test -x $filename && perm="$perm executable"

#4. 开始输出信息
echo "The filename: $filename is a $filetype "
echo "And the permission for you see : $perm"
