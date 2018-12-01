#pragma once
#include <winsock2.h>
#include "vector2.h"

struct Client {
	sockaddr_in address;
	int addrLength = sizeof(address);
	int uniqueID;

	int width, height;

	Vector2 position;
	double angle;

	bool isAlive = false;
};

void setClientData(Client &client, Vector2 position, double angle);
bool clientEquals(Client a, Client b);

void coutClient(Client client);