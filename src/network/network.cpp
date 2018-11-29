#include "network.h"

bool netConnected;
std::queue<std::string> replyList;
std::queue<std::string> advertList;

unsigned __stdcall receiveMessageThread(void* data);
unsigned __stdcall initialMessageTimeout(void* data);

void initializeWinsock(char IP[]) {
	WSAStartup(MAKEWORD(2, 2), &wsa);
	slen = sizeof(server);

	memset((char *)&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    server.sin_addr.S_un.S_addr = inet_addr(IP);
}

void closeWinsock() {
	CloseHandle(receiveThread);
	shutdown(s, SD_SEND);
	closesocket(s);
    WSACleanup();
}

void sendMessage(char message[]) {
	sendto(s, message, strlen(message), 0, (struct sockaddr *) &server, slen);
}

void receiveMessage() {
    unsigned threadID;
    receiveThread = (HANDLE)_beginthreadex(NULL, 0, receiveMessageThread, 0, 0, &threadID);
}

void receiveInitialMessage() {
	HANDLE hThread;  
    unsigned threadID;
    hThread = (HANDLE)_beginthreadex(NULL, 0, initialMessageTimeout, 0, 0, &threadID);
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);
}

unsigned __stdcall receiveMessageThread(void* data) {
	while (netConnected) {
		memset(buf, '\0', BUFLEN);
		recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &server, &slen);
		std::string message(buf);
		
		shoutMessage(message);

		if (message.substr(0, 5).compare("reply") == 0) { replyList.push(message.substr(message.find('>') + 1)); }
		else if (message.substr(0, 6).compare("advert") == 0) { advertList.push(message.substr(message.find('>') + 1)); }
	}

	_endthreadex(0);
	return 0;
}

unsigned __stdcall initialMessageTimeout(void* data) {
	recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&server, &slen);
	replyList.push(buf);
	std::cout << replyList.front() << std::endl;

	_endthreadex(0);
	return 0;
}

void shoutMessage(std::string message) {
	if (message.substr(0, 19).compare("advert->board_data:") != 0) {
		std::cout << message << std::endl;
	}
}