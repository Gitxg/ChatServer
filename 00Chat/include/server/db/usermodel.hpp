#ifndef USERMODEL_H
#define USERMODEL_H

#include "user.hpp"

//User表的数据操作类
class UserModel
{
public:
    //user的增加用户信息的方法
    bool insert(User &user);

    //user的登录方法
    bool logselect(User &user);
};

#endif