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

	bool next() override;

	ccstring curFieldIdAsCString() override;

	fieldType_t curFieldType() override;

	fieldId_t curFieldIdAsInt() override;

	int64 curValueAsInt64() override;

	String curValueAsString() override;

	DocumentReader* curValueAsDocument() override;

private:
	InputStream* inputStream_;
	docSize_t documentSize_;
	docSize_t nBytesRead_;

	int curFieldIdType_;
	String curFieldName_;
	fieldId_t curFieldId_=-1;

	fieldType_t curFieldType_;
	int curFieldValueSize_;
	byte* curFieldValue_= nullptr; //todo: now current field is copied and stored in this buffer. But I can improve its performance by removing this buffer and directly returning data from the stream

	ByteInputStream* lastByteInputStream_ = nullptr;
	DRDocumentReader* lastDocumentValue_ = nullptr;

	///this function has the logic of how a field of a document is represented
	void loadNextField();
	inline void loadNextFieldId();
	inline void loadNextFieldValue();
};

}}
#endif //DOCUMENT_STORE_DR_DOCUMENT_READER_H
