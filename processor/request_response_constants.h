//
// Created by Muktadir Rahman on 9/9/20.
//

#ifndef DOCUMENT_STORE_REQUEST_RESPONSE_CONSTANTS_H
#define DOCUMENT_STORE_REQUEST_RESPONSE_CONSTANTS_H


#include "../typedefs.h"

struct {
    const byte CLOSE_CONNECTION = 0x00;

    const byte AUTHENTICATION = 0x11;

    const byte CREATE_COLLECTION = 0x21;
    const byte RENAME_COLLECTION = 0x22;
    const byte DELETE_COLLECTION = 0x23;

    const byte INSERT_DOCUMENT = 0x31;
    const byte UPDATE_DOCUMENT = 0x32;
    const byte DELETE_DOCUMENT = 0x33;
    const byte QUERY_DOCUMENT = 0x34;
} OpCode;

struct {
    const byte SUCCESS = 0x00;
    const byte FAILURE = 0x01;
} ResponseStatus;

#endif //DOCUMENT_STORE_REQUEST_RESPONSE_CONSTANTS_H
