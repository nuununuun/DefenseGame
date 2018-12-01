#pragma once

#include<string>
#include<functional>
#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  
#include <unistd.h>

typedef int SOCKET;

#endif
#include<thread>
#include<map>

class SocketServer
{
public:
	SocketServer(short port);

	void listenClient(std::function<void()> callback);
	void emit(std::string name, std::string message);
	void on(std::string name, std::function<void(std::string)> callback);
	void close();

private:
	void ErrorHandling(char* message);
private:
	short port;
	int sizeClientAddr;
	bool closed = true;

	std::function<void()> listenCallback;
	std::map<std::string, std::function<void(std::string)>> onCallbacks;
	std::thread tHear;
	std::thread tListen;
	SOCKET      hServSock, hClntSock;
	sockaddr_in servAddr, clntAddr;
};
