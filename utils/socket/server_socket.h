//
// Created by Muktadir Rahman on 5/9/20.
//

#ifndef TPC_CPP_POC_SERVERSOCKET_H
#define TPC_CPP_POC_SERVERSOCKET_H

#include "client_socket.h"

class ServerSocket {
public:
    explicit ServerSocket(int port);
    ClientSocket acceptRequest();
    void closeSocket();
private:
    int n_tcp_connection_q_size_ = 100;
    int port_;
    int server_socket_fd_;
    bool is_listening_;
    void listenForRequest();
};


#endif //TPC_CPP_POC_SERVERSOCKET_H
