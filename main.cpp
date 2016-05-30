
#include "TcpServer/TcpServer.h"

int main()
{

    TcpServer *tcpServer = new TcpServer(4000, 10);

    tcpServer->connect();

    tcpServer->beginListen();

    printf("%s\n",__FILE__);
    tcpServer->beginAccept();

    return 0;
}
