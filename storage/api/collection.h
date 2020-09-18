//
// Created by Muktadir Rahman on 7/9/20.
//

#ifndef DOCUMENT_STORE_COLLECTION_H
#define DOCUMENT_STORE_COLLECTION_H


#include <map>
#include "field_name_id_map.h"
#include "../../utils/data/byte_output_stream.h"

class Collection {
public:
    virtual void insertDocument(RawData& document)=0;
//    virtual void updateDocument()=0;
//    virtual void deleteDocument()=0;
    virtual ByteOutputStream getDocuments()=0;
    virtual FieldNameIDMap* getFieldNameIdMap()=0;
};


#endif //DOCUMENT_STORE_COLLECTION_H
