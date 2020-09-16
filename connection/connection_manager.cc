//
// Created by Muktadir Rahman on 6/9/20.
//

#include <iostream>
#include "connection_manager.h"
#include "../utils/socket/socket_exception.h"
#include "../utils/exceptions/exception.h"

void HandleConnectionRequest(ConnectionManager *connectionManager, ClientSocket clientSocket);

ConnectionManager::ConnectionManager(int port, int maxNumberOfConnections) {
    std::cout << "Port: " << port << std::endl;
    std::cout << "maximum number of connections: " << maxNumberOfConnections << std::endl;

    try {
        serverSocket_ = new ServerSocket(port);
        maxNumberOfConnections_ = maxNumberOfConnections;
        curNumberOfConnections_ = 0;
    } catch (SocketException& exception) {
        std::cout << "Connection Error: " << exception.GetMessage() << std::endl;
        exit(1);
    }
}

ConnectionManager::~ConnectionManager() {
    delete serverSocket_;
}

void ConnectionManager::Serve() {
    while (true) {
        ClientSocket clientSocket = serverSocket_->acceptRequest();
        std::thread * t = new std::thread(HandleConnectionRequest, this, clientSocket);
        t->detach();
        threadMap_[t->get_id()] = t;
    }
}

void ConnectionManager::AllocateConnection() {
    bool success ;
    mtxConnections.lock();
    if (curNumberOfConnections_ < maxNumberOfConnections_) {
        curNumberOfConnections_++;
        success = true;
    } else {
        success = false;
    }
    mtxConnections.unlock();

    if (!success) throw Exception("No Connection Available");
}

void ConnectionManager::ReleaseConnection() {
    std::thread::id threadID = std::this_thread::get_id();

    mtxConnections.lock();
    curNumberOfConnections_--;

    for(auto & t : threadsToDelete_) {
        delete t;
    }
    threadsToDelete_.clear();

    threadsToDelete_.push_back(threadMap_[threadID]);
    threadMap_.erase(threadID);

    mtxConnections.unlock();
}
