//
// Created by Muktadir Rahman on 14/9/20.
//

#ifndef DOCUMENT_STORE_DR_DOCUMENT_WRITER_H
#define DOCUMENT_STORE_DR_DOCUMENT_WRITER_H

#include "../document_writer.h"
#include "../../utils/data/byte_output_stream.h"

namespace document { namespace dr {

class DRDocumentWriter : public document::DocumentWriter {
public:
	explicit DRDocumentWriter(ByteOutputStream outputStream, FieldIdType fieldIdType=FieldIdType::kInteger);
	explicit DRDocumentWriter(FieldIdType fieldIdType=FieldIdType::kInteger);

	void appendInt32(void* fieldId, int32 value) override;

	void appendInt64(void* fieldId, int64 value) override;

	void appendCString(void* fieldId, ccstring value, stringSize_t strSize=-1) override;

	void appendDocument(void* fieldId, DocumentWriter& value) override;

	AllocatableOutputStream* getOutputStream() override;

private:
	ByteOutputStream outputStream_;
	FieldIdType fieldIdType_;

	int32 docSizeOffset_;

	inline void appendFieldId(void* fieldId);
};

}}
#endif //DOCUMENT_STORE_DR_DOCUMENT_WRITER_H
