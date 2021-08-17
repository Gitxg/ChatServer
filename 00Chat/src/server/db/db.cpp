
#include "db.hpp"
#include <muduo/base/Logging.h>

// 数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "1";
static string dbname = "chat";

// 初始化数据库连接
OrderSQL::OrderSQL()
{
    _conn = mysql_init(nullptr);
}
// 释放数据库连接资源
OrderSQL::~OrderSQL()
{
    if (_conn != nullptr)
        mysql_close(_conn);
}

// 连接数据库
bool OrderSQL::connect()
{
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                  password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr)
    {
        //C和C++的编码格式设置
        mysql_query(_conn, "set names gbk");
        LOG_INFO << "连接数据库成功!";
        return true;
    }
    else
    {
        LOG_INFO << "连接数据库失败!";
    }
    return false;
}

// 更新操作
bool OrderSQL::update(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败!";
        return false;
    }
    return true;
}

// 查询操作
MYSQL_RES *OrderSQL::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

MYSQL *OrderSQL::getConnect()
{
    return _conn;
}
