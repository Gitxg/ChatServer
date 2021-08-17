#ifndef PUBLIC_H
#define PUBLIC_H

/* server和client公共文件 */

enum EnMsgType
{
    LOGIN_MSG = 1,     //登录消息
    LOGIN_MSG_ACK = 2, //登录响应消息
    REG_MSG = 3,       //注册消息
    REG_MSG_ACK = 4,   //注册响应消息
    OTHER_MSG
};

#endif
