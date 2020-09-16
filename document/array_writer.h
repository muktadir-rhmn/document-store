//
// Created by Muktadir Rahman on 13/9/20.
//

#ifndef DOCUMENT_STORE_ARRAY_WRITER_H
#define DOCUMENT_STORE_ARRAY_WRITER_H

#include "../utils/data/allocatable_output_stream.h"

class ArrayWriter {
public:
	virtual void append(int16 element)=0;
	virtual void append(String element)=0;
};


#endif //DOCUMENT_STORE_ARRAY_WRITER_H
