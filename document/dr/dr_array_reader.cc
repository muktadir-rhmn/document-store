//
// Created by Muktadir Rahman on 17/9/20.
//

#include "dr_array_reader.h"
#include "../../utils/debug/debug.h"
#include "../bson_constants.h"

namespace document{ namespace dr {

DRArrayReader::DRArrayReader(InputStream* inputStream) {
	inputStream_ = inputStream;

	inputStream_->nextBytes(&arraySize_, sizeof(arraySize_t));
	nBytesRead_ += sizeof(arraySize_t);
	DEBUG_MSG("An array of size: " << arraySize_);
}

bool DRArrayReader::next() {
	if (nBytesRead_ >= arraySize_) {
		if (nBytesRead_ > arraySize_) throw InternalException("DRArrayReader::next(): nBytesRead_ > arraySize_ => there is a bug");
		return false;
	}

	readCurElementType_ = false;
	readCurElementValue_ = false;

	return false;
}

fieldType_t DRArrayReader::curElementType() {
	ASSERT(!readCurElementType_, "Element can be read only once");

	inputStream_->nextBytes(&curElementType_, sizeof(fieldType_t));
	nBytesRead_ += sizeof(fieldType_t);
	readCurElementType_ = true;
	return curElementType_;
}

int64 DRArrayReader::curValueAsInt64() {
	ASSERT(!readCurElementType_, "Type must be read before value");
	ASSERT(curElementType_ == FieldType.INT64, "Current element is not INT64");
	ASSERT(!readCurElementValue_, "Element can be read only once");

	int64 val;
	inputStream_->nextBytes(&val, sizeof(int64));
	return val;
}

String DRArrayReader::curValueAsString() {
	ASSERT(!readCurElementType_, "Type must be read before value");
	ASSERT(curElementType_ == FieldType.STRING, "Current element is not String");
	ASSERT(!readCurElementValue_, "Element can be read only once");

	stringSize_t size;
	inputStream_->nextBytes(&size, sizeof(stringSize_t));

	char str[size];
	inputStream_->nextBytes(str, size);

	return String(str, size);
}

}}