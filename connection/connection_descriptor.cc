//
// Created by Muktadir Rahman on 7/9/20.
//

#include "connection_descriptor.h"

ConnectionDescriptor::ConnectionDescriptor(User *user, std::string* databaseName,
										   BufferedSocketInputStream *bufferedInputStream,
										   BufferedSocketOutputStream *bufferedOutputStream) {
    user_ = user;
    databaseName_ = databaseName;
    bufferedInputStream_ = bufferedInputStream;
    bufferedOutputStream_ =  bufferedOutputStream;
}
