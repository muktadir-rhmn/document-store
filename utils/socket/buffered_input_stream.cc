//
// Created by Muktadir Rahman on 6/9/20.
//

#include <iostream>
#include "buffered_input_stream.h"


BufferedSocketInputStream::BufferedSocketInputStream(ClientSocket* clientSocket) {
    clientSocket_ = clientSocket;
}

void BufferedSocketInputStream::nextBytes(void* buffer, size_t maxNumbOfBytesToRead) {
	read(buffer, maxNumbOfBytesToRead);
}

void BufferedSocketInputStream::skip(size_t bytes) {
	//todo: buffer adding.
	for (int bytesToSkip = bytes; bytesToSkip > 0;) {
		int n = 1024 < bytesToSkip ? 1024 : bytesToSkip;
		clientSocket_->readData(buffer_, n);
		bytesToSkip -= n;
	}
}

void BufferedSocketInputStream::read(void *buffer, int maxNumOfBytesToRead) {
	//todo: adsf
//    char* buff = (char*) buffer_;
// for now ignore the buffer_
	//todo: if maxNumOfBytesToRead > # bytes available in buffer_, we will 1) copy the data remaining in buffer_ 2) read directly into buffer, without touching buffer_. This will save copying twice.
	clientSocket_->readData(buffer, maxNumOfBytesToRead);
}

