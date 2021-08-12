#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <string>

#include <vector>
#include <map>
using namespace std;

void func1()
{
    json js;
    js["id"] = {1, 2, 3, 4};
    js["name"] = "branch";
    js["msg"] = "hello world";
    js["one"] = "hello world one";
    cout << js << endl;

    //转为字符串
    string sendbuf = js.dump();
    cout << sendbuf.c_str() << endl;
}

void func2()
{
    json js;
    vector<int> vec1;
    vec1.push_back(1);
    vec1.push_back(2);
    vec1.push_back(3);

    js["list"] = vec1;

    map<int, string> mp1;
    mp1.insert({1, "华为"});
    mp1.insert({2, "小米"});
    mp1.insert({3, "苹果"});
    js["path"] = mp1;
    cout << js << endl;
}

string refunc1()
{
    json js;
    js["id"] = {1, 2, 3, 4};
    js["name"] = "branch";
    js["msg"] = "hello world";
    js["one"] = "hello world one";
    cout << js << endl;

    //转为字符串
    string sendbuf = js.dump();
    return sendbuf;
}

string refunc2()
{
    json js;
    vector<int> vec1;
    vec1.push_back(111);
    vec1.push_back(2);
    vec1.push_back(333);

    js["list"] = vec1;

    map<int, string> mp1;
    mp1.insert({1, "华为"});
    mp1.insert({2, "小米"});
    mp1.insert({3, "苹果"});
    js["path"] = mp1;

    string sendbuf = js.dump();
    return sendbuf;
}

int main()
{
    func1();
    func2();

    //模拟接收到的字符串数据为 recvbuf
    string recvbuf1 = refunc1();
    //将字符串转为json对象
    json rejs1 = json::parse(recvbuf1);
    //反序列号得到对应的string数据
    string name = rejs1["name"];
    cout << name << endl;

    //
    //

    string recvbuf2 = refunc2();
    //将字符串转为json对象
    json rejs2 = json::parse(recvbuf2);
    vector<int> vecre1 = rejs2["list"];

    vector<int>::iterator it1 = vecre1.begin();
    while (it1 != vecre1.end())
    {
        cout << *it1++ << endl;
    }

    //
    //

    map<int, string> map1 = rejs2["path"];

    map<int, string>::iterator it2 = map1.begin();
    while (it2 != map1.end())
    {
        cout << (*it2).first << "  " << (*it2).second.c_str() << endl;
        it2++;
    }

    return 0;
}