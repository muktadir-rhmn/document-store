//
// Created by Muktadir Rahman on 6/9/20.
//

#ifndef DOCUMENT_STORE_USER_MANAGER_H
#define DOCUMENT_STORE_USER_MANAGER_H

#include <string>
#include "user.h"
#include "../typedefs.h"

class UserManager {
public:
    static UserManager* getInstance() {return instance_;};

    User* authenticate(String& databaseName, String& userName, String& password);

private:
    static UserManager* instance_;

    UserManager()= default;
};


#endif //DOCUMENT_STORE_USER_MANAGER_H
