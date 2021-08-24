
#include "db.hpp"
#include "offlinemsgmodel.hpp"

#include <vector>
#include <string>
using namespace std;

//存储用户的离线消息
void OfflineMsgModle::insert(int userid, string msg)
{
    char strsql[1024] = {0};
    //1.组装sql语句 insert into offlinemessage(userid, message)values(20,'123');
    sprintf(strsql, "insert into offlinemessage(userid, message)values(%d,'%s')", userid, msg);

    //2. 定义MYSQL对象
    OrderSQL mysql;
    if (mysql.connect())
    {
        mysql.update(strsql)
    }
}

//删除用户的离线消息
void OfflineMsgModle::remove(int userid)
{
    char strsql[1024] = {0};
    //1.组装sql语句 delete from offlinemessage where userid = 20;
    sprintf(strsql, "delete from offlinemessage where userid = %d", userid);

    //2. 定义MYSQL对象
    OrderSQL mysql;
    if (mysql.connect())
    {
        mysql.update(strsql)
    }
}

//查询用户的所有离线消息
vector<string> OfflineMsgModle::query(int userid)
{
    vector<string> vecres;

    //1. 组装sql语句
    char strsql[1024] = {0};
    // select * from offlinemessage where userid = 19;
    sprintf(strsql, "select message from offlinemessage where userid = '%d'", userid);

    //2. 定义MYSQL对象
    OrderSQL mysql;
    if (mysql.connect())
    {
        //如果更新数据成功
        MYSQL_RES *res = mysql.query(strsql);
        //res不等于空指针代表查询成功
        if (res != nullptr)
        {
            LOG_INFO << "查询成功";
            //从返回值中查询行数
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)) != nullptr)
            {
                vecres.push_back(row[0]);
            }
        }
        //释放资源，保证内存不发生泄露
        mysql_free_result(res);
    }
    // 否则是注册失败，直接返回id值为-1的User对象
    return vecres;
}
