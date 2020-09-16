//
// Created by Muktadir Rahman on 8/9/20.
//

#include "document_converter.h"
#include "bson_constants.h"
#include "../utils/logger/logger.h"

using document::FieldType;

DRDocumentWriter DocumentConverter::replaceFieldNamesWithIds(DocumentReader& documentReader, FieldNameIDMap* fieldNameIdMap) {
	DRDocumentWriter writer;

	while (documentReader.hasNext()) {
		String fieldName = documentReader.fieldIdAsCString();

		document::fieldId_t fieldId = fieldNameIdMap->getFieldId(fieldName);

		document::fieldType_t fieldType = documentReader.fieldType();

		DEBUG_MSG("Field\n\tfield name: " << fieldName );
		if (fieldType == FieldType.INT64) {
			int64 val = documentReader.valueAsInt64();
			DEBUG_MSG("\n\tfield value: <INT64> " << val);

			writer.appendInt64(&fieldId, val);
		} else if (fieldType == FieldType.STRING) {
			String val = documentReader.valueAsString();
			DEBUG_MSG("\n\tfield value: <String> " << val);

			writer.appendCString(&fieldId, val.c_str(), val.size());
		} else if (fieldType == FieldType.DOCUMENT) {
			DEBUG_MSG("\n\tfield value: <Document> ");

			DocumentReader* embeddedDocReader = documentReader.valueAsDocument();
			DRDocumentWriter embeddedDocWriter = replaceFieldNamesWithIds(*embeddedDocReader, fieldNameIdMap);
			writer.appendDocument(&fieldId, embeddedDocWriter);
		}

		documentReader.next();
	}

	return writer;
}
