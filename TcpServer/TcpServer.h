#include <stdio.h>
#include <stdlib.h>
#include <errno.h>



class TcpServer
{
public:
    TcpServer();
    TcpServer(int port, int maxConnect);
    ~TcpServer();

    int getPort();
    void setPort(int port);

    int getMaxConnect();
    void setMaxConnect();

    void connect();
    bool listen();
    bool unlisten();


private:
    int port;
    int maxConnect;
    int server_fd;
};
