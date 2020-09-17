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
	virtual int appendBytes(const void* bytes, size_t size)=0;
	virtual void flush() {}

	int appendByte(byte n){
		return appendBytes((byte*) &n, sizeof n);
	}

	int appendInt16(int16 n){
		return appendBytes((byte*) &n, sizeof n);
	}

	int appendInt32(int32 n){
		return appendBytes((const void*) &n, sizeof n);
	}

	int appendInt64(int64 n){
		return appendBytes((byte*) &n, sizeof n);
	}

	int appendFloat32(float32 n){
		return appendBytes((byte*) &n, sizeof n);
	}

	int appendFloat64(float64 n){
		return appendBytes((byte*) &n, sizeof n);
	}

	int appendCString(ccstring s, int size= -1){
		size = strlen(s);
		size += 1;//1 for the null character

		return appendBytes((byte*) s, size);
	}
};


#endif //DOCUMENT_STORE_OUTPUT_STREAM_H
