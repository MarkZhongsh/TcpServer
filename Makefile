CC=g++ -ggdb3 -D DEBUG

test : main.o TcpServer.o LogUtil.o
	$(CC) -o test TcpServer.o main.o LogUtil.o

TcpServer.o : TcpServer/TcpServer.h TcpServer/TcpServer.cpp Util/LogUtil.cpp
	$(CC) -c -o TcpServer.o TcpServer/TcpServer.cpp -I TcpServer

LogUtil.o : Util/LogUtil.h
	$(CC) -c -o LogUtil.o Util/LogUtil.cpp -I Util

main.o : main.cpp
	$(CC) -c main.cpp 

clean:
	rm -rf main.o TcpServer.o LogUtil.o test
