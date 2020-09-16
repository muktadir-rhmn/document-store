//
// Created by Muktadir Rahman on 7/9/20.
//

#ifndef DOCUMENT_STORE_CONNECTION_DESCRIPTOR_H
#define DOCUMENT_STORE_CONNECTION_DESCRIPTOR_H


#include "../user/user.h"
#include "../utils/socket/buffered_input_stream.h"
#include "../utils/socket/buffered_output_stream.h"

class ConnectionDescriptor {
public:
    ConnectionDescriptor(User *user, String* databaseName, BufferedSocketInputStream *bufferedInputStream, BufferedSocketOutputStream *bufferedOutputStream);

    User *getUser() const {return user_; }
    BufferedSocketInputStream *getInputStream() const {return bufferedInputStream_;}
    BufferedSocketOutputStream *getOutputStream() const {return bufferedOutputStream_;}
    String& getDatabaseName() const {return *databaseName_;}

private:
    User* user_;
    String* databaseName_;
    BufferedSocketInputStream* bufferedInputStream_;
    BufferedSocketOutputStream* bufferedOutputStream_;
};


#endif //DOCUMENT_STORE_CONNECTION_DESCRIPTOR_H
