//
// Created by Muktadir Rahman on 6/9/20.
//

#include "../utils/logger/logger.h"
#include "processor.h"
#include "../utils/exceptions/exception.h"
#include "database_processor.h"
#include "../storage_api/database_manager.h"
#include "collection_processor.h"
#include "request_response_constants.h"

Processor::Processor(ConnectionDescriptor *connectionDescriptor) {
    conDescriptor_ = connectionDescriptor;
}

void Processor::process() {
    DEBUG_MSG("Processing");

    Database* database = DatabaseManager::GetInstance()->getDatabase(conDescriptor_->getDatabaseName());
    DEBUG_MSG(conDescriptor_->getDatabaseName());

    int8_t opCode;
    while ((opCode = conDescriptor_->getInputStream()->nextByte()) != OpCode.CLOSE_CONNECTION) {
        DEBUG_MSG("opCode" << opCode);
        if (opCode == OpCode.CREATE_COLLECTION) {
			DatabaseProcessor::processCreateCollection(database, conDescriptor_);

        } else if (opCode == OpCode.RENAME_COLLECTION) {
			DatabaseProcessor::processRenameCollection(database, conDescriptor_);

        } else if (opCode == OpCode.DELETE_COLLECTION) {
			DatabaseProcessor::processDeleteCollection(database, conDescriptor_);

        } else if (opCode == OpCode.INSERT_DOCUMENT) {
			CollectionProcessor::processInsertDocument(database, conDescriptor_);

        } else if (opCode == OpCode.UPDATE_DOCUMENT) {
			CollectionProcessor::processUpdateDocument(database, conDescriptor_);

        } else if (opCode == OpCode.DELETE_DOCUMENT) {
			CollectionProcessor::processDeleteDocument(database, conDescriptor_);

        } else if (opCode == OpCode.QUERY_DOCUMENT) {
			CollectionProcessor::processQuery(database, conDescriptor_);

        } else {
            throw Exception("Invalid Opcode");
        }
    }
	DatabaseManager::GetInstance()->releaseDatabase(database);
}
