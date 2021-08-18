#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

//User表的数据操作类
class UserModel
{
public:
    //user的增加用户信息的方法
    bool insert_user(User &user);

    //user的登录方法:返回登录成功的bool类型
    bool logselect(User &user);

    //user的登录方法:根据id的值查询用户信息
    User select_user(int id);

    //user的登录方法:根据id的值查询用户信息
    bool update_user(User &user);
};

#endif