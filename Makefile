test : main.o TcpServer.o
	g++ -o test TcpServer.o main.o 

TcpServer.o : TcpServer/TcpServer.h TcpServer/TcpServer.cpp
	g++ -ggdb3 -DDEBUG -c -o TcpServer.o TcpServer/TcpServer.cpp -I TcpServer

main.o : main.cpp
	g++ -ggdb3 -DDEBUG -c main.cpp TcpServer/TcpServer.cpp 

clean:
	rm -rf main.o TcpServer.o test
