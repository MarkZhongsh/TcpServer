
#include "TcpServer/TcpServer.h"

void MsgHandle(void *);

int main()
{

    TcpServer *tcpServer = new TcpServer(4000, 10);
    tcpServer->startRecv(MsgHandle);

    printf("%s\n",__FILE__);

    return 0;
}

void MsgHandle(void *data)
{
    printf("MsgHandle in main:%s \n",(char*) data);
}
