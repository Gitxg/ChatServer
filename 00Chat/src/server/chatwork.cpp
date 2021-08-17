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

// ORM框架 对象关系映射(Object Relational Mapping)
// 业务模块和数据模块拆分开

// 处理登录业务
// {"msgid":1,"name":"xiao ai","password":"123456"}
void ChatWork::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "开始处理登录业务";
    //int id = js["id"];
    string name = js["name"];
    string password = js["password"];

    //select count(*) from user where password = "123456" AND name="pi pi";
    User usercin;
    usercin.setName(name);
    usercin.setPassword(password);

    //通过
    if (this->_usermodel.logselect(usercin))
    {
        LOG_INFO << "登录成功";
        json response;
        response["msgid"] = LOGIN_MSG_ACK;
        //表示登录响应成功
        response["reeno"] = 0;
        conn->send(response.dump());
    }
    else
    {
        LOG_INFO << "登录失败";
        json response;
        response["msgid"] = LOGIN_MSG_ACK;
        //表示响应成功
        response["reeno"] = 1;
        conn->send(response.dump());
    }
}

// 处理注册业务
void ChatWork::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    // 接收到的 js 信息为：
    // {"msgid":2,"name":"xiao ai","password":"123456"}
    LOG_INFO << "开始处理注册业务";

    string jsname = js["name"];
    string jspwd = js["password"];

    User usercin;
    usercin.setName(jsname);
    usercin.setPassword(jspwd);

    //通过
    if (this->_usermodel.insert(usercin))
    {
        LOG_INFO << "注册成功";
        json response;
        response["msgid"] = REG_MSG_ACK;
        //表示响应成功
        response["reeno"] = 0;
        response["id"] = usercin.getId();
        conn->send(response.dump());
    }

    else
    {
        LOG_INFO << "注册失败";
        json response;
        response["msgid"] = REG_MSG_ACK;
        //表示响应失败
        response["reeno"] = 1;
        conn->send(response.dump());
    }
}
