//
// Created by Muktadir Rahman on 6/9/20.
//

#include "user_manager.h"
#include "../utils/exceptions/exception.h"
#include "../utils/logger/logger.h"

UserManager* UserManager::instance_ = new UserManager();

User* UserManager::authenticate(String &databaseName, String &userName, String &password) {
    DEBUG_MSG(databaseName.size());
    DEBUG_MSG((databaseName == "test") << " " << userName << " " << password);
    bool isUser = databaseName == "test" && userName == "root" && password == "12345";
    if (!isUser) throw Exception("Authentication Failure");

    return new User();
}
