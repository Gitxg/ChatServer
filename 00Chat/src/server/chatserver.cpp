#include "chatserver.hpp"
#include "chatwork.hpp"

#include <functional>
#include <iostream>
#include <string>

//引用json头文件
#include "json.hpp"
using json = nlohmann::json;

using namespace std;
using namespace placeholders;

ChatServer::ChatServer(EventLoop *loop,               //事件循环
                       const InetAddress &listenAddr, //IP地址+端口
                       const string &nameArg          //服务器的名字
                       ) : _server(loop, listenAddr, nameArg), _loop(loop)
{
    //给服务器注册用户连接的创建和断开回调        绑定器
    _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    //给服务器注册用户读写事件的回调
    _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    //设置服务器端的数量  1个IO线程，3个worker线程
    _server.setThreadNum(4);
}

//开启事件循环
void ChatServer::start()
{
    _server.start();
}

//专门处理用户的连接创建和断开
void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    if (conn->connected())
    {
        //客户端的IP地址 - > 服务端的的IP地址
        cout << "连接成功 " << conn->peerAddress().toIpPort() << " - > " << conn->localAddress().toIpPort() << endl;
    }
    else
    {
        cout << "连接失败 " << conn->peerAddress().toIpPort() << " - > " << conn->localAddress().toIpPort() << endl;
        conn->shutdown();
        //_loop->quit();
    }
}

//专门处理用户的读写事件
void ChatServer::onMessage(const TcpConnectionPtr &conn, //连接
                           Buffer *buffer,               //缓冲区
                           Timestamp time)               //接收到数据的时间戳
{
    //将缓冲区的内容存到字符串中
    string buf = buffer->retrieveAllAsString();

    //数据的解码，反序列化
    json js = json::parse(buf);

    //目的：完全拆分开（解耦）网络模块和业务模块
    //解耦: (1)面向基类的接口做。(2)采用回调函数

    //通过js["msgid"]来获取一个业务的handler
    auto msghandler = ChatWork::instance()->getHandldr(js["msgid"].get<int>());
    //回调消息对应绑定好的事件处理器，来执行相应的业务处理
    msghandler(conn, js, time);

    cout << "接收到的数据为：" << buf << "time: " << time.toString() << endl;
    conn->send(buf);
}
