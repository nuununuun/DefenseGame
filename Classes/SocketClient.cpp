#include "SocketClient.h"



#define _WINSOCK_DEPRECATED_NO_WARNINGS


#ifdef _WIN32

#include <WS2tcpip.h>

#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "ws2_32.lib")

#endif

#include"StringUtil.h"

#include<stdio.h>
#include <vector>




SocketClient::SocketClient(std::string ip, short port)
{
	this->port = port;

#ifdef _WIN32
	WSADATA     wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");
	
#endif
	hSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (hSocket < 0)
		ErrorHandling("hSocket() error!");

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip.data(), &servAddr.sin_addr.s_addr);

}

void SocketClient::connectServer(std::function<void(bool)> callback)
{
	connectCallback = callback;
	tConnect = std::thread([&]() {
		bool connect_try = true;
		if (connect(hSocket, (sockaddr*)&servAddr, sizeof(servAddr)) == -1)
			connect_try = false;
		connectCallback(connect);
		closed = false;
		tHear = std::thread([&]() {
			char message[512];
			while (!closed)
			{
				int len = recv(hSocket, message, 512, 0);
				if (len > 0)
				{
					std::string s_message = message;
					auto s = StringUtil:: split(message, '@');
					int size = atoi(s[0].data());
					auto _s = s[1].substr(0, size);
					auto msg = StringUtil::split(_s, ';');
					onCallbacks[msg[0]](msg[1]);
					onCallbacks.erase(msg[0]);
				}
			}
		});
		tHear.detach();
	});
	tConnect.detach();
}

void SocketClient::emit(std::string name, std::string message)
{
	std::string msg = name + ";" + message;
	msg = std::to_string(msg.length()) + "@" + msg;
	send(hSocket, msg.data(), msg.length(), 0);
}

void SocketClient::on(std::string name, std::function<void(std::string)> callback)
{
	onCallbacks.insert(make_pair(name, callback));
}

void SocketClient::close()
{
#ifdef _WIN32
    closesocket(hSocket);
    WSACleanup();
#else
    ::close(hSocket);
#endif
}

void SocketClient::ErrorHandling(char * message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}
