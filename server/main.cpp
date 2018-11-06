#include "src\network.h"

Network network;
bool isRunning = true;

int main(int argc, char *argv[]) { 
    network.initialize();
    while(isRunning) { network.listen(); }
 	network.close();
    
    return 0;
}