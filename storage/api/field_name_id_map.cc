//
// Created by Muktadir Rahman on 8/9/20.
//

#include "field_name_id_map.h"
#include "../../utils/debug/debug.h"

int FieldNameIDMap::getFieldId(String fieldName) {
    //todo: add to the map if not found
    //todo: make thread safe
    return map_[fieldName];
}

void FieldNameIDMap::putPair(String fieldName, int id) {
    map_[fieldName] = id;
}

void FieldNameIDMap::outputData(BufferedSocketOutputStream* outputStream) {
    DEBUG_MSG("Sending FieldNameIDMap");

    for (auto & itr : map_) {
        String fieldName = itr.first;
        int32 fieldID = itr.second;

        DEBUG_MSG("(" << fieldName << ", " << fieldID << ")");

        outputStream->appendInt32(fieldID);
		outputStream->appendCString(fieldName.c_str(), fieldName.size());
    }
	outputStream->appendInt32(-1);
}
