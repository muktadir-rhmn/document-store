//
// Created by Muktadir Rahman on 7/9/20.
//

#include "database_imp.h"
#include "collection_imp.h"
#include "../../utils/exceptions/exception.h"
#include "../../utils/debug/debug.h"

namespace storageengine { namespace wiredtiger{

DatabaseImp::DatabaseImp(WT_SESSION *session) {
    session_ = session;
}

DatabaseImp::~DatabaseImp() {
    session_->close(session_, NULL);
}

void DatabaseImp::createCollection(const String& collectionName) {
    String nameString = getCollectionNameString(collectionName);
    DEBUG_MSG(nameString);
    int status = session_->create(session_, nameString.c_str(), "key_format=u,value_format=u"); /// format ref: https://source.wiredtiger.com/develop/schema.html#schema_column_types
    if (status != 0) {
        throw Exception("Failed to create the collection");
    }
}

void DatabaseImp::renameCollection(const String &oldCollectionName, const String &newCollectionName) {
    String oldNameString = getCollectionNameString(oldCollectionName);
    String newNameString = getCollectionNameString(newCollectionName);
    int status = session_->rename(session_, oldNameString.c_str(), newNameString.c_str(), NULL);
    if (status != 0) {
        throw Exception("Failed to rename the collection");
    }
}

void DatabaseImp::deleteCollection(const String &collectionName) {
    String nameString = getCollectionNameString(collectionName);
    int status = session_->drop(session_, nameString.c_str(), NULL);
    if (status != 0) {
        throw Exception("Failed to drop the collection");
    }
}

Collection *DatabaseImp::getCollection(const String &collectionName) {
    WT_CURSOR *cursor;
    String nameString = getCollectionNameString(collectionName);
    int status = session_->open_cursor(session_, nameString.c_str(), NULL, "raw", &cursor);
    if (status != 0) {
		throw Exception("Collection not found");
    }
    return new CollectionImp(cursor);
}

String DatabaseImp::getCollectionNameString(const String &collectionName) {
    return "table:" + collectionName;
}

}}