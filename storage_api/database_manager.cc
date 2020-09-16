//
// Created by Muktadir Rahman on 7/9/20.
//

#include "database_manager.h"
#include "../storage_engines/wiredtiger/database_manager_imp.h"

DatabaseManager* DatabaseManager::instance_ = new storageengine::wiredtiger::DatabaseManagerImp();
