#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>


//class TcpServer
//{
//public:
//    TcpServer();
//    TcpServer(int port, int maxConnect);
//    ~TcpServer();
//
//    int getPort() const;
//    void setPort(int port);
//
//    int getMaxConnect() const;
//    void setMaxConnect(int maxConnect);
//
//    void connect();
//    bool beginListen();
//    bool unlisten();
//
//    void beginAccept();
//private:
//    //进行初始化操作
//    void setup();
//    //退出操作
//    void recycle();
//    //sigint处理
//    static void receiveSignInt(int signno);
//
//private:
//    int port;
//    int maxConnect;
//    int server_fd;
//    struct sockaddr_in s_socket;
//};

typedef void(*msgHandler)(void*);

class TcpServer
{
public:
    TcpServer(int port, int maxConnect);

    int getPort() const { return this->port;}
    void setPort(int port) { this->port = port;}

    int getMaxConnect() const { return this->maxConnet; }
    void setMaxConnect(int maxConnet) { this->maxConnet = maxConnet; }
    //开始监听
    void startRecv(msgHandler handler);
    //停止监听
    void stopRecv();

    //消息发送
    int sendMsg(const char* str, unsigned int length);

private:
    int bindSocket();
    int listenSocket();
private:
    int port;
    int maxConnet;
    int connFd;
    struct sockaddr_in socket;


};
