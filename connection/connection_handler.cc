//
// Created by Muktadir Rahman on 6/9/20.
//

#include <iostream>
#include "../utils/socket/client_socket.h"
#include "connection_manager.h"
#include "../utils/logger/logger.h"
#include "../utils/exceptions/exception.h"
#include "../utils/socket/buffered_input_stream.h"
#include "../utils/socket/buffered_output_stream.h"
#include "../processor/processor.h"
#include "../processor/request_response_constants.h"

std::pair<User*, String> Authenticate(BufferedSocketInputStream& inputStream, BufferedSocketOutputStream& outputStream);

void HandleConnectionRequest(ConnectionManager *connectionManager, ClientSocket clientSocket) {
    DEBUG_MSG("HandleConnectionRequest()");

    User* user = nullptr;
    try {
        BufferedSocketInputStream bufferedInputStream(&clientSocket);
        BufferedSocketOutputStream bufferedOutputStream(&clientSocket);

        auto pair = Authenticate(bufferedInputStream, bufferedOutputStream);
        user = pair.first;
        String databaseName = pair.second;

        connectionManager->AllocateConnection();

        ConnectionDescriptor connectionDescriptor(user, &databaseName, &bufferedInputStream, &bufferedOutputStream);
        Processor processor(&connectionDescriptor);
		processor.process();

        delete user;

		clientSocket.closeSocket();
        connectionManager->ReleaseConnection();

        DEBUG_MSG("Finish Handling a connection");
    } catch (Exception& e) {
        DEBUG_MSG("Got an exception: " << e.GetMessage());

		clientSocket.writeData(e.GetMessage(), e.GetMessageLength());
		clientSocket.closeSocket();
        delete user;
        connectionManager->ReleaseConnection();
    }
}

std::pair<User*, String> Authenticate(BufferedSocketInputStream& inputStream, BufferedSocketOutputStream& outputStream) {
    int8_t opCode = inputStream.nextByte();
    if (opCode != OpCode.AUTHENTICATION) throw Exception("Unexpected Opcode");

    DEBUG_MSG("Waiting for database");
    String databaseName = inputStream.nextCString();
    String userName = inputStream.nextCString();
    String password = inputStream.nextCString();

    DEBUG_MSG("Authenticating:: userName: " << userName << " Password: " << password);

    User* user = UserManager::getInstance()->authenticate(databaseName, userName, password);

	outputStream.appendByte(ResponseStatus.SUCCESS);
    return {user, databaseName};
}
