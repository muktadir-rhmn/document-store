//
// Created by Muktadir Rahman on 7/9/20.
//

#ifndef DOCUMENT_STORE_DATABASE_H
#define DOCUMENT_STORE_DATABASE_H


#include <string>
#include "collection.h"

class Database {
public:
    virtual void createCollection(const String& collectionName)=0;
    virtual void renameCollection(const String& oldCollectionName, const String& newCollectionName)=0;
    virtual void deleteCollection(const String& collectionName)=0;
    virtual Collection* getCollection(const String& collectionName)=0;
private:

};


#endif //DOCUMENT_STORE_DATABASE_H
