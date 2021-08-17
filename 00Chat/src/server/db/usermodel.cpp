#include "usermodel.hpp"
#include "db.hpp"

#include <iostream>
using namespace std;

bool UserModel::insert(User &user)
{
    //1. 组装sql语句
    char str_ins[1024] = {0};
    // insert into user(name, password, state)values('123','123','online');
    sprintf(str_ins, "insert into user(name, password, state)values('%s','%s','%s')",
            user.getName().c_str(),
            user.getPassword().c_str(),
            user.getState().c_str());

    //2. 定义MYSQL对象
    OrderSQL mysql1;
    if (mysql1.connect())
    {
        //如果更新数据成功
        if (mysql1.update(str_ins))
        {
            //设置用户的id
            //先获取当前连接 mysql.getConnect()
            //根据连接得到对应的id mysql_insert_id
            //然后进行用户id的设置
            user.setId(mysql_insert_id(mysql1.getConnect()));
            return true;
        }
    }
    // 否则是注册失败
    return false;
}

// 登录查询数据
bool UserModel::logselect(User &user)
{
    //1. 组装sql语句
    char str_sel[1024] = {0};
    // select count(*) from user where password = '123456' AND name = 'xiao ai'y
    sprintf(str_sel, "select count(*) from user where password = '%s' AND name = '%s'",
            user.getPassword().c_str(),
            user.getName().c_str());

    //2. 定义MYSQL对象
    OrderSQL mysql1;
    if (mysql1.connect())
    {
        //如果更新数据成功
        MYSQL_RES *res = mysql1.query(str_sel);
        //res不等于空指针代表查询成功
        if (res != nullptr)
        {
            //从返回值中查询行数
            MYSQL_ROW row = mysql_fetch_row(res);
            if (row != nullptr)
            {
                int num = atoi(row[0]);
                if (num > 0)
                {
                    //释放资源，保证内存不发生泄露
                    mysql_free_result(res);
                    return true;
                }
                /*
                User user;
                user.setId(atoi(row[0]));
                user.setName(row[1]);
                user.setPassword(row[2]);
                user.setState(row[3]);
                return user;
                */
            }
        }
        //释放资源，保证内存不发生泄露
        mysql_free_result(res);
        return false;
    }
    // 否则是注册失败
    return false;
}
