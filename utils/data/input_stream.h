//
// Created by Muktadir Rahman on 12/9/20.
//

#ifndef DOCUMENT_STORE_INPUT_STREAM_H
#define DOCUMENT_STORE_INPUT_STREAM_H


#include "../../typedefs.h"
#include "../exceptions/internal_exception.h"

class InputStream {
public:
	virtual void nextBytes(void* buffer, size_t maxNumbOfBytesToRead)=0;
	virtual void skip(size_t bytes)=0;
	virtual bool hasMoreBytes() {
		throw InternalException("hasMoreBytes() not implemented on this stream");
	}
	virtual void resetCursor() {
		throw InternalException("resetCursor() not implemented on this stream");
	}

	byte nextByte(){
		byte n;
		nextBytes((byte *)&n, sizeof n);
		return n;
	};

	int16 nextInt16(){
		int16 n;
		nextBytes((byte *)&n, sizeof n);
		return n;
	};

	int32 nextInt32(){
		int32 n;
		nextBytes((byte *)&n, sizeof n);
		return n;
	};

	int64 nextInt64(){
		int64 n;
		nextBytes((byte *)&n, sizeof n);
		return n;
	};

	int64 nextFloat32(){
		float32 n;
		nextBytes((byte *)&n, sizeof n);
		return n;
	};

	int64 nextFloat64(){
		int64 n;
		nextBytes((byte *)&n, sizeof n);
		return n;
	};

	char nextChar(){
		char n;
		nextBytes((byte *)&n, sizeof n);
		return n;
	};

	String nextCString(){ ///next null terminated string, ie. C string
		String s;
		char ch;
		while ( (ch = nextChar()) ) {
			s += (ch);
		}
		return s;
	};

};


#endif //DOCUMENT_STORE_INPUT_STREAM_H
