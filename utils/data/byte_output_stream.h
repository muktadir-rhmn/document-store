//
// Created by Muktadir Rahman on 14/9/20.
//

#ifndef DOCUMENT_STORE_BYTE_OUTPUT_STREAM_H
#define DOCUMENT_STORE_BYTE_OUTPUT_STREAM_H

#include "../../typedefs.h"
#include "output_stream.h"
#include "input_stream.h"
#include "allocatable_output_stream.h"

class ByteOutputStream : public AllocatableOutputStream{
public:
	explicit ByteOutputStream();
	explicit ByteOutputStream(size_t initialCapacity);
	~ByteOutputStream() override;

	byte* bytes() {return bytes_;}
	size_t size() const {return size_;}

	void appendBytes(const void* value, size_t size) override;

	int allocate(size_t nBytes) override;

	void setAllocatedData(int offset, int size, void* data) override;

	RawData getRawData() override;

private:
	static const int DEFAULT_CAPACITY = 2;

	byte* bytes_;
	size_t cursor_;
	size_t cap_;
	size_t size_;

	inline void initWithCapacity(size_t cap);
	void ensureSpace(size_t size);
};

#endif //DOCUMENT_STORE_BYTE_OUTPUT_STREAM_H
