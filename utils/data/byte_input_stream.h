//
// Created by Muktadir Rahman on 9/9/20.
//

#ifndef DOCUMENT_STORE_BYTE_INPUT_STREAM_H
#define DOCUMENT_STORE_BYTE_INPUT_STREAM_H

#include "../../typedefs.h"
#include "output_stream.h"
#include "input_stream.h"
#include "allocatable_output_stream.h"

class ByteInputStream :public InputStream {
public:
    explicit ByteInputStream(void* bytes, size_t size);

	void nextBytes(void* buffer, size_t nBytesToRead) override;

	bool hasMoreBytes() override;

	void skip(size_t bytes) override;

private:
	byte* bytes_;
    size_t cursor_;
    size_t size_;
};


#endif //DOCUMENT_STORE_BYTE_INPUT_STREAM_H