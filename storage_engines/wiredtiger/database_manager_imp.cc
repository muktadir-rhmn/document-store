//
// Created by Muktadir Rahman on 7/9/20.
//

#include <string>
#include "database_manager_imp.h"
#include "database_imp.h"
#include "../../utils/exceptions/exception.h"
#include "../../utils/logger/logger.h"

namespace storageengine { namespace wiredtiger{

DatabaseManagerImp::DatabaseManagerImp() {
    //open one connection for each of the databases
    String databaseName = "test";

    String databaseDirectory = GetDatabaseDirectory(databaseName);

    String configurations;
    configurations += "create,";
    configurations += COMPRESSOR_CONFIGURATION;
//    configurations += DURABILITY_CONFIGURATION;
    DEBUG_MSG("Database configuration string: " << configurations);

    int status = wiredtiger_open(databaseDirectory.c_str(), NULL, configurations.c_str(), &connection);
    if (status != 0) {
		throw Exception("Failed to connect to the database");
    }

    connectionMap_[databaseName] = connection;
}

DatabaseManagerImp::~DatabaseManagerImp() {
    for (auto &itr : connectionMap_) {
        WT_CONNECTION *connection = itr.second;
        connection->close(connection, NULL);
    }
}

void DatabaseManagerImp::createDatabase(String databaseName) {

}

Database *DatabaseManagerImp::getDatabase(String databaseName) {
    WT_CONNECTION *connection = connectionMap_[databaseName];
    if (connection == nullptr) {
        throw Exception("Database not found");
    }

    WT_SESSION *session;
    connection->open_session(connection, NULL, NULL, &session);
    return new DatabaseImp(session);
}

String DatabaseManagerImp::GetDatabaseDirectory(String &databaseName) {
    return "./databases/" + databaseName;
}

void DatabaseManagerImp::releaseDatabase(Database *database) {
    delete (DatabaseImp *) database;
}

}}