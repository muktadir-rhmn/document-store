//
// Created by Muktadir Rahman on 8/9/20.
//

#ifndef DOCUMENT_STORE_DOCUMENT_CONVERTER_H
#define DOCUMENT_STORE_DOCUMENT_CONVERTER_H

#include "../utils/data/byte_input_stream.h"
#include "../utils/exceptions/exception.h"
#include "document_writer.h"
#include "../storage_api/field_name_id_map.h"
#include "dr/dr_document_writer.h"
#include "dr/dr_document_reader.h"
#include "../utils/socket/buffered_input_stream.h"

using document::DocumentReader;
using document::dr::DRDocumentWriter;

class DocumentConverter {
public:
	static ByteOutputStream replaceFieldNamesWithIds(BufferedSocketInputStream* documentReader, FieldNameIDMap* fieldNameIdMap);

private:
	static ByteOutputStream
	replaceFieldNamesWithIds(DocumentReader& reader, FieldNameIDMap* fieldNameIDMap);
};


#endif //DOCUMENT_STORE_DOCUMENT_CONVERTER_H
