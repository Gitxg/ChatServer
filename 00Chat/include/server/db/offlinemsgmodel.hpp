#ifndef OFFLINEMSGMODEL_H
#define OFFLINEMSGMODEL_H

#include <list>
#include <string>
using namespace std;

class OfflineMsgModle
{
public:
    //存储用户的离线消息
    void insert(int userid, string msg);

    //删除用户的离线消息
    void remove(int userid);

    //查询用户的所有离线消息
    list<string> query(int userid);

private:
};

#endif