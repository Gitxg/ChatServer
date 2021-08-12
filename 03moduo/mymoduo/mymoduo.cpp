#include <muduo/net/TcpServer.h>
#include <muduo/base/Logging.h>
//#include <boost/bind.hpp>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <string>

#include <functional>

using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

// muduo 网络库给用户主要提供两个类
// TcpServer ： 用于编写服务器程序的
// TcpClient ： 用于编写客户端程序的
// epoll+线程池
// 好处：能把网络的IO的代码和业务分开
// 用户的连接和断开，用户的可读写事件

/*
第1步 组合TcpServer对象
第2步 创建EventLoop事件的循环指针
第3步 明确TcpServer构造函数需要什么参数，输出ChatServer的构造参数
第4步 在当前服务其的构造函数中，处理回调函数
第5步 设置合适的服务端线程数量，muduo库会自己划分 IO线程和 work线程
 */

class ChatServer
{
public:
  ChatServer(EventLoop *loop,               //事件循环
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
  void start()
  {
    _server.start();
  }

private:
  //专门处理用户的连接创建和断开
  void onConnection(const TcpConnectionPtr &conn)
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
  void onMessage(const TcpConnectionPtr &conn, //连接
                 Buffer *buffer,               //缓冲区
                 Timestamp time)               //接收到数据的时间戳
  {
    string buf = buffer->retrieveAllAsString();
    cout << "接收到的数据为：" << buf << "time: " << time.toString() << endl;
    conn->send(buf);
  }

  TcpServer _server; //#1
  EventLoop *_loop;  //#2 epoll
};

int main()
{
  cout << "我是服务器，已经开始运行..." << endl;
  EventLoop loop;
  //10.221.100.15
  InetAddress addr("10.221.100.15", 4567);
  ChatServer server(&loop, addr, "mychatserver");
  server.start(); //启动服务
  loop.loop();    //epoll_wait 以阻塞的方式等待用户连接

  // bash里面以客户端的身份进行访问
  // telnet 127.0.0.1 4567
  return 0;
}
