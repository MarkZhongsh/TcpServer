test : main.o TcpServer.o
	g++ -o test TcpServer.o main.o 

TcpServer.o : TcpServer/TcpServer.h TcpServer/TcpServer.cpp
	g++ -DDEBUG -c -o TcpServer.o TcpServer/TcpServer.h -I TcpServer/TcpServer.cpp

main.o : main.cpp
	g++ -DDEBUG -c main.cpp TcpServer/TcpServer.cpp 

clean:
	rm -rf main.o TcpServer.o test
