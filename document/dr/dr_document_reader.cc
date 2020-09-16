
#include "dr_document_reader.h"


namespace document { namespace dr {

DRDocumentReader::DRDocumentReader(InputStream* inputStream, int fieldIdType) {
	inputStream_ = inputStream;
	curFieldIdType_ = fieldIdType;
	readingFinished_ = false;

	documentSize_ = inputStream_->nextInt32();
	nBytesRead_ = sizeof(int32);

	loadNextField();
}

bool DRDocumentReader::hasNext() {
	return !readingFinished_;
}

void DRDocumentReader::next() {
	if (!hasNext()) throw InternalException("Call to DocumentReader::next() after reaching the end of the document");
	if (nBytesRead_ == documentSize_) {
		readingFinished_ = true;
		return;
	}

	loadNextField();
}

ccstring DRDocumentReader::fieldIdAsCString() {
	return curFieldName_.c_str();
}

fieldId_t DRDocumentReader::fieldIdAsInt() {
	return curFieldId_;
}

fieldType_t DRDocumentReader::fieldType() {
	return curFieldType_;
}

int32 DRDocumentReader::valueAsInt32() {
	return *(int32*) curFieldValue_;
}

int64 DRDocumentReader::valueAsInt64() {
	return *(int64*) curFieldValue_;
}

String DRDocumentReader::valueAsString() {
	String val;
	for (int i = 0; i < curFieldValueSize_; ++i) {
		val += ((char *) curFieldValue_) [i];
	}
	return val;
}

DocumentReader* DRDocumentReader::valueAsDocument() {
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
	}
}

void DRDocumentReader::loadNextFieldValue() {
	curFieldType_ = inputStream_->nextByte();
	nBytesRead_ += 1;

	if (curFieldType_ == FieldType.INT64) {
		curFieldValueSize_ = sizeof(int64);
	} else if (curFieldType_ == FieldType.STRING) {
		curFieldValueSize_ = inputStream_->nextInt32();
		nBytesRead_ += sizeof(int32);
	} else if (curFieldType_ == FieldType.DOCUMENT) {
		curFieldValueSize_ = inputStream_->nextInt32();
		nBytesRead_ += sizeof(int32);
	} else if (curFieldType_ == FieldType.ARRAY) {
		curFieldValueSize_ = inputStream_->nextInt32();
		nBytesRead_ += sizeof(int32);
	}

	delete[] (char*) curFieldValue_;
	curFieldValue_ = new char[curFieldValueSize_];
	inputStream_->nextBytes(curFieldValue_, curFieldValueSize_);
	nBytesRead_ += curFieldValueSize_;
}

DRDocumentReader::~DRDocumentReader() {
	delete lastByteInputStream_;
	delete lastDocumentValue_;
	delete[] (char*) curFieldValue_;
}

}}

