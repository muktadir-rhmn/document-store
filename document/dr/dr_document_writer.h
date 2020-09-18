//
// Created by Muktadir Rahman on 14/9/20.
//

#ifndef DOCUMENT_STORE_DR_DOCUMENT_WRITER_H
#define DOCUMENT_STORE_DR_DOCUMENT_WRITER_H

#include "../document_writer.h"
#include "../../utils/data/byte_output_stream.h"

namespace document { namespace dr {

class DRDocumentWriter : public DocumentWriter {
public:
	explicit DRDocumentWriter(ByteOutputStream* outputStream, FieldIdType fieldIdType=FieldIdType::kInteger);

	void appendInt32(void* fieldId, int32 value) override;

	void appendInt64(void* fieldId, int64 value) override;

	void appendCString(void* fieldId, ccstring value, stringSize_t strSize) override;

	void appendCString(void* fieldId, ccstring value) override {appendCString(fieldId, value, strlen(value));};

	void appendDocument(void* fieldId, RawData& rawData) override;


private:
	ByteOutputStream* outputStream_;
	FieldIdType fieldIdType_;
	docSize_t docSize_;

	int32 docSizeOffset_;

	inline void appendFieldId(void* fieldId);
};

}}
#endif //DOCUMENT_STORE_DR_DOCUMENT_WRITER_H
