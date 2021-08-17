#include <iostream>
#include <chatserver.hpp>

using namespace std;

int main()
{
    cout << "server is running..." << endl;
    EventLoop loop;
    //10.221.100.15
    InetAddress addr("127.0.0.1", 4567);
    ChatServer server(&loop, addr, "mychatserver");
    server.start(); //启动服务
    loop.loop();    //epoll_wait 以阻塞的方式等待用户连接

    // bash里面以客户端的身份进行访问
    // telnet 127.0.0.1 4567
    return 0;
}