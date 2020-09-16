//
// Created by Muktadir Rahman on 13/9/20.
//

#ifndef DOCUMENT_STORE_DOCUMENT_READER_H
#define DOCUMENT_STORE_DOCUMENT_READER_H

#include "../utils/data/input_stream.h"
#include "array_reader.h"
#include "document_typedefs.h"

namespace document {
typedef int16 fieldType;
typedef int16 fieldId;

class DocumentReader {
public:
	virtual ~DocumentReader() = default;

	/** cursor movement interface*/
	virtual bool hasNext()=0;

	virtual void next()=0;

	/** reader interface */
	virtual ccstring fieldIdAsCString()=0;
	virtual fieldId_t fieldIdAsInt()=0;

	virtual document::fieldType_t fieldType()=0;

	virtual int32 valueAsInt32()=0;
	virtual int64 valueAsInt64()=0;
	virtual String valueAsString()=0;
	virtual DocumentReader* valueAsDocument()=0;

//	virtual ArrayReader getCurArray()=0;

};

}

#endif //DOCUMENT_STORE_MDR_DOCUMENT_READER_H
