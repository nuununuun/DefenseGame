#pragma once

#include<WinSock2.h>

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
	int port;
	bool closed = true;

	std::function<void()> connectCallback;
	std::map<std::string, std::function<void(std::string)>> onCallbacks;
	std::thread tHear;
	std::thread tConnect;

	WSADATA     wsaData;
	SOCKET      hSocket;
	SOCKADDR_IN servAddr;
};