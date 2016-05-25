#incldue <sys/socket.h>
#include <assert.h>
#include "TcpServer.h"

#define MINPORT 1
#define MAXPORT 65535



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

void TcpServer::port(int port)
{
    this.port = port;
}

int TcpServer::getMaxConnect()
{
    return this.maxConnect;
}

void TcpServer::maxConnect(int maxConnect)
{
    this.maxConnect = maxConnect;
}

void TcpServer::connect()
{
    //端口不能超过范围
    assert(this.port >= MINPORT && this.port < MAXPORT);

    struct sockaddr_in s_socket;
    if(( this.server_fd = socket(AF_INET, SOCK_STREAM, 0))
    {
#ifdef DEBUG
        perror("bind 出错");
        exit(1);
#endif
    }
    socket.sin_family = AF_INET;
    socket.sin_port = htons(port);
    socket.sin_addr.s_addr = INADDR_ANY;
    bzero(&(s_socket.sin_zero),8);

    if(bind(this.server_fd, (struct sockaddr *)& s_socket, sizeof(struct sockaddr)) == -1)
    {
#ifdef DEBUG
        perror("counld not bind");
        exit(1);
#endif
    }

}

bool TcpServer::listen()
{
    assert(this.server_fd != 0);
    if(listen(this.server_fd, maxConnect) == -1)
    {
#ifdef DEBUG
        perror("listen error");
        exit(1);
    }
}










