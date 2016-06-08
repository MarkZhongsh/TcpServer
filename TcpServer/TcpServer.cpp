#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#include "TcpServer.h"
#include "../Util/LogUtil.h"



TcpServer::TcpServer(int port, int maxConnect):port(port),maxConnet(maxConnect),connFd(0)
{
}



void TcpServer::startRecv(msgHandler handler)
{
    assert(this->port>0);
    assert(this->maxConnet>0);

    if(connFd)
    {
        close(connFd);
        connFd = 0;
    }

    LogUtil::Log("begin connect");
    this->connFd = socket(AF_INET, SOCK_STREAM, 0);
    if(this->connFd < 0)
    {
        perror("create socket error");
        return ;
    }
    LogUtil::Log("end connect");

    LogUtil::Log("begin bind");
    if(bindSocket() < 0)
    {
        close(this->connFd);
        this->connFd = 0;
        return ;
    }
    LogUtil::Log("end bind");

    LogUtil::Log("begin listen");
    if(listenSocket() < 0)
    {
        close(this->connFd);
        this->connFd = 0;
        return ;
    }
    LogUtil::Log("end listen");

    LogUtil::Log("begin accept");
    struct sockaddr_in client;
    int conn = acceptFromClient(client);
    if(conn < 0)
    {
        close(this->connFd);
        return ;
    }
    printf("client's ip:%s \n", inet_ntoa(client.sin_addr));
    LogUtil::Log("end accept");

    while(true)
    {
        char buff[TCP_BUFFER_SIZE];
        memset(buff, 0, TCP_BUFFER_SIZE);
        int len = recv(conn, buff, TCP_BUFFER_SIZE, 0);
        if(len > 0)
        {
            printf("client msg:%s\n", buff);
            if(handler != NULL)
            {
                handler((void*)buff);
            }
            //const char *sayHello = "hello, I am the server~";
            //sendMsg(conn, (void*)sayHello, strlen(sayHello));
        }
        else if(len<0)
        {
            perror("recv error");
            return ;
        }
    }

}


void TcpServer::stopRecv()
{
}

int TcpServer::sendMsg(int conn, void* data, unsigned int length)
{
    if(send(conn, data, length, 0) < 0)
    {
        perror("send error");
        return -1;
    }
    return 0;
}

int TcpServer::sendMsg(const char* str, unsigned int length)
{

    return 0;
}


int TcpServer::bindSocket()
{
    this->m_Socket.sin_port = htons(this->port);
    this->m_Socket.sin_family = AF_INET;
    this->m_Socket.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(this->connFd, (struct sockaddr*)&(this->m_Socket), sizeof(this->m_Socket)) < 0)
    {
        perror("bind error");
        return -1;
    }
    return 0;
}

int TcpServer::listenSocket()
{
    if(listen(this->connFd, this->maxConnet) < 0)
    {
        perror("listen error");
        return -1;
    }
    return 0;
}

int TcpServer::acceptFromClient(struct sockaddr_in &client)
{
    socklen_t length = sizeof(client);
    int conn = accept(this->connFd, (struct sockaddr*)&client, &length); 
    if(conn < 0)
    {
        perror("accept error");
        return -1;
    }
    return conn;
}


