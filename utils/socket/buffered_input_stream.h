//
// Created by Muktadir Rahman on 6/9/20.
//

#ifndef DOCUMENT_STORE_BUFFERED_INPUT_STREAM_H
#define DOCUMENT_STORE_BUFFERED_INPUT_STREAM_H

#include <string>
#include "client_socket.h"
#include "../../typedefs.h"
#include "../data/input_stream.h"

/**
 * Abstracts network communication to the upper layers.
 */
class BufferedSocketInputStream : public InputStream {
public:
    explicit BufferedSocketInputStream(ClientSocket* clientSocket);

	void nextBytes(void* buffer, size_t maxNumbOfBytesToRead) override;

	void skip(size_t bytes) override;

private:
    ClientSocket* clientSocket_;

    char buffer_[1024];
    int curPos_;
    int lastPos_;

    void read(void* buffer, int maxNumOfBytesToRead);
};


#endif //DOCUMENT_STORE_BUFFERED_INPUT_STREAM_H
