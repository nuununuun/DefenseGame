#pragma once

#include<string>
#include<functional>
#include<WinSock2.h>
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
	short port;
	int sizeClientAddr;
	bool closed = true;

	std::function<void()> listenCallback;
	std::map<std::string, std::function<void(std::string)>> onCallbacks;
	std::thread tHear;
	std::thread tListen;
	WSADATA     wsaData;
	SOCKET      hServSock, hClntSock;
	SOCKADDR_IN servAddr, clntAddr;
};