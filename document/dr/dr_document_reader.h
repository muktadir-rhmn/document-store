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

class DRDocumentReader : public DocumentReader {
public:

	explicit DRDocumentReader(InputStream* inputStream, FieldIdType fieldIdType = FieldIdType::kInteger);
	explicit DRDocumentReader(ByteInputStream inputStream, FieldIdType fieldIdType = FieldIdType::kInteger);
	~DRDocumentReader() override;

	bool next() override;

	ccstring curFieldIdAsCString() override;

	fieldType_t curFieldType() override;

	fieldId_t curFieldIdAsInt() override;

	int64 curValueAsInt64() override;

	String curValueAsString() override;

	DocumentReader* curValueAsDocument() override;

private:
	ByteInputStream inputStream_;
	docSize_t documentSize_;
	docSize_t nBytesRead_;

	FieldIdType curFieldIdType_;
	String curFieldName_;
	fieldId_t curFieldId_=-1;

	fieldType_t curFieldType_;
	RawData curFieldValue_;

	DRDocumentReader* lastDocumentValue_ = nullptr;

	///this function has the logic of how a field of a document is represented
	void loadNextField();
	inline void loadNextFieldId();
	inline void loadNextFieldValue();

	RawData extractRawData(InputStream* inputStream);
};

}}
#endif //DOCUMENT_STORE_DR_DOCUMENT_READER_H
