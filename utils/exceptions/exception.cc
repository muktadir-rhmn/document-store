//
// Created by Muktadir Rahman on 6/9/20.
//

#include <cstring>
#include "exception.h"
#include "../../processor/request_response_constants.h"

Exception::Exception(const char *message) {
    messageLen_ = strlen(message) + 2;
    message_ = new char[messageLen_];
    message_[0] = ResponseStatus.FAILURE;
    strcpy(message_ + 1, message);
}

const char *Exception::GetMessage() {
    return message_;
}

int Exception::GetMessageLength() const {
    return messageLen_;
}
