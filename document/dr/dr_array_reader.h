//
// Created by Muktadir Rahman on 17/9/20.
//

#ifndef DOCUMENT_STORE_DR_ARRAY_READER_H
#define DOCUMENT_STORE_DR_ARRAY_READER_H

#include "../array_reader.h"

namespace document { namespace dr {

class DRArrayReader : public ArrayReader {
public:
	explicit DRArrayReader(InputStream* inputStream);

	bool next() override;

	fieldType_t curElementType() override;

	int64 curValueAsInt64() override;

	String curValueAsString() override;

private:
	InputStream* inputStream_;
	arraySize_t arraySize_;
	arraySize_t nBytesRead_;

	fieldType_t curElementType_;

	bool readCurElementType_;
	bool readCurElementValue_;

};

}}

#endif //DOCUMENT_STORE_DR_ARRAY_READER_H
