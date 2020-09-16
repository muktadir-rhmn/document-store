//
// Created by Muktadir Rahman on 8/9/20.
//

#ifndef DOCUMENT_STORE_COLLECTION_IMP_H
#define DOCUMENT_STORE_COLLECTION_IMP_H


#include "../../storage_api/collection.h"
#include "lib/wiredtiger.h"

class CollectionImp : public Collection {
public:
    explicit CollectionImp(WT_CURSOR* cursor);
    ~CollectionImp();

    FieldNameIDMap* getFieldNameIdMap() override {return fieldNameIDMap_;};

    void insertDocument(RawData& rawData) override;

    ByteOutputStream getDocuments() override;

private:
    static int id;
    WT_CURSOR* cursor_;
    FieldNameIDMap * fieldNameIDMap_;
};


#endif //DOCUMENT_STORE_COLLECTION_IMP_H
