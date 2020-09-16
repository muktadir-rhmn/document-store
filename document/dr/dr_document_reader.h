//
// Created by Muktadir Rahman on 14/9/20.
//

#ifndef DOCUMENT_STORE_DR_DOCUMENT_READER_H
#define DOCUMENT_STORE_DR_DOCUMENT_READER_H

#include "../document_reader.h"
#include "../../utils/data/byte_input_stream.h"
#include "../bson_constants.h"
#include "../document_typedefs.h"

namespace document { namespace  dr {

class DRDocumentReader : public document::DocumentReader {
public:
	explicit DRDocumentReader(InputStream* inputStream, int fieldIdType = 0);
	~DRDocumentReader() override;

	bool hasNext() override;

	void next() override;

	ccstring fieldIdAsCString() override;

	document::fieldType_t fieldType() override;

	fieldId_t fieldIdAsInt() override;

	int32 valueAsInt32() override;

	int64 valueAsInt64() override;

	String valueAsString() override;

	DocumentReader* valueAsDocument() override;

private:
	InputStream* inputStream_;
	docSize_t documentSize_;
	docSize_t nBytesRead_;
	bool readingFinished_;

	int curFieldIdType_;
	String curFieldName_;
	fieldId_t curFieldId_=-1;

	fieldType_t curFieldType_;
	int curFieldValueSize_;
	byte* curFieldValue_= nullptr;

	ByteInputStream* lastByteInputStream_ = nullptr;
	DRDocumentReader* lastDocumentValue_ = nullptr;

	///this function has the logic of how a field of a document is represented
	void loadNextField();
	inline void loadNextFieldId();
	inline void loadNextFieldValue();
};

}}
#endif //DOCUMENT_STORE_DR_DOCUMENT_READER_H
