//
// Created by Muktadir Rahman on 8/9/20.
//

#ifndef DOCUMENT_STORE_BSON_CONSTANTS_H
#define DOCUMENT_STORE_BSON_CONSTANTS_H

namespace document{
struct {
	const fieldType_t NO_FIELD = 0x00;
	const fieldType_t NIL = 0x0A;
	const fieldType_t INT32 = 0x10;
	const fieldType_t INT64 = 0x12;
	const fieldType_t FLOAT64 = 0x01;
	const fieldType_t STRING = 0x02;
	const fieldType_t DOCUMENT = 0x03;
	const fieldType_t ARRAY = 0x04;
} FieldType;

}

#endif //DOCUMENT_STORE_BSON_CONSTANTS_H
