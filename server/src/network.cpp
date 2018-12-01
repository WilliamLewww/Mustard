#include "network.h"

void networkInitialize() {
	networkInitializeWinsock();
	networkCreateSocket();
	networkBindSocket();
	networkGenerateSeed();
}

void networkGenerateSeed() {
	seed = time(NULL);
}

void networkInitializeWinsock() {
	printf("\nInitializing Winsock...\n");
	slen = sizeof(tempClient.addrLength);
	WSAStartup(MAKEWORD(2,2),&wsa);
}

void networkCreateSocket() {
	printf("Creating Socket...\n");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( PORT );

	s = socket(AF_INET , SOCK_DGRAM , 0);
}

void networkBindSocket() {
	printf("Binding Socket...\n");
	bind(s ,(struct sockaddr*)&server , sizeof(server));
	printf("Complete\n\n");
	printf("Listening for Messages:\n");
}

void networkListen() {
	bool shoutMessage = true;
	bool clientExists = false;

	fflush(stdout);
	memset(buf,'\0', BUFLEN);
	 
	recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &tempClient.address, &tempClient.addrLength);
	newestMessage = buf;

	for (Client &client : clientList) {
		if (inet_ntoa(tempClient.address.sin_addr) == inet_ntoa(client.address.sin_addr) &&
			ntohs(tempClient.address.sin_port) == ntohs(client.address.sin_port)) {
			knownClient = &client;
			clientExists = true;
		}
	}

	if (clientExists == false) {
		if (newestMessage == "connect") {
			networkStartUpdate();

			tempClient.uniqueID = clientListSize;
			clientListSize += 1;
			clientList.emplace_back(tempClient);

			sendMessage((char*)"connect", tempClient);

			sendStr = "reply->unique_id:" + std::to_string(tempClient.uniqueID);
			sendMessage(&sendStr[0u], tempClient);

			sendStr = "reply->seed:" + std::to_string(seed);
			sendMessage(&sendStr[0u], tempClient);

			sendStr = "reply->rain_seed:" + std::to_string(time(NULL));
			sendMessage(&sendStr[0u], tempClient);

			for (Client client : clientList) {
				if (!clientEquals(tempClient, client)) {
					sendStr = "advert->new_client:" + std::to_string(client.uniqueID);
					sendMessage(&sendStr[0u], tempClient);

					sendStr = "advert->new_client:" + std::to_string(tempClient.uniqueID);
					sendMessage(&sendStr[0u], client);

					sendStr = "advert->rain_seed:" + std::to_string(time(NULL));
					sendMessage(&sendStr[0u], client);

					sendStr = "advert->reset_full";
					sendMessage(&sendStr[0u], client);
				}
			}

			sendStr = "reply->reset_full";
			sendMessage(&sendStr[0u], tempClient);
		}
	}
	else {
		if (newestMessage.substr(0, 10).compare("board_data") == 0) {
			shoutMessage = false;

			knownClient->isAlive = true;
			std::string tempMessage(newestMessage.substr(newestMessage.find(':') + 1));

			knownClient->position.x = std::stod(tempMessage.substr(0, tempMessage.find(':')));
			tempMessage = tempMessage.substr(tempMessage.find(':') + 1);

			knownClient->position.y = std::stod(tempMessage.substr(0, tempMessage.find(':')));
			tempMessage = tempMessage.substr(tempMessage.find(':') + 1);

			knownClient->angle = std::stod(tempMessage);
		}

		if (newestMessage.substr(0, 4).compare("kill") == 0) {
			knownClient->isAlive = false;

			for (Client client : clientList) {
				if (!clientEquals(*knownClient, client)) {
					sendStr = "advert->board_data:" + std::to_string(knownClient->uniqueID) + ":";
					sendStr += std::to_string(knownClient->position.x) + ":";
					sendStr += std::to_string(knownClient->position.y) + ":";
					sendStr += std::to_string(knownClient->angle);
					sendMessage(&sendStr[0u], client);

					sendStr = "advert->kill:" + std::to_string(knownClient->uniqueID);
					sendMessage(&sendStr[0u], client);
				}
			}
		}
	}
	
	if (shoutMessage) {
		printf("%s:%d: ", inet_ntoa(tempClient.address.sin_addr), ntohs(tempClient.address.sin_port));
		printf("%s\n" , buf);
	}
}

void networkStartUpdate() {
	HANDLE thread;  
	unsigned threadID;
	thread = (HANDLE)_beginthreadex(NULL, 0, updateThread, 0, 0, &threadID);
}

unsigned __stdcall updateThread(void* data) {
	std::clock_t initial = std::clock();
	double duration = 0;
	int tempSize = clientListSize;

	start = false;

	while (tempSize == clientListSize) {
		if (!start) {
			duration = (std::clock() - initial) / (double)CLOCKS_PER_SEC;
			if (duration > 5) {
				start = true;
				for (Client client : clientList) {
					threadSendStr = "advert->start";
					sendMessage(&threadSendStr[0u], client);
				}
			}
		}
		else {
			duration = (std::clock() - initial) / (double)CLOCKS_PER_SEC;

			if (duration > 0.2) {
				for (int x = 0; x < clientList.size(); x++) {
					if (clientList[x].isAlive) {
						for (int y = 0; y < clientList.size(); y++) {
							if (x != y) {
								threadSendStr = "advert->board_data:" + std::to_string(clientList[x].uniqueID) + ":";
								threadSendStr += std::to_string(clientList[x].position.x) + ":";
								threadSendStr += std::to_string(clientList[x].position.y) + ":";
								threadSendStr += std::to_string(clientList[x].angle);

								sendMessage(&threadSendStr[0u], clientList[y]);
							}
						}
					}
				}

				initial = std::clock();
			}
		}
	}

	_endthreadex(0);
	return 0;
}

void networkClose() {
	closesocket(s);
	WSACleanup();
}

void sendMessage(char message[], Client client) {
	sendto(s, message, strlen(message), 0, (struct sockaddr *) &client.address, client.addrLength);
}