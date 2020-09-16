//
// Created by Muktadir Rahman on 8/9/20.
//

#ifndef DOCUMENT_STORE_TYPEDEFS_H
#define DOCUMENT_STORE_TYPEDEFS_H

#include <cstdint>
#include <cstdio>
#include <string>
#include <map>

typedef int8_t byte;
typedef int16_t int16;
typedef int32_t int32;
typedef int64_t int64;

typedef float float32;
typedef double float64;

typedef size_t size_t;

typedef const char * ccstring; //Constant C-String
typedef std::string String;

template <
		typename Key,
		typename Value
>
using Map = std::map<Key, Value>;


#endif //DOCUMENT_STORE_DOCUMENT_TYPEDEFS_H
