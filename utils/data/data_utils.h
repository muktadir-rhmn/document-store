//
// Created by Muktadir Rahman on 14/9/20.
//

#ifndef DOCUMENT_STORE_DATA_UTILS_H
#define DOCUMENT_STORE_DATA_UTILS_H


#include "../../typedefs.h"

class DataUtils {
public:
	static void copy(void* source, void* dest, size_t nBytes);
	static void print(void* data, size_t nBytes);

};


#endif //DOCUMENT_STORE_DATA_UTILS_H
