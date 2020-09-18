//
// Created by Muktadir Rahman on 7/9/20.
//

#ifndef DOCUMENT_STORE_DATABASE_MANAGER_H
#define DOCUMENT_STORE_DATABASE_MANAGER_H

#include <string>
#include "database.h"

class DatabaseManager {
public:
    static DatabaseManager* GetInstance() {return instance_;}

    virtual void createDatabase(String databaseName)=0;
    virtual Database* getDatabase(String databaseName)=0;
    virtual void releaseDatabase(Database* database)=0;
private:
    static DatabaseManager* instance_;
};


#endif //DOCUMENT_STORE_DATABASE_MANAGER_H
