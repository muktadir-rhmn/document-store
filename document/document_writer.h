//
// Created by Muktadir Rahman on 13/9/20.
//

#ifndef DOCUMENT_STORE_DOCUMENT_WRITER_H
#define DOCUMENT_STORE_DOCUMENT_WRITER_H

#include "../typedefs.h"
#include "../utils/data/allocatable_output_stream.h"
#include "document_reader.h"

namespace document {

class DocumentWriter {
public:
	virtual void appendInt32(void* fieldId, int32 value)=0;
	virtual void appendInt64(void* fieldId, int64 value)=0;
	virtual void appendCString(void* fieldId, ccstring value, stringSize_t strSize=-1)=0;
	virtual void appendDocument(void* fieldId, DocumentWriter& value)=0;
	virtual AllocatableOutputStream* getOutputStream()=0;
};

}

#endif //DOCUMENT_STORE_DOCUMENT_WRITER_H
