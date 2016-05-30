#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <netinet/in.h>


class TcpServer
{
public:
    TcpServer();
    TcpServer(int port, int maxConnect);
    ~TcpServer();

    int getPort();
    void setPort(int port);

    int getMaxConnect();
    void setMaxConnect(int maxConnect);

    void connect();
    bool beginListen();
    bool unlisten();

    void beginAccept();


private:
    int port;
    int maxConnect;
    int server_fd;
    struct sockaddr_in s_socket;
};
