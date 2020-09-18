//
// Created by Muktadir Rahman on 9/9/20.
//

#include "byte_input_stream.h"
#include "data_utils.h"

ByteInputStream::ByteInputStream(void* bytes, size_t size, bool destroyBytes) {
	bytes_ = (byte*) bytes;
	size_ = size;
	cursor_ = 0;
	destroyBytes_ = destroyBytes;

	DataUtils::print(bytes, size);
}

ByteInputStream::ByteInputStream(RawData rawData, bool destroyBytes) {
	bytes_ = rawData.bytes;
	size_ = rawData.size;
	cursor_ = 0;
	destroyBytes_ = destroyBytes;
	DataUtils::print(bytes_, size_);
}

ByteInputStream::~ByteInputStream() {
	if (destroyBytes_) delete [] bytes_;
}

bool ByteInputStream::hasMoreBytes() {
	return cursor_ < size_;
}

void ByteInputStream::nextBytes(void* buffer, size_t nBytesToRead) {
	peekBytes(buffer, nBytesToRead);
	cursor_ += nBytesToRead;
}

void ByteInputStream::peekBytes(void* buffer, size_t nBytesToRead) {
	if (cursor_ >= size_) throw InternalException("No more data to read");

	char* buff = (char*) buffer;

	size_t bytesRemaining = size_ - cursor_;
	if (nBytesToRead > bytesRemaining) {
		throw Exception("Not enough data available");
	}

	int t = cursor_;
	for (int i = 0; i < nBytesToRead; ++i) {
		buff[i] = bytes_[t++];
	}
}

void ByteInputStream::skip(size_t bytes) {
	cursor_ += bytes;
}

byte* ByteInputStream::nextBytes(size_t nBytesToRead) {
	byte* t = &bytes_[cursor_];
	cursor_ += nBytesToRead;
	return t;
}

void ByteInputStream::resetCursor() {
	cursor_ = 0;
}

