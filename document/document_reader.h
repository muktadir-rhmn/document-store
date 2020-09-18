//
// Created by Muktadir Rahman on 13/9/20.
//

#ifndef DOCUMENT_STORE_DOCUMENT_READER_H
#define DOCUMENT_STORE_DOCUMENT_READER_H

#include "../utils/data/input_stream.h"
#include "array_reader.h"
#include "document_typedefs.h"

namespace document {

class DocumentReader {
public:
	enum class FieldIdType { kInteger, kString};

	virtual ~DocumentReader() = default;

	/** cursor movement interface*/
	virtual bool next()=0; ///moves cursor to the next position and returns false if there is no next field.

	/** reader interface */
	virtual ccstring curFieldIdAsCString()=0;
	virtual fieldId_t curFieldIdAsInt()=0;

	virtual fieldType_t curFieldType()=0;

	virtual int64 curValueAsInt64()=0;
	virtual String curValueAsString()=0;
	virtual DocumentReader* curValueAsDocument()=0;

};

}

#endif //DOCUMENT_STORE_MDR_DOCUMENT_READER_H
