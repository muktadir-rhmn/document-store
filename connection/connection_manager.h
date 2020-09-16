//
// Created by Muktadir Rahman on 6/9/20.
//

#ifndef DOCUMENT_STORE_CONNECTIONMANAGER_H
#define DOCUMENT_STORE_CONNECTIONMANAGER_H
#include <thread>
#include <mutex>
#include <map>
#include <vector>
#include "../utils/socket/server_socket.h"
#include "../user/user_manager.h"

class ConnectionManager {
public:
    explicit ConnectionManager(int port, int maxNumberOfConnections);
    ~ConnectionManager();
    void Serve();
    void AllocateConnection();
    void ReleaseConnection();

private:
    ServerSocket* serverSocket_;
    int maxNumberOfConnections_;

    int curNumberOfConnections_;
    std::mutex mtxConnections;

    //to handle memory leak
    std::map<std::thread::id, std::thread*> threadMap_;
    std::vector<std::thread*> threadsToDelete_;
};

#endif //DOCUMENT_STORE_CONNECTIONMANAGER_H
