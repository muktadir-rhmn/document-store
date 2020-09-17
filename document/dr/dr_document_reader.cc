
#include "dr_document_reader.h"


namespace document { namespace dr {

DRDocumentReader::DRDocumentReader(InputStream* inputStream, int fieldIdType) {
	inputStream_ = inputStream;
	curFieldIdType_ = fieldIdType;

	inputStream_->nextBytes(&documentSize_, sizeof(docSize_t));
	nBytesRead_ = sizeof(docSize_t);
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
	return *(int64*) curFieldValue_;
}

String DRDocumentReader::curValueAsString() {
	String val;
	stringSize_t size = *(stringSize_t*) curFieldValue_;
	for (int i = 0; i < size; ++i) {
		val += ((char *) curFieldValue_) [i + sizeof(stringSize_t)];
	}
	return val;
}

DocumentReader* DRDocumentReader::curValueAsDocument() {
	delete lastByteInputStream_;
	delete lastDocumentValue_;

	lastByteInputStream_ = new ByteInputStream((byte*) curFieldValue_, curFieldValueSize_);
	lastDocumentValue_ = new DRDocumentReader(lastByteInputStream_);
	return lastDocumentValue_;
}

void DRDocumentReader::loadNextField() {
	loadNextFieldId();
	loadNextFieldValue();
}

void DRDocumentReader::loadNextFieldId() {
	if (curFieldIdType_ != -1) {
		curFieldName_ = inputStream_->nextCString();

		nBytesRead_ += curFieldName_.size() + 1;
	} else {
		curFieldId_ = inputStream_->nextInt16();
		nBytesRead_ += sizeof(int16);
	}
}

void DRDocumentReader::loadNextFieldValue() {
	delete[] (char*) curFieldValue_;

	curFieldType_ = inputStream_->nextByte();
	nBytesRead_ += 1;

	if (curFieldType_ == FieldType.INT64) {
		curFieldValueSize_ = sizeof(int64);

		curFieldValue_ = new byte[curFieldValueSize_];
		inputStream_->nextBytes(curFieldValue_, curFieldValueSize_);
		nBytesRead_ += curFieldValueSize_;
	} else if (curFieldType_ == FieldType.STRING) {
		stringSize_t size;
		inputStream_->nextBytes(&size, sizeof(stringSize_t));
		nBytesRead_ += sizeof(stringSize_t);
		curFieldValueSize_ = size;

		curFieldValue_ = new byte[curFieldValueSize_];
		*(stringSize_t *) curFieldValue_ = curFieldValueSize_;
		inputStream_->nextBytes(curFieldValue_ + sizeof(stringSize_t), curFieldValueSize_);
		nBytesRead_ += curFieldValueSize_;
	} else if (curFieldType_ == FieldType.DOCUMENT) {
		docSize_t size;
		inputStream_->nextBytes(&size, sizeof(docSize_t));
		curFieldValueSize_ = size;

		curFieldValue_ = new byte[curFieldValueSize_];
		*(docSize_t *) curFieldValue_ = curFieldValueSize_;
		inputStream_->nextBytes(curFieldValue_ + sizeof(docSize_t), curFieldValueSize_);
		nBytesRead_ += curFieldValueSize_;
	} else if (curFieldType_ == FieldType.ARRAY) {
		arraySize_t size;
		inputStream_->nextBytes(&size, sizeof(arraySize_t));
		curFieldValueSize_ = size;

		curFieldValue_ = new byte [curFieldValueSize_];
		*(arraySize_t *) curFieldValue_ = curFieldValueSize_;
		inputStream_->nextBytes(curFieldValue_ + sizeof(arraySize_t), curFieldValueSize_);
		nBytesRead_ += curFieldValueSize_;
	}
}

DRDocumentReader::~DRDocumentReader() {
	delete lastByteInputStream_;
	delete lastDocumentValue_;
	delete[] (char*) curFieldValue_;
}

}}
