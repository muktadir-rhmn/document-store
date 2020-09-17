//
// Created by Muktadir Rahman on 6/9/20.
//

#ifndef DOCUMENT_STORE_DEBUG_H
#define DOCUMENT_STORE_DEBUG_H

#include <iostream>

#define DEBUG_MSG(message) std::cout << message << std::endl

#define ASSERT(EXPR, MSG) if (!(EXPR)) {std::cout << MSG << std::endl; assert(EXPR);}

#endif //DOCUMENT_STORE_DEBUG_H
