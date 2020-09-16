//
// Created by Muktadir Rahman on 7/9/20.
//

#ifndef DOCUMENT_STORE_DATABASE_IMP_H
#define DOCUMENT_STORE_DATABASE_IMP_H

#include "../../storage_api/database.h"
#include "lib/wiredtiger.h"

namespace storageengine { namespace wiredtiger{

class DatabaseImp : public Database {
public:
    explicit DatabaseImp(WT_SESSION *session);
    ~DatabaseImp();

    void createCollection(const String& collectionName) override;
    void renameCollection(const String& oldCollectionName, const String& newCollectionName) override;
    void deleteCollection(const String& collectionName) override;
    Collection* getCollection(const String& collectionName) override;

private:
    WT_SESSION *session_;
    static String getCollectionNameString(const String& collectionName);
};

}}

#endif //DOCUMENT_STORE_DATABASE_IMP_H
