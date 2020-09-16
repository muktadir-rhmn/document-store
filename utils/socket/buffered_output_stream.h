//
// Created by Muktadir Rahman on 6/9/20.
//

#ifndef DOCUMENT_STORE_BUFFERED_OUTPUT_STREAM_H
#define DOCUMENT_STORE_BUFFERED_OUTPUT_STREAM_H


#include "client_socket.h"
#include "../data/output_stream.h"

class BufferedSocketOutputStream : public OutputStream {
public:
    explicit BufferedSocketOutputStream(ClientSocket* clientSocket);

	void appendBytes(const void* value, size_t size) override;
	void flush() override;

private:
    ClientSocket* clientSocket_;

    char buffer[1024]{};
    int curPos;
    int lastPos;
};


#endif //DOCUMENT_STORE_BUFFERED_OUTPUT_STREAM_H
