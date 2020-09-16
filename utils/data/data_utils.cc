//
// Created by Muktadir Rahman on 14/9/20.
//

#include <iostream>
#include "data_utils.h"

void DataUtils::copy(void* source, void* dest, size_t nBytes) {
	char* s = (char*) source;
	char* d = (char*) dest;
	while (nBytes--){
		*d = *s;
		d++;
		s++;
	}
}

void DataUtils::print(void* data, size_t nBytes) {
	byte* d = (byte*) data;
	for (int i = 0; i < nBytes; ++i) {
		std::cout << (int) d[i] <<std::endl;
	}
}
