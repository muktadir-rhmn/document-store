//
// Created by Muktadir Rahman on 13/9/20.
//

#ifndef DOCUMENT_STORE_INTERNAL_EXCEPTION_H
#define DOCUMENT_STORE_INTERNAL_EXCEPTION_H


#include "exception.h"
#include "../../typedefs.h"

/**
 * The exception that will not let client know details about
 */
class InternalException : public Exception{
public:
	InternalException(ccstring msg) : Exception(msg) {

	}
};


#endif //DOCUMENT_STORE_INTERNAL_EXCEPTION_H
