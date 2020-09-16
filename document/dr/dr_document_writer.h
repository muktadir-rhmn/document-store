//
// Created by Muktadir Rahman on 14/9/20.
//

#ifndef DOCUMENT_STORE_DR_DOCUMENT_WRITER_H
#define DOCUMENT_STORE_DR_DOCUMENT_WRITER_H

#include "../document_writer.h"

namespace document { namespace dr {

class DRDocumentWriter : public document::DocumentWriter {
public:
//	explicit DRDocumentWriter(AllocatableOutputStream* outputStream, byte fieldIdType=-1);
	explicit DRDocumentWriter(byte fieldIdType=-1);
	~DRDocumentWriter();

	void appendInt32(void* fieldId, int32 value) override;

	void appendInt64(void* fieldId, int64 value) override;

	void appendCString(void* fieldId, ccstring value, stringSize_t strSize=-1) override;

	void appendDocument(void* fieldId, DocumentReader* value) override;

	AllocatableOutputStream* getOutputStream() override;

private:
	AllocatableOutputStream* outputStream_;
	byte fieldIdType_;

	int32 docSizeOffset_;

	inline void appendFieldId(void* fieldId);
};

}}
#endif //DOCUMENT_STORE_DR_DOCUMENT_WRITER_H
