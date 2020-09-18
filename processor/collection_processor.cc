//
// Created by Muktadir Rahman on 7/9/20.
//

#include "collection_processor.h"
#include "../document/document_converter.h"
#include "../utils/debug/debug.h"
#include "request_response_constants.h"
#include "../utils/data/data_utils.h"


using document::dr::DRDocumentWriter;

void CollectionProcessor::processInsertDocument(Database* database, ConnectionDescriptor *conDescriptor) {
    Collection* collection = CollectionProcessor::retrieveCollection(database, conDescriptor);

    ByteOutputStream outputStream = DocumentConverter::replaceFieldNamesWithIds(conDescriptor->getInputStream(), collection->getFieldNameIdMap());
    RawData rawData = outputStream.getRawData();

	collection->insertDocument(rawData);

	DataUtils::print(rawData.bytes, rawData.size);

	conDescriptor->getOutputStream()->appendByte(ResponseStatus.SUCCESS);
	conDescriptor->getOutputStream()->flush();
}

void CollectionProcessor::processUpdateDocument(Database* database, ConnectionDescriptor *conDescriptor) {

}

void CollectionProcessor::processDeleteDocument(Database* database, ConnectionDescriptor *conDescriptor) {

}

void CollectionProcessor::processQuery(Database* database, ConnectionDescriptor *conDescriptor) {
    DEBUG_MSG("Processing query");
    Collection* collection = CollectionProcessor::retrieveCollection(database, conDescriptor);

	auto outputStream = conDescriptor->getOutputStream();
	outputStream->appendByte(ResponseStatus.SUCCESS);

    collection->getFieldNameIdMap()->outputData(outputStream);

    DEBUG_MSG("Sending documents");
    ByteOutputStream byteOutputStream = collection->getDocuments();
    RawData data = byteOutputStream.getRawData();
	outputStream->appendBytes(data.bytes, data.size);
	outputStream->appendInt32(0);
    DEBUG_MSG("Sent documents");
}

Collection* CollectionProcessor::retrieveCollection(Database *database, ConnectionDescriptor *conDescriptor) {
    String collectionName = conDescriptor->getInputStream()->nextCString();
	DEBUG_MSG("Collection Name: " << collectionName);
	Collection* collection = database->getCollection(collectionName);
    return collection;
}
