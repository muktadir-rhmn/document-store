//
// Created by Muktadir Rahman on 8/9/20.
//

#include "document_converter.h"
#include "bson_constants.h"
#include "../utils/debug/debug.h"
#include "dr/dr_array_writer.h"

using document::FieldType;
using document::dr::DRArrayWriter;
using document::dr::DRDocumentReader;

ByteOutputStream DocumentConverter::replaceFieldNamesWithIds(BufferedSocketInputStream* inputStream, FieldNameIDMap* fieldNameIdMap) {
	DRDocumentReader documentReader(inputStream, document::FieldIdType::kString);
	return replaceFieldNamesWithIds(documentReader, fieldNameIdMap);
}

ByteOutputStream DocumentConverter::replaceFieldNamesWithIds(DocumentReader& documentReader, FieldNameIDMap* fieldNameIdMap) {
	ByteOutputStream byteOutputStream;
	DRDocumentWriter documentWriter(&byteOutputStream);

	while (documentReader.next()) {
		String fieldName = documentReader.curFieldIdAsCString();

		document::fieldId_t fieldId = fieldNameIdMap->getFieldId(fieldName);

		document::fieldType_t fieldType = documentReader.curFieldType();

		DEBUG_MSG("Field\n\tfield name: " << fieldName );
		if (fieldType == FieldType.INT64) {
			int64 val = documentReader.curValueAsInt64();
			DEBUG_MSG("\n\tfield value: <INT64> " << val);

			documentWriter.appendInt64(&fieldId, val);
		} else if (fieldType == FieldType.STRING) {
			String val = documentReader.curValueAsString();
			DEBUG_MSG("\n\tfield value: <String> " << val);

			documentWriter.appendCString(&fieldId, val.c_str(), val.size());
		} else if (fieldType == FieldType.DOCUMENT) {
			DEBUG_MSG("\n\tfield value: <Document> ");

			DocumentReader* embeddedDocReader = documentReader.curValueAsDocument();

			ByteOutputStream bot = replaceFieldNamesWithIds(*embeddedDocReader, fieldNameIdMap);
			RawData rawData = bot.getRawData();
			documentWriter.appendDocument(&fieldId, rawData);
		} else if (fieldType == FieldType.ARRAY) {
			ArrayReader* arrayReader = documentReader.curValueAsArray();

			ByteOutputStream bot = replaceFieldNamesWithIds(arrayReader, fieldNameIdMap);
			RawData rawData = bot.getRawData();
			documentWriter.appendArray(&fieldId, rawData);
		}
	}
	return byteOutputStream;
}

ByteOutputStream DocumentConverter::replaceFieldNamesWithIds(ArrayReader* arrayReader, FieldNameIDMap* fieldNameIDMap) {
	ByteOutputStream byteOutputStream;
	DRArrayWriter arrayWriter(&byteOutputStream);

	while (arrayReader->next()) {
		document::fieldType_t elementType = arrayReader->curElementType();

		if (elementType == FieldType.INT64) {
			int64 val = arrayReader->curValueAsInt64();
			arrayWriter.appendInt64(val);
		} else if (elementType == FieldType.STRING) {
			String val = arrayReader->curValueAsString();
			arrayWriter.appendCString(val.c_str(), val.size());
		}
	}

	return byteOutputStream;
}
