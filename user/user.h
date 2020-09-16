//
// Created by Muktadir Rahman on 6/9/20.
//

#ifndef DOCUMENT_STORE_USER_H
#define DOCUMENT_STORE_USER_H


#include <string>
#include "../typedefs.h"

class User {
public:
    bool hasPermission(String& collectionName, const int opCode);

};


#endif //DOCUMENT_STORE_USER_H
