#pragma once

#ifdef _WIN32
#include <winsock2.h>
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>  
#include <unistd.h> 
#endif
#include<functional>
#include<map>
#include<thread>

class SocketClient
{
public:
	SocketClient(std::string ip, short port);
	void connectServer(std::function<void(bool)> callback);
	void emit(std::string name, std::string message);
	void on(std::string name, std::function<void(std::string)> callback);
	void close();

private:

	void ErrorHandling(char* message);
private:
	int port;
	bool closed = true;

	std::function<void(bool)> connectCallback;
	std::map<std::string, std::function<void(std::string)>> onCallbacks;
	std::thread tHear;
	std::thread tConnect;

	SOCKET      hSocket;
	SOCKADDR_IN servAddr;
};
