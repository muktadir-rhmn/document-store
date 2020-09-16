#include <iostream>
#include "connection/connection_manager.h"

#define DEFAULT_PORT 8080
#define DEFAULT_NUM_OF_CONNECTIONS 5

int main(int argc, char* argv[]) {
    std::cout << "Starting the Database" << std::endl;

    int port = DEFAULT_PORT;
    int maxNumOfConnections = DEFAULT_NUM_OF_CONNECTIONS;

    for (int i = 1; i < argc; i += 2) {
        if (!strcmp(argv[i], "-port")) {
            int t = atoi(argv[i + 1]);
            if (t > 0) port = t;
        } else if (!strcmp(argv[i], "-maxConnection")) {
            int t = atoi(argv[i + 1]);
            if (t > 0) maxNumOfConnections = t;
        }
    }

    ConnectionManager connectionManager(port, maxNumOfConnections);
    connectionManager.Serve();

    return 0;
}
