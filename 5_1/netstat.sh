#!/bin/bash 


#1. 先进行告知的动作
echo -e "Now,I will detect your Linux server's services!\n"
echo -e "The www,ftp,ssh,adn mail(smtp) will be detect! \n"

#2. 开始进行一些测试的工作，并且输出一些信息

testfile=/dev/shm/netstat_checking.txt
netstat -tuln > ${testfile}
testing=$(grep ":80" $testfile) 
