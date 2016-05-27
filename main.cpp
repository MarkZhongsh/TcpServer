#include <iostream>

#include "TcpServer/TcpServer.h"
using namespace std;

int main()
{

    TcpServer *tcpServer = new TcpServer(4000, 10);

    tcpServer->connect();

    tcpServer->beginListen();

    return 0;
}
