#安装mysql的教程
https://www.cnblogs.com/zhuyp1015/p/3561470.html

# 安装mysql服务器
sudo apt-get install mysql-server

# 安装mysql客户端
apt-get install mysql-client

# 安装mysql开发包
sudo apt-get install libmysqlclient-dev


---初始的用户名和密码是自动生成的，需要进行修改：---
# 查看用户名和密码
sudo cat /etc/mysql/debian.cnf
查看初始的用户名和密码，然后登录mysql（注意空格）
mysql -u 用户名 -p密码
mysql -u debian-sys-maint -prXcsJDTErK4NXwlf
设置新的用户名为 root 和密码为 1：
update mysql.user set authentication_string=password('1') where
user='root' and host='localhost';

update mysql.user set plugin="mysql_native_password";

flush privileges;

exit;
----------------------end------------------------

# 登录并连接到MySQL数据库
mysql -u root -p
# 密码为1

# 先查看MySQL默认的字符编码
show variables like "char%";

# 设置MySQL字符编码utf-8，可以支持中文操作
set character_set_server=utf8;


# 通过.sql文件导入数据库
# 创建好数据库,因为导出的文件里没有创建数据库的语句,如果数据库已经建好,则不用再创建。
CREATE DATABASE example;
# 切换数据库：
use example；
# 切换到对应的sql文件目录下,执行以下文件导入数据库的表
source chat.sql


# 显示所有的数据库
show databases;
# 切换数据库：
use chat;
# 显示该数据库下的所有表
show tables;

# 查看当前的进程
sudo netstat -tanp




