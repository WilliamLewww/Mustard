#include "client.h"

bool clientEquals(Client a, Client b) {
	if (a.uniqueID == b.uniqueID || ntohs(a.address.sin_port) == ntohs(b.address.sin_port)) {
		return true;
	}

	return false;
}