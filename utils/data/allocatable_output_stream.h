//
// Created by Muktadir Rahman on 13/9/20.
//

#ifndef DOCUMENT_STORE_ALLOCATABLE_OUTPUT_STREAM_H
#define DOCUMENT_STORE_ALLOCATABLE_OUTPUT_STREAM_H


#include "output_stream.h"
#include "raw_data.h"

class AllocatableOutputStream : public OutputStream {
public:
	virtual ~AllocatableOutputStream()= default;
	virtual int allocate(size_t nBytes)=0;
	virtual void setAllocatedData(int offset, int size, void* data)=0;
	virtual RawData getRawData()=0;
};

#endif //DOCUMENT_STORE_ALLOCATABLE_OUTPUT_STREAM_H
