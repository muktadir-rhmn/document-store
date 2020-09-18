//
// Created by Muktadir Rahman on 14/9/20.
//

#include "dr_document_writer.h"
#include "../bson_constants.h"

namespace document { namespace dr {

DRDocumentWriter::DRDocumentWriter(FieldIdType fieldIdType) {
	fieldIdType_ = fieldIdType;

	docSizeOffset_ = outputStream_.allocate(sizeof(docSize_t));
}

DRDocumentWriter::DRDocumentWriter(ByteOutputStream outputStream, FieldIdType fieldIdType) : outputStream_(outputStream) {
	fieldIdType_ = fieldIdType;

	docSizeOffset_ = outputStream_.allocate(sizeof(docSize_t));
}

void DRDocumentWriter::appendInt32(void* fieldId, int32 value) {
	appendFieldId(fieldId);

	outputStream_.appendBytes(&FieldType.INT32, sizeof(fieldType_t));

	outputStream_.appendInt32(value);
}

void DRDocumentWriter::appendInt64(void* fieldId, int64 value) {
	appendFieldId(fieldId);

	outputStream_.appendBytes(&FieldType.INT64, sizeof(fieldType_t));

	outputStream_.appendInt64(value);
}

void DRDocumentWriter::appendCString(void* fieldId, ccstring value, stringSize_t strSize) {
	appendFieldId(fieldId);

	outputStream_.appendBytes(&FieldType.STRING, sizeof(fieldType_t));

	if (strSize <= 0) strSize = strlen(value);
	outputStream_.appendBytes(&strSize, sizeof(stringSize_t));
	outputStream_.appendBytes(value, strSize); ///no null character
}

void DRDocumentWriter::appendDocument(void* fieldId, DocumentWriter& embeddedDoc) {
	appendFieldId(fieldId);

	outputStream_.appendBytes(&FieldType.DOCUMENT, sizeof(fieldType_t));

	AllocatableOutputStream* outputStream = embeddedDoc.getOutputStream();
	RawData rawData = outputStream->getRawData();
	outputStream_.appendBytes(rawData.bytes, rawData.size);
}

void DRDocumentWriter::appendFieldId(void* fieldId) {
	if (fieldIdType_ == FieldIdType::kString) {
		outputStream_.appendCString((ccstring) fieldId);
	} else {
		fieldId_t id = *(fieldId_t *) fieldId;
		outputStream_.appendBytes(&id, sizeof(fieldId_t));
	}
}

AllocatableOutputStream* DRDocumentWriter::getOutputStream() {
	docSize_t nBytes = outputStream_.getRawData().size;
	outputStream_.setAllocatedData(docSizeOffset_, sizeof(docSize_t), &nBytes);
	return &outputStream_;
}

}}