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

using document::DocumentReader;
using document::dr::DRDocumentWriter;

class DocumentConverter {
public:
	static DRDocumentWriter replaceFieldNamesWithIds(DocumentReader& documentReader, FieldNameIDMap* fieldNameIdMap);

};


#endif //DOCUMENT_STORE_DOCUMENT_CONVERTER_H
