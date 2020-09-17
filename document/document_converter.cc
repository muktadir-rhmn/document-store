//
// Created by Muktadir Rahman on 8/9/20.
//

#include "document_converter.h"
#include "bson_constants.h"
#include "../utils/debug/debug.h"

using document::FieldType;

DRDocumentWriter DocumentConverter::replaceFieldNamesWithIds(DocumentReader& documentReader, FieldNameIDMap* fieldNameIdMap) {
	DRDocumentWriter writer; //todo: for each embedded document, a new output stream is created, which is not necessary

	while (documentReader.next()) {
		String fieldName = documentReader.curFieldIdAsCString();

		document::fieldId_t fieldId = fieldNameIdMap->getFieldId(fieldName);

		document::fieldType_t fieldType = documentReader.curFieldType();

		DEBUG_MSG("Field\n\tfield name: " << fieldName );
		if (fieldType == FieldType.INT64) {
			int64 val = documentReader.curValueAsInt64();
			DEBUG_MSG("\n\tfield value: <INT64> " << val);

			writer.appendInt64(&fieldId, val);
		} else if (fieldType == FieldType.STRING) {
			String val = documentReader.curValueAsString();
			DEBUG_MSG("\n\tfield value: <String> " << val);

			writer.appendCString(&fieldId, val.c_str(), val.size());
		} else if (fieldType == FieldType.DOCUMENT) {
			DEBUG_MSG("\n\tfield value: <Document> ");

			DocumentReader* embeddedDocReader = documentReader.curValueAsDocument();
			DRDocumentWriter embeddedDocWriter = replaceFieldNamesWithIds(*embeddedDocReader, fieldNameIdMap);
			writer.appendDocument(&fieldId, embeddedDocWriter);
		}
	}

	return writer;
}
