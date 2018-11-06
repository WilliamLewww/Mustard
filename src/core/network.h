#pragma once
#include <winsock2.h>
#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <process.h>

#pragma comment(lib,"ws2_32.lib")

#define BUFLEN 512
#define PORT 8888

static HANDLE receiveThread;

static WSADATA wsa;
static struct sockaddr_in server;
static int s, slen = sizeof(server);
static char buf[BUFLEN];
static bool messageReceived;

extern bool netConnected;
extern std::vector<std::string> replyList;
extern std::vector<std::string> advertList;

void initializeWinsock(char IP[]);
void closeWinsock();
void sendMessage(char message[]);

void receiveMessage();
void receiveInitialMessage();