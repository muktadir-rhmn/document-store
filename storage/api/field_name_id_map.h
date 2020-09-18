//
// Created by Muktadir Rahman on 8/9/20.
//

#ifndef DOCUMENT_STORE_FIELD_NAME_ID_MAP_H
#define DOCUMENT_STORE_FIELD_NAME_ID_MAP_H


#include <string>
#include <map>
#include "../../typedefs.h"
#include "../../utils/data/byte_input_stream.h"
#include "../../utils/socket/buffered_output_stream.h"

class FieldNameIDMap {
public:
    int getFieldId(String fieldName);

    void putPair(String fieldName, int id);
    void outputData(BufferedSocketOutputStream* outputStream);
private:
    Map<String, int> map_;
};

#endif //DOCUMENT_STORE_FIELD_NAME_ID_MAP_H
