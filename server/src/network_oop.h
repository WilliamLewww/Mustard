#pragma once
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>
#include <stdio.h>
#include <winsock2.h>
#include "client.h"

#pragma comment(lib,"ws2_32.lib")

#define BUFLEN 512
#define PORT 8888

class Network {
private:
	std::string str;
	
	bool start = false;
	double startTimer = -1;

	int seed;
	Client tempClient;
	std::vector<Client> clientList;
	int clientListSize = 0;

	std::string newestMessage;

	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen , recv_len;
	char buf[BUFLEN];
	WSADATA wsa;

	void initializeWinsock();
	void createSocket();
	void bindSocket();
	void generateSeed();

	void updateThread();

	void sendMessage(char message[], Client client);
public:
	void initialize();
	void listen();
	void close();
};