//
// Created by Muktadir Rahman on 6/9/20.
//

#ifndef DOCUMENT_STORE_PROCESSOR_H
#define DOCUMENT_STORE_PROCESSOR_H


#include "../connection/connection_descriptor.h"

class Processor {
public:
    explicit Processor(ConnectionDescriptor* connectionDescriptor);
    void process();

private:
    ConnectionDescriptor* conDescriptor_;
};


#endif //DOCUMENT_STORE_PROCESSOR_H
