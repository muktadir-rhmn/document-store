//
// Created by Muktadir Rahman on 13/9/20.
//

#ifndef DOCUMENT_STORE_ARRAY_READER_H
#define DOCUMENT_STORE_ARRAY_READER_H

#include "../utils/data/input_stream.h"

class ArrayReader {
public:
	///reader cursor movement logic
	virtual bool hasNext()=0;

	virtual void next()=0;

	///current cursor reading logic
	virtual int16 curFieldType()=0;

	virtual byte getCurByte()=0;

	virtual int16 getCurInt16()=0;

	virtual String getCurString()=0;

	virtual ArrayReader* getCurArray()=0;

};


#endif //DOCUMENT_STORE_ARRAY_READER_H
