//
// Created by Muktadir Rahman on 6/9/20.
//

#include "socket_exception.h"

SocketException::SocketException(const char *message) {
    message_ = message;
}

const char *SocketException::GetMessage() {
    return message_;
}
