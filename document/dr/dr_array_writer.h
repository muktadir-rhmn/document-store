//
// Created by Muktadir Rahman on 17/9/20.
//

#ifndef DOCUMENT_STORE_DR_ARRAY_WRITER_H
#define DOCUMENT_STORE_DR_ARRAY_WRITER_H

#include "../array_writer.h"
#include "../document_typedefs.h"
#include "../../utils/data/byte_output_stream.h"

namespace document { namespace dr{

class DRArrayWriter : public ArrayWriter{
public:
	explicit DRArrayWriter(ByteOutputStream* outputStream);

	void appendInt64(int64 element) override;

	void appendCString(ccstring element, stringSize_t size) override;

	void appendCString(ccstring element) override { appendCString(element, strlen(element)); }

private:
	ByteOutputStream* outputStream_;
	arraySize_t arraySizeOffset_;
	arraySize_t arraySize_;

	void updateArraySizeInStream(){ outputStream_->setAllocatedData(arraySizeOffset_, sizeof(arraySize_t), &arraySize_); }
};

}}

#endif //DOCUMENT_STORE_DR_ARRAY_WRITER_H
