//
// Created by Muktadir Rahman on 13/9/20.
//

#ifndef DOCUMENT_STORE_ARRAY_READER_H
#define DOCUMENT_STORE_ARRAY_READER_H

#include "../utils/data/input_stream.h"
#include "document_typedefs.h"

namespace document{

class ArrayReader {
public:
	virtual bool next()=0; ///moves the cursor to the next position and return false if there is no element available to read

	///current cursor reading logic
	virtual fieldType_t curElementType()=0;

	virtual int64 curValueAsInt64()=0;
	virtual String curValueAsString()=0;
};

}

#endif //DOCUMENT_STORE_ARRAY_READER_H
