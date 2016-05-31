#include <sys/socket.h>
#include <assert.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <error.h>

#include "TcpServer.h"

#define MINPORT 1
#define MAXPORT 65535
#define BUFFER_SIZE 512


TcpServer::TcpServer():port(0),maxConnect(10),server_fd(0)
{
}

TcpServer::TcpServer(int port, int maxConnect):port(port),maxConnect(maxConnect),server_fd(0)
{
}

TcpServer::~TcpServer()
{

}


int TcpServer::getPort()
{
    return port;
}

void TcpServer::setPort(int port)
{
    this->port = port;
}

int TcpServer::getMaxConnect()
{
    return this->maxConnect;
}

void TcpServer::setMaxConnect(int maxConnect)
{
    this->maxConnect = maxConnect;
}

void TcpServer::connect()
{
    //端口不能超过范围
    assert(this->port >= MINPORT && this->port < MAXPORT);

    if(( this->server_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
#ifdef DEBUG
        extern int error;
        perror(strerror(error));
        error = 0;
        exit(1);
#endif
    }
    this->s_socket.sin_family = AF_INET;
    this->s_socket.sin_port = htons(port);
    this->s_socket.sin_addr.s_addr = htonl(INADDR_ANY);
    bzero(&(s_socket.sin_zero),8);

    if(bind(this->server_fd, (struct sockaddr *)& s_socket, sizeof(struct sockaddr)) == -1)
    {
#ifdef DEBUG
        perror("counld not bind");
        exit(1);
#endif
    }

}



bool TcpServer::beginListen()
{
    assert(this->server_fd != 0);
    if(listen(this->server_fd, this->maxConnect) == -1)
    {
#ifdef DEBUG
        perror("listen error");
        exit(1);
#endif
    }
    return true;
}

void TcpServer::beginAccept()
{
    struct sockaddr_in client_addr;
    socklen_t length = sizeof(client_addr);
    int conn = accept(this->server_fd, (struct sockaddr*)&client_addr, &length);

    if(conn < 0)
    {
#ifdef DEBUG
        perror("connect err");
#endif
        close(conn);
        return ;
    }
    
    char buffer[BUFFER_SIZE];
    while(true)
    {
        memset(buffer, 0, sizeof(buffer));
        int len = recv(conn, buffer, sizeof(buffer), 0);
        if(len > 0)
        {
            printf("%d\n", len);
            printf("%s\n", buffer);
            
            char sendStr[] = "asdf";
            sprintf(sendStr, "%s_from_server", buffer);
            printf("ready to send str: %s\n", sendStr);
            int result = send(conn, sendStr, strlen(sendStr), MSG_DONTWAIT);
            if(result < 0)
            {
                printf("send error:%d\n", result);
                perror("发送失败");
            }

        }
    }
    printf("exit accept\n");
    close(conn);
    close(this->server_fd);
}








