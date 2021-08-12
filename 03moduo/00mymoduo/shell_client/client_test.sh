#!/bin/bash
g++ --version
whoami
date

#以客户端连接服务器
telnet 10.221.100.15 4567

i=1
while(( $i<=5 ))
do
    $i
    let "i++"
# sleep 2 延时2秒
    sleep 2
done





