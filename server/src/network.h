#pragma once
#include <ctime>
#include <algorithm>
#include <vector>
#include <string>
#include <stdio.h>
#include <winsock2.h>
#include <process.h>
#include "client.h"

#pragma comment(lib,"ws2_32.lib")

#define BUFLEN 512
#define PORT 8888

static HANDLE thread;

static std::string sendStr;
static std::string threadSendStr;

static bool start = false;
static int seed;

static Client tempClient, *knownClient;
static std::vector<Client> clientList;
static int clientListSize = 0;

static std::string newestMessage;

static SOCKET s;
static struct sockaddr_in server, si_other;
static int slen , recv_len;
static char buf[BUFLEN];
static WSADATA wsa;

void networkInitializeWinsock();
void networkCreateSocket();
void networkBindSocket();
void networkGenerateSeed();

void networkStartUpdate();
unsigned __stdcall updateThread(void* data);

Client *getClientFromID(int ID);

void networkInitialize();
void networkListen();
void networkClose();

void sendMessage(char message[], Client client);