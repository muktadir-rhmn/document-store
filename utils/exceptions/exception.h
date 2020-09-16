//
// Created by Muktadir Rahman on 6/9/20.
//

#ifndef DOCUMENT_STORE_EXCEPTION_H
#define DOCUMENT_STORE_EXCEPTION_H

#include <exception>

class Exception : std::exception{
public:
    explicit Exception(const char* message);
    const char* GetMessage();
    int GetMessageLength() const;
private:
    char* message_;
    int messageLen_;
};


#endif //DOCUMENT_STORE_EXCEPTION_H
