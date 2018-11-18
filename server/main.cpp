#include "src\network.h"

bool isRunning = true;

int main(int argc, char *argv[]) { 
    networkInitialize();
    while(isRunning) { networkListen(); }
 	networkClose();
    
    return 0;
}