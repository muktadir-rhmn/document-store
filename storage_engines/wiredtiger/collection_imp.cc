//
// Created by Muktadir Rahman on 8/9/20.
//

#include "collection_imp.h"
#include "../../utils/logger/logger.h"

int CollectionImp::id = 1;

CollectionImp::CollectionImp(WT_CURSOR *cursor) {
    cursor_ = cursor;

    //todo: retrieve map from the actual database
    fieldNameIDMap_ = new FieldNameIDMap();
	fieldNameIDMap_->putPair("name", 0);
	fieldNameIDMap_->putPair("address", 1);
//	fieldNameIDMap_->putPair("last_login", 2);
//	fieldNameIDMap_->putPair("propic", 3);
}

CollectionImp::~CollectionImp() {
    delete fieldNameIDMap_;
}

void CollectionImp::insertDocument(RawData& rawData) {
    WT_ITEM key;
    String idStr = std::to_string(id);
    key.data = idStr.c_str();
    key.size = idStr.size();
    DEBUG_MSG("document id: " << idStr);
    cursor_->set_key(cursor_, &key);
    id++;

    WT_ITEM item;
    item.data = rawData.bytes;
    item.size = rawData.size;
    cursor_->set_value(cursor_, &item);

    DEBUG_MSG("INSERTING a document to the collection");
    cursor_->insert(cursor_);
    DEBUG_MSG("Done insertion");
}

ByteOutputStream CollectionImp::getDocuments() {
    DEBUG_MSG("Getting documents from DB:");
    ByteOutputStream outputStream(1024);

    cursor_->reset(cursor_);
    while (cursor_->next(cursor_) == 0) {
        DEBUG_MSG("\tFound one document");
        WT_ITEM key, value;
        cursor_->get_key(cursor_, &key);
        cursor_->get_value(cursor_, &value);

        DEBUG_MSG("\tone document with key: " << (char*) key.data << " and doc size: " << value.size);

        outputStream.appendBytes(value.data, value.size);
    }
    return outputStream;
}
