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
    fflush(stdout);
    memset(buf,'\0', BUFLEN);
     
   	recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &tempClient.address, &tempClient.addrLength);
    newestMessage = buf;

    if (newestMessage == "connect") {
        networkStartUpdate();

        clientListSize += 1;
        clientList.push_back({tempClient.address, tempClient.addrLength, clientListSize});

        sendMessage((char*)"connect", tempClient);

        str = "reply->seed:" + std::to_string(seed);
        sendMessage(&str[0u], tempClient);

        str = "reply->rain_seed:" + std::to_string(time(NULL));
        sendMessage(&str[0u], tempClient);

        str = "reply->player_count:" + std::to_string(clientListSize);
        sendMessage(&str[0u], tempClient);

        str = "reply->reset_full";
        sendMessage(&str[0u], tempClient);

        for (Client client : clientList) {
            if (!clientEquals(tempClient, client)) {
                str = "advert->new_client:" + std::to_string(clientListSize);
                sendMessage(&str[0u], client);

                str = "advert->rain_seed:" + std::to_string(time(NULL));
                sendMessage(&str[0u], tempClient);

                str = "advert->reset_full";
                sendMessage(&str[0u], client);
            }
        }
    }
     
    printf("%s:%d: ", inet_ntoa(tempClient.address.sin_addr), ntohs(tempClient.address.sin_port));
    printf("%s\n" , buf);
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
					str = "advert->start";
	                sendMessage(&str[0u], client);
	            }
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