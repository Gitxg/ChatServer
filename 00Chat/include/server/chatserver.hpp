#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

class ChatServer
{
public:
    ChatServer(EventLoop *loop,               //事件循环
               const InetAddress &listenAddr, //IP地址+端口
               const string &nameArg          //服务器的名字
    );

    //开启事件循环
    void start();

private:
    //专门处理用户的连接创建和断开
    void onConnection(const TcpConnectionPtr &conn);

    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn, //连接
                   Buffer *buffer,               //缓冲区
                   Timestamp time);              //接收到数据的时间戳

    TcpServer _server; //组合 moduo 库，实现服务器功能的类对象
    EventLoop *_loop;  //指向事件循环对象的指针
};

#endif