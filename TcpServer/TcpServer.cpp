#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>

#include "TcpServer.h"

TcpServer::TcpServer(int port, int maxConnect):port(port),maxConnet(maxConnect),connFd(0)
{
}



void TcpServer::startRecv(msgHandler handler)
{
}


void TcpServer::stopRecv()
{
}

int TcpServer::sendMsg(const char* str, unsigned int length)
{
    return 0;
}


int TcpServer::bindSocket()
{
    return 0;
}

int TcpServer::listenSocket()
{
    return 0;
}


