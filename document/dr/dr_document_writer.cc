//
// Created by Muktadir Rahman on 14/9/20.
//

#include "dr_document_writer.h"
#include "../bson_constants.h"

namespace document { namespace dr {

DRDocumentWriter::DRDocumentWriter(ByteOutputStream* outputStream, FieldIdType fieldIdType) {
	outputStream_ = outputStream;
	fieldIdType_ = fieldIdType;

	docSizeOffset_ = outputStream_->allocate(sizeof(docSize_t));
	docSize_ = sizeof(docSize_t);
}

void DRDocumentWriter::appendInt32(void* fieldId, int32 value) {
	appendFieldId(fieldId);

	docSize_ += outputStream_->appendBytes(&FieldType.INT32, sizeof(fieldType_t));

	docSize_ += outputStream_->appendInt32(value);
	outputStream_->setAllocatedData(docSizeOffset_, sizeof(docSize_t), &docSize_);
}

void DRDocumentWriter::appendInt64(void* fieldId, int64 value) {
	appendFieldId(fieldId);

	docSize_ += outputStream_->appendBytes(&FieldType.INT64, sizeof(fieldType_t));

	docSize_ += outputStream_->appendInt64(value);
	outputStream_->setAllocatedData(docSizeOffset_, sizeof(docSize_t), &docSize_);
}

void DRDocumentWriter::appendCString(void* fieldId, ccstring value, stringSize_t strSize) {
	appendFieldId(fieldId);

	docSize_ += outputStream_->appendBytes(&FieldType.STRING, sizeof(fieldType_t));

	if (strSize <= 0) strSize = strlen(value);
	docSize_ += outputStream_->appendBytes(&strSize, sizeof(stringSize_t));
	docSize_ += outputStream_->appendBytes(value, strSize); ///no null character
	outputStream_->setAllocatedData(docSizeOffset_, sizeof(docSize_t), &docSize_);
}

void DRDocumentWriter::appendDocument(void* fieldId, RawData& rawData) {
	appendFieldId(fieldId);

	docSize_ += outputStream_->appendBytes(&FieldType.DOCUMENT, sizeof(fieldType_t));

	docSize_ += outputStream_->appendBytes(rawData.bytes, rawData.size);

	outputStream_->setAllocatedData(docSizeOffset_, sizeof(docSize_t), &docSize_);
}

void DRDocumentWriter::appendFieldId(void* fieldId) {
	if (fieldIdType_ == FieldIdType::kString) {
		size_t size = strlen((ccstring)fieldId);
		docSize_ += outputStream_->appendCString((ccstring) fieldId, size);
	} else {
		fieldId_t id = *(fieldId_t *) fieldId;
		docSize_ += outputStream_->appendBytes(&id, sizeof(fieldId_t));
	}
	outputStream_->setAllocatedData(docSizeOffset_, sizeof(docSize_t), &docSize_);
}
}}