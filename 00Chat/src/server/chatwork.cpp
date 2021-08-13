#include "chatwork.hpp"
#include "public.hpp"

#include <muduo/base/Logging.h>
using namespace muduo;

//获取单例对象的接口函数
ChatWork *ChatWork::instance()
{
    static ChatWork work;
    return &work;
}

//构造函数私有化 注册消息以及对应的Handler回调操作
ChatWork::ChatWork()
{
    _msghandlermap.insert({LOGIN_MSG, std::bind(&ChatWork::login, this, _1, _2, _3)});
    _msghandlermap.insert({REG_MSG, std::bind(&ChatWork::reg, this, _1, _2, _3)});
}

//获取消息对应的处理器
MsgHandler ChatWork::getHandldr(int msgid)
{
    //记录错误日志，msgid没有对应的事件处理回调
    auto it = _msghandlermap.find(msgid);
    if (it == _msghandlermap.end())
    {
        return [=](const TcpConnectionPtr &conn, json &js, Timestamp time)
        {
            //返回默认的处理器，空操作
            LOG_ERROR << "msgid:" << msgid << "do not find handler!";
        };
    }
    else
    { //找到存在的
        return _msghandlermap[msgid];
    }
}

//处理登录业务
void ChatWork::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "处理登录业务";
}

//处理注册业务
void ChatWork::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "处理注册业务";
}
