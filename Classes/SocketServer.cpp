#include "SocketServer.h"

#include <thread>
#include <vector>

#include"StringUtil.h"

#ifdef _WIN32
#pragma comment(lib,"wsock32.lib")
#endif

void SocketServer::ErrorHandling(char* message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	exit(1);
}

SocketServer::SocketServer(short port)
{
	this->port = port;
#ifdef _WIN32
	WSADATA     wsaData;
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
		ErrorHandling("WSAStartup() error!");
#endif
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	if (hServSock == INVALID_SOCKET)
		ErrorHandling("socket() error!");
	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);  // 현재 PC IP주소 사용
	servAddr.sin_port = htons(port);        // 포트번호

	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR)
		ErrorHandling("bind() error!");

}

void SocketServer::listenClient(std::function<void()> callback)
{
	listenCallback = callback;
	tListen = std::thread([&]() {
		if (listen(hServSock, 5) == SOCKET_ERROR)
			ErrorHandling("listen() error");
		sizeClientAddr = sizeof(clntAddr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &sizeClientAddr);   // 클라이언트와 통신 할
		if (hClntSock == INVALID_SOCKET)
			ErrorHandling("accept() error!");
		listenCallback();
		closed = false;

		tHear = std::thread([&]() {
			char message[512];
			while (!closed)
			{
				int len = recv(hClntSock, message, 512, 0);
				if (len > 0)
				{
					std::string s_message = message;
					auto s = StringUtil::split(message, '@');
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
	tListen.detach();
}

void SocketServer::emit(std::string name, std::string message)
{
	std::string msg = name + ";" + message;
	msg = std::to_string(msg.length()) + "@" + msg;
	send(hClntSock, msg.data(), msg.length(), 0);
}

void SocketServer::on(std::string name, std::function<void(std::string)> callback)
{
	onCallbacks.insert(make_pair(name, callback));
}

void SocketServer::close()
{
	closesocket(hClntSock);
	closesocket(hServSock);
#ifdef _WIN32
	WSACleanup();
#endif
	closed = true;
}

