//
// Created by Muktadir Rahman on 13/9/20.
//

#ifndef DOCUMENT_STORE_ARRAY_WRITER_H
#define DOCUMENT_STORE_ARRAY_WRITER_H

#include "../utils/data/allocatable_output_stream.h"
#include "document_typedefs.h"

namespace document{

class ArrayWriter {
public:
	virtual void appendInt64(int64 element)=0;
	virtual void appendCString(ccstring element, stringSize_t size)=0;
	virtual void appendCString(ccstring element)=0;
};

}
#endif //DOCUMENT_STORE_ARRAY_WRITER_H
