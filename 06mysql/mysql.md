sudo apt-get install mysql-server
# 安装mysql服务器

sudo apt-get install libmysqlclient-dev
# 安装mysql开发包

# 查看用户名和密码
sudo cat /etc/mysql/debian.cnf

# 登录mysql
mysql -u root -p
# 密码为1

# 先查看MySQL默认的字符编码
show variables like "char%";

# 设置MySQL字符编码utf-8，可以支持中文操作
set character_set_server=utf8;


# 查看当前的进程
sudo netstat -tanp


# 连接到MySQL：
mysql -u root -p

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