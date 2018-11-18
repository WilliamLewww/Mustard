#include "network_oop.h"

void Network::initialize() {
	initializeWinsock();
	createSocket();
	bindSocket();
    generateSeed();
}

void Network::generateSeed() {
    seed = time(NULL);
}

void Network::initializeWinsock() {
	printf("\nInitializing Winsock...\n");
	slen = sizeof(tempClient.addrLength);
	WSAStartup(MAKEWORD(2,2),&wsa);
}

void Network::createSocket() {
	printf("Creating Socket...\n");
	server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );

    s = socket(AF_INET , SOCK_DGRAM , 0);
}

void Network::bindSocket() {
	printf("Binding Socket...\n");
    bind(s ,(struct sockaddr*)&server , sizeof(server));
    printf("Complete\n\n");
    printf("Listening for Messages:\n");
}

void Network::listen() {
    fflush(stdout);
    memset(buf,'\0', BUFLEN);
     
   	recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &tempClient.address, &tempClient.addrLength);
    newestMessage = buf;

    if (newestMessage == "connect") {
        start = false;
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

void Network::updateThread() {
    if (!start && clientListSize > 0) {
        std::clock_t initial;
        if (startTimer = -1) { startTimer = std::clock(); }

        if ((std::clock() - initial) / (double)CLOCKS_PER_SEC > 5) {
            startTimer = -1;
            start = true;

            for (Client client : clientList) {
                str = "advert->start";
                sendMessage(&str[0u], client);
            }
        }
    }
}

void Network::close() {
	closesocket(s);
    WSACleanup();
}

void Network::sendMessage(char message[], Client client) {
    sendto(s, message, strlen(message), 0, (struct sockaddr *) &client.address, client.addrLength);
}