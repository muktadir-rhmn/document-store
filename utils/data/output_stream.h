//
// Created by Muktadir Rahman on 12/9/20.
//

#ifndef DOCUMENT_STORE_OUTPUT_STREAM_H
#define DOCUMENT_STORE_OUTPUT_STREAM_H


#include <iostream>
#include "../../typedefs.h"
#include "../exceptions/internal_exception.h"

class OutputStream {
public:
	virtual void appendBytes(const void* bytes, size_t size)=0;
	virtual void flush() {}

	void appendByte(byte n){
		appendBytes((byte*) &n, sizeof n);
	}

	void appendInt16(int16 n){
		appendBytes((byte*) &n, sizeof n);
	}

	void appendInt32(int32 n){
		appendBytes((const void*) &n, sizeof n);
	}

	void appendInt64(int64 n){
		appendBytes((byte*) &n, sizeof n);
	}

	void appendFloat32(float32 n){
		appendBytes((byte*) &n, sizeof n);
	}

	void appendFloat64(float64 n){
		appendBytes((byte*) &n, sizeof n);
	}

	void appendCString(ccstring s, int size= -1){
		size = strlen(s);
		size += 1;//1 for the null character

		appendBytes((byte*) s, size);
	}
};


#endif //DOCUMENT_STORE_OUTPUT_STREAM_H
