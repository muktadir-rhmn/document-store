//
// Created by Muktadir Rahman on 9/9/20.
//

#include "byte_input_stream.h"

ByteInputStream::ByteInputStream(void* bytes, size_t size) {
	bytes_ = (byte*) bytes;
	size_ = size;
	cursor_ = 0;
}

bool ByteInputStream::hasMoreBytes() {
	return cursor_ < size_;
}

void ByteInputStream::nextBytes(void* buffer, size_t nBytesToRead) {
	if (cursor_ >= size_) throw InternalException("No more data to read");

	char* buff = (char*) buffer;

	size_t bytesRemaining = size_ - cursor_;
	if (nBytesToRead > bytesRemaining) {
		throw Exception("Not enough data available");
	}

	for (int i = 0; i < nBytesToRead; ++i) {
		buff[i] = bytes_[cursor_++];
	}
}

void ByteInputStream::skip(size_t bytes) {
	cursor_ += bytes;
}

