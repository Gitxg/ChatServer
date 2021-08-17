#ifndef CHATWORK_H
#define CHATWORK_H

#include <muduo/net/TcpServer.h>

#include <unordered_map>
#include <functional>

using namespace muduo;
using namespace muduo::net;
using namespace std;

#include "json.hpp"
using json = nlohmann::json;

// 用户注册的数据库操作
#include "usermodel.hpp"

//表示处理消息的事件，回调方法类型
using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

//聊天服务器的业务类
class ChatWork
{
public:
    //获取单例对象的接口函数
    static ChatWork *instance();

    //处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);

    //获取消息对应的处理器
    MsgHandler getHandldr(int msgid);

private:
    //构造函数私有化
    ChatWork();

    //存储消息ID和其业务对应的处理方法
    unordered_map<int, MsgHandler> _msghandlermap;

    // 数据操作类的对象
    UserModel _usermodel;
};

#endif