//
// Created by Muktadir Rahman on 17/9/20.
//

#ifndef DOCUMENT_STORE_DR_ARRAY_READER_H
#define DOCUMENT_STORE_DR_ARRAY_READER_H

#include "../array_reader.h"
#include "../../utils/data/byte_input_stream.h"

namespace document { namespace dr {

class DRArrayReader : public ArrayReader {
public:
	DRArrayReader(RawData data);

	bool next() override;

	fieldType_t curElementType() override;

	int64 curValueAsInt64() override;

	String curValueAsString() override;

private:
	ByteInputStream* inputStream_;
	arraySize_t arraySize_;
	arraySize_t nBytesRead_;

	fieldType_t curElementType_;

	bool readCurElementType_;
	bool readCurElementValue_;

};

}}

#endif //DOCUMENT_STORE_DR_ARRAY_READER_H
