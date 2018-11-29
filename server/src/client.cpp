#include "client.h"

void setClientData(Client &client, Vector2 position, double angle) {
	client.position = position;
	client.angle = angle;
}

bool clientEquals(Client a, Client b) {
	if (a.uniqueID == b.uniqueID || ntohs(a.address.sin_port) == ntohs(b.address.sin_port)) {
		return true;
	}

	return false;
}

void coutClient(Client client) {
	std::cout << "Client #" << client.uniqueID << ": [" << client.position << "], " << client.angle << std::endl;
}