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
// 返回bool类型的登录  {"msgid":1,"name":"xiao ai","password":"123456"}
// 返回user类型的登录  {"msgid":1,"id":22,"password":"123456"}
void ChatWork::login(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    LOG_INFO << "开始处理登录业务";
    int id = js["id"];
    string password = js["password"];

    User user = this->_usermodel.select_user(id);

    if ((user.getId() != -1) && password == user.getPassword())
    {
        if ("online" == user.getState())
        {
            LOG_INFO << "该用户已经登录，禁止重复登录";
            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            //表示登录响应成功
            response["reeno"] = 2;
            response["errmsg"] = "该用户已经登录，禁止重复登录";
            conn->send(response.dump());
        }
        else
        {
            //更新用户状态信息
            user.setState("online");
            this->_usermodel.update_user(user);

            LOG_INFO << "登录成功";
            json response;
            response["msgid"] = LOGIN_MSG_ACK;
            //表示登录响应成功
            response["reeno"] = 0;
            conn->send(response.dump());

            { //作用域：在大括号里面定义该对象，出去括号自动析构并解锁
                //加锁来保证线程安全
                lock_guard<mutex> _guard(_gmut);
                //存储记录当前在线用户的通信连接信息
                _userConnMap.insert({id, conn});
            }
        }
    }
    else
    {
        LOG_INFO << "用户不存在或密码错误";
        json response;
        response["msgid"] = LOGIN_MSG_ACK;
        //表示登录响应失败
        response["reeno"] = 1;
        response["errmsg"] = "用户不存在或密码错误";
        conn->send(response.dump());
    }
    LOG_INFO << "处理登录业务结束";
    /*
    //方法1：返回bool类型的方法调用
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
    */
}

// 处理注册业务
void ChatWork::reg(const TcpConnectionPtr &conn, json &js, Timestamp time)
{
    // 接收到的 js 信息为：
    // {"msgid":3,"name":"xiao ai","password":"123456"}
    LOG_INFO << "开始处理注册业务";

    string jsname = js["name"];
    string jspwd = js["password"];

    User usercin;
    usercin.setName(jsname);
    usercin.setPassword(jspwd);

    //通过
    if (this->_usermodel.insert_user(usercin))
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

//处理客户端的异常退出
/*
    根据conn在map表中查询对应的id
    然后在map中删除该键值对
    最后通过数据库修改当前对应id的状态为 offline
*/
void ChatWork::clientCloseException(const TcpConnectionPtr &conn)
{
    User user;
    { //作用域：在大括号里面定义该对象，出去括号自动析构并解锁
        //加锁来保证线程安全
        lock_guard<mutex> _guard(_gmut);

        unordered_map<int, TcpConnectionPtr>::iterator it;
        for (it = _userConnMap.begin(); it != _userConnMap.end(); it++)
        {
            if (it->second == conn)
            {
                user.setId(it->first);
                _userConnMap.erase(it);
                break;
            }
        }
    }
    //在map表中查询到对应的id时
    if (-1 != user.getId())
    {
        //更新用户状态信息为 offline
        user.setState("offline");
        this->_usermodel.update_user(user);
    }
}
