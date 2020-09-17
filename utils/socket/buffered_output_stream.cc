//
// Created by Muktadir Rahman on 6/9/20.
//

#include "buffered_output_stream.h"

BufferedSocketOutputStream::BufferedSocketOutputStream(ClientSocket* clientSocket) {
    clientSocket_ = clientSocket;
}

int BufferedSocketOutputStream::appendBytes(const void* value, size_t size) {
	//todo: buffer_ the write
	return clientSocket_->writeData(value, size);
}

void BufferedSocketOutputStream::flush() {
	OutputStream::flush();
}
