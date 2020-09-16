//
// Created by Muktadir Rahman on 5/9/20.
//

#include <cstdlib>
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <zconf.h>

#include "server_socket.h"
#include "socket_exception.h"

ServerSocket::ServerSocket(int port) {
    port_ = port;
    is_listening_ = false;

    if ((server_socket_fd_ = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        throw SocketException("Failed to create the socket");
    }

    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port_);

    // Forcefully attaching socket to the port 8080
    if (bind(server_socket_fd_, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        throw SocketException("Failed to bind the socket to the port");
    }
}

ClientSocket ServerSocket::acceptRequest() {
    if (!is_listening_) listenForRequest();

    int client_socket_fd;
    sockaddr_in client_address;
    int address_len = sizeof(client_address);
    if ((client_socket_fd = accept(server_socket_fd_, (struct sockaddr*) &client_address,
										  (socklen_t*) &address_len)) < 0) {
        throw SocketException("Failed to acceptRequest new connection");
    }

    return {client_socket_fd, client_address}; //need to released by the client code
}

void ServerSocket::listenForRequest() {
    if (listen(server_socket_fd_, n_tcp_connection_q_size_) < 0) {
        throw SocketException("Failed to listenForRequest to the socket");
    }
    is_listening_ = true;
}

void ServerSocket::closeSocket() {
	close(server_socket_fd_);
}
