//
// Created by Muktadir Rahman on 17/9/20.
//

#include "dr_array_writer.h"
#include "../bson_constants.h"

namespace document { namespace dr {

DRArrayWriter::DRArrayWriter(ByteOutputStream* outputStream) {
	outputStream_ = outputStream;

	arraySizeOffset_ = outputStream_->allocate(sizeof(arraySize_t));
	arraySize_ = sizeof(arraySize_t);
	updateArraySizeInStream();
}

void DRArrayWriter::appendInt64(int64 element) {
	arraySize_ += outputStream_->appendBytes(&FieldType.INT64, sizeof(fieldType_t));

	arraySize_ += outputStream_->appendInt64(element);

	updateArraySizeInStream();
}

void DRArrayWriter::appendCString(ccstring element, stringSize_t size) {
	arraySize_ += outputStream_->appendBytes(&FieldType.STRING, sizeof(fieldType_t));

	arraySize_ += outputStream_->appendBytes(&size, sizeof(stringSize_t));
	arraySize_ += outputStream_->appendBytes(element, size);

	updateArraySizeInStream();
}

}}