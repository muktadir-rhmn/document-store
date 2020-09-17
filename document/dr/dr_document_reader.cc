
#include "dr_document_reader.h"


namespace document { namespace dr {

DRDocumentReader::DRDocumentReader(InputStream* inputStream, int fieldIdType)
: inputStream_(extractRawData(inputStream), true) {
	curFieldIdType_ = fieldIdType;
}

DRDocumentReader::DRDocumentReader(ByteInputStream inputStream, int fieldIdType) : inputStream_(inputStream) {
	curFieldIdType_ = fieldIdType;
}

RawData DRDocumentReader::extractRawData(InputStream* inputStream) {
	inputStream->nextBytes(&documentSize_, sizeof(docSize_t));
	nBytesRead_ = sizeof(docSize_t);

	RawData rawData;
	rawData.size = documentSize_;
	rawData.bytes = new byte[documentSize_];

	*(docSize_t*) rawData.bytes = documentSize_;

	inputStream->nextBytes(rawData.bytes + sizeof(docSize_t), documentSize_ - sizeof(docSize_t));

	return rawData;
}

DRDocumentReader::~DRDocumentReader() {
	delete lastDocumentValue_;
}

bool DRDocumentReader::next() {
	if (nBytesRead_ >= documentSize_) {
		if (nBytesRead_ > documentSize_) throw InternalException("nBytesRead_ > documentSize_ :: There is some bug in DRDocumentReader");
		return false;
	}

	loadNextField();
	return true;
}

ccstring DRDocumentReader::curFieldIdAsCString() {
	return curFieldName_.c_str();
}

fieldId_t DRDocumentReader::curFieldIdAsInt() {
	return curFieldId_;
}

fieldType_t DRDocumentReader::curFieldType() {
	return curFieldType_;
}

int64 DRDocumentReader::curValueAsInt64() {
	return *(int64*) curFieldValue_.bytes;
}

String DRDocumentReader::curValueAsString() {
	String val;
	stringSize_t size = *(stringSize_t*) curFieldValue_.bytes;
	for (int i = 0; i < size; ++i) {
		val += ((char *) curFieldValue_.bytes) [i + sizeof(stringSize_t)];
	}
	return val;
}

DocumentReader* DRDocumentReader::curValueAsDocument() {
	delete lastDocumentValue_;

	lastDocumentValue_ = new DRDocumentReader(ByteInputStream(curFieldValue_));
	return lastDocumentValue_;
}

void DRDocumentReader::loadNextField() {
	loadNextFieldId();
	loadNextFieldValue();
}

void DRDocumentReader::loadNextFieldId() {
	if (curFieldIdType_ != -1) {
		curFieldName_ = inputStream_.nextCString();

		nBytesRead_ += curFieldName_.size() + 1;
	} else {
		curFieldId_ = inputStream_.nextInt16();
		nBytesRead_ += sizeof(int16);
	}
}

void DRDocumentReader::loadNextFieldValue() {
	inputStream_.nextBytes(&curFieldType_, sizeof(fieldType_t));
	nBytesRead_ += sizeof(fieldType_t);

	if (curFieldType_ == FieldType.INT64) {
		curFieldValue_.size = sizeof(int64);
		curFieldValue_.bytes = inputStream_.nextBytes(curFieldValue_.size);
		nBytesRead_ += curFieldValue_.size;
	} else if (curFieldType_ == FieldType.STRING) {
		stringSize_t size;
		inputStream_.peekBytes(&size, sizeof(stringSize_t));
		curFieldValue_.size = size;

		curFieldValue_.bytes = inputStream_.nextBytes(size + sizeof(stringSize_t));
		nBytesRead_ += curFieldValue_.size + sizeof(stringSize_t);
	} else if (curFieldType_ == FieldType.DOCUMENT) {
		docSize_t size;
		inputStream_.peekBytes(&size, sizeof(docSize_t));
		curFieldValue_.size = size;

		curFieldValue_.bytes = inputStream_.nextBytes(curFieldValue_.size);
		nBytesRead_ += curFieldValue_.size;
	} else if (curFieldType_ == FieldType.ARRAY) {
		arraySize_t size;
		inputStream_.peekBytes(&size, sizeof(arraySize_t));
		curFieldValue_.size = size;

		curFieldValue_.bytes = inputStream_.nextBytes(curFieldValue_.size);
		nBytesRead_ += curFieldValue_.size;
	}
}

}}
