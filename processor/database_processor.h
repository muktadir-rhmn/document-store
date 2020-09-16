//
// Created by Muktadir Rahman on 7/9/20.
//

#ifndef DOCUMENT_STORE_DATABASE_PROCESSOR_H
#define DOCUMENT_STORE_DATABASE_PROCESSOR_H


#include "../connection/connection_descriptor.h"
#include "../storage_api/database.h"

class DatabaseProcessor {
public:
    static void processCreateCollection(Database* database, ConnectionDescriptor* conDescriptor);
    static void processRenameCollection(Database* database, ConnectionDescriptor* conDescriptor);
    static void processDeleteCollection(Database* database, ConnectionDescriptor* conDescriptor);
};


#endif //DOCUMENT_STORE_DATABASE_PROCESSOR_H
