//
// Created by Muktadir Rahman on 14/9/20.
//
#include "../../utils/debug/debug.h"
#include "byte_output_stream.h"

ByteOutputStream::ByteOutputStream() {
	initWithCapacity(ByteOutputStream::DEFAULT_CAPACITY);
}

ByteOutputStream::ByteOutputStream(size_t initialCapacity) {
	initWithCapacity(initialCapacity);
}

ByteOutputStream::~ByteOutputStream() {
	delete [] bytes_;
}

void ByteOutputStream::initWithCapacity(size_t cap) {
	cursor_ = 0;
	size_ = 0;
	cap_ = cap;
	bytes_ = new byte[cap_];
}

int ByteOutputStream::appendBytes(const void* value, size_t size) {
	ensureSpace(size);

	byte* t = (byte*) value;
	for (int i = 0; i < size; ++i) {
		bytes_[cursor_++] = *t;
		size_++;
		t++;
	}
	return size;
}

int ByteOutputStream::allocate(size_t nBytes) {
	ensureSpace(nBytes);

	int t = cursor_;
	cursor_ += nBytes;
	size_ += nBytes;
	return t;
}

void ByteOutputStream::ensureSpace(size_t size) {
	if (size + size_ > cap_) {
		size_t tmpCap = cap_ << 1;
		auto tmpBytes = new byte[tmpCap];

		DEBUG_MSG("PrefixLengthRawData: need more space. So, increasing capacity from " << cap_ << " to " << tmpCap);

		for (int i = 0; i < size_; ++i) {
			tmpBytes[i] = bytes_[i];
		}

		delete[] bytes_;

		bytes_ = tmpBytes;
		cap_ = tmpCap;
	}
}

RawData ByteOutputStream::getRawData() {
	return RawData{bytes_, size_};
}

void ByteOutputStream::setAllocatedData(int offset, int size, void* data) {
	byte* b = &bytes_[offset];
	byte* d = (byte*) data;
	for (int i = 0; i < size; ++i) {
		*b = d[i];
		b++;
	}
}
