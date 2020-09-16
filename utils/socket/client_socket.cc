//
// Created by Muktadir Rahman on 5/9/20.
//

#include <zconf.h>
#include <arpa/inet.h>
#include <iostream>
#include "client_socket.h"

ClientSocket::ClientSocket(int socket_fd, sockaddr_in client_address) {
    socket_fd_ = socket_fd;
    client_address_ = client_address;
}

int ClientSocket::readData(void *buffer, int max_bytes_to_read) const {
    int n_bytes_read = read(socket_fd_, buffer, max_bytes_to_read);
    return n_bytes_read;
}

int ClientSocket::writeData(const void *buffer, int bytes_to_write) const {
    int n_bytes_written = send(socket_fd_, buffer, bytes_to_write, 0);
    return n_bytes_written;
}

int ClientSocket::getPort() const {
    return client_address_.sin_port;
}

std::string ClientSocket::getAddress() const {
    std::string address(inet_ntoa(client_address_.sin_addr));
    return address;
}

void ClientSocket::closeSocket() {
	close(socket_fd_);
}
