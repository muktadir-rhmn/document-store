//
// Created by Muktadir Rahman on 6/9/20.
//

#ifndef TPC_CPP_POC_SOCKETEXCEPTION_H
#define TPC_CPP_POC_SOCKETEXCEPTION_H

#include <exception>
class SocketException : public std::exception{
public:
    explicit SocketException(const char* message);
    const char* GetMessage();
private:
    const char* message_;
};

#endif //TPC_CPP_POC_SOCKETEXCEPTION_H
