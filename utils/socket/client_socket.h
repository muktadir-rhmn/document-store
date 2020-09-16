//
// Created by Muktadir Rahman on 5/9/20.
//

#ifndef TPC_CPP_POC_CLIENTSOCKET_H
#define TPC_CPP_POC_CLIENTSOCKET_H

#include <string>
#include <netinet/in.h>

class ClientSocket {
public:
    ClientSocket(int socket_fd, sockaddr_in client_address);

    int getPort() const;
    std::string getAddress() const;

    int readData(void* buffer, int max_bytes_to_read) const;
    int writeData(const void* buffer, int bytes_to_write) const;

    void closeSocket(); //we should not use a destructor to closeSocket the connection.
                // Reason: a client socket may be copied multiple times as it travels from one function to another.
                //      One copy (eg. local variable) may be destroyed and we may proceed with other copies.
                //      If we closeSocket the connection in the destructor, the connection will be closed though we may need to access the connection from another copy
private:
    int socket_fd_;
    sockaddr_in client_address_{};
};


#endif //TPC_CPP_POC_CLIENTSOCKET_H
