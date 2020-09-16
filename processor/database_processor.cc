//
// Created by Muktadir Rahman on 7/9/20.
//
#include "database_processor.h"

#include "../utils/logger/logger.h"


void DatabaseProcessor::processCreateCollection(Database *database, ConnectionDescriptor *conDescriptor) {
    String collectionName = conDescriptor->getInputStream()->nextCString();

    DEBUG_MSG("Creating collection: " << collectionName);
	database->createCollection(collectionName);

//	conDescriptor->getOutputStream()->writeByte(0x00);
	conDescriptor->getOutputStream()->flush();
}

void DatabaseProcessor::processRenameCollection(Database *database, ConnectionDescriptor *conDescriptor) {
    String oldCollectionName = conDescriptor->getInputStream()->nextCString();
    String newCollectionName = conDescriptor->getInputStream()->nextCString();

    DEBUG_MSG("Renaming collection: " << oldCollectionName << " --> " << newCollectionName);
	database->renameCollection(oldCollectionName, newCollectionName);

	conDescriptor->getOutputStream()->appendByte(0x00);
	conDescriptor->getOutputStream()->flush();
}

void DatabaseProcessor::processDeleteCollection(Database *database, ConnectionDescriptor *conDescriptor) {
    String collectionName = conDescriptor->getInputStream()->nextCString();

    DEBUG_MSG("Deleting collection: " << collectionName);
	database->deleteCollection(collectionName);

	conDescriptor->getOutputStream()->appendByte((byte) 0x00);
	conDescriptor->getOutputStream()->flush();
}
