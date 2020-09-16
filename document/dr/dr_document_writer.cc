//
// Created by Muktadir Rahman on 14/9/20.
//

#include "dr_document_writer.h"
#include "../bson_constants.h"
#include "../../utils/data/byte_output_stream.h"

namespace document { namespace dr {

DRDocumentWriter::DRDocumentWriter(byte fieldIdType) {
	outputStream_ = new ByteOutputStream();
	fieldIdType_ = fieldIdType;

	docSizeOffset_ = outputStream_->allocate(sizeof(docSize_t));
}

DRDocumentWriter::~DRDocumentWriter() {
	delete outputStream_;
}

//DRDocumentWriter::DRDocumentWriter(AllocatableOutputStream* outputStream, byte fieldIdType) {
//	outputStream_ = outputStream;
//	fieldIdType_ = fieldIdType;
//}

void DRDocumentWriter::appendInt32(void* fieldId, int32 value) {
	appendFieldId(fieldId);

	outputStream_->appendBytes(&FieldType.INT32, sizeof(fieldType_t));
	outputStream_->appendInt32(value);
}

void DRDocumentWriter::appendInt64(void* fieldId, int64 value) {
	appendFieldId(fieldId);

	outputStream_->appendBytes(&FieldType.INT64, sizeof(fieldType_t));
	outputStream_->appendInt64(value);
}

void DRDocumentWriter::appendCString(void* fieldId, ccstring value, stringSize_t strSize) {
	appendFieldId(fieldId);

	if (strSize <= 0) strSize = strlen(value);
	outputStream_->appendBytes(&FieldType.STRING, sizeof(fieldType_t));
	outputStream_->appendBytes(&strSize, sizeof(stringSize_t));
	outputStream_->appendBytes(value, strSize); ///no null character
}

void DRDocumentWriter::appendDocument(void* fieldId, DocumentReader* embeddedDoc) {
	appendFieldId(fieldId);

	///todo: get just bytes of the document and append them
}

AllocatableOutputStream* DRDocumentWriter::getOutputStream() {
	docSize_t nBytes = outputStream_->getRawData().size;
	outputStream_->setAllocatedData(docSizeOffset_, sizeof(docSize_t), &nBytes);
	return outputStream_;
}

void DRDocumentWriter::appendFieldId(void* fieldId) {
	if (fieldIdType_ == FieldType.STRING) {
		outputStream_->appendCString((ccstring) fieldId);
	} else {
		fieldId_t id = *(fieldId_t *) fieldId;
		outputStream_->appendBytes(&id, sizeof(fieldId_t));
	}
}

}}