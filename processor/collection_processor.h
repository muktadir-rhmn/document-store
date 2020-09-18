//
// Created by Muktadir Rahman on 7/9/20.
//

#ifndef DOCUMENT_STORE_COLLECTION_PROCESSOR_H
#define DOCUMENT_STORE_COLLECTION_PROCESSOR_H


#include "../connection/connection_descriptor.h"
#include "../storage/api/database.h"
#include "../storage/api/collection.h"

class CollectionProcessor {
public:
    static void processInsertDocument(Database* database, ConnectionDescriptor* conDescriptor);
    static void processUpdateDocument(Database* database, ConnectionDescriptor* conDescriptor);
    static void processDeleteDocument(Database* database, ConnectionDescriptor* conDescriptor);
    static void processQuery(Database* database, ConnectionDescriptor* conDescriptor);

private:
    static Collection* retrieveCollection(Database* database, ConnectionDescriptor* conDescriptor);
};


#endif //DOCUMENT_STORE_COLLECTION_PROCESSOR_H
