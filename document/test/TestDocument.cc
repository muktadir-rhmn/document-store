//
// Created by Muktadir Rahman on 18/9/20.
//

#include "gtest/gtest.h"
#include "../dr/dr_document_writer.h"
#include "../dr/dr_document_reader.h"
#include "../../utils/data/data_utils.h"

namespace document {
using dr::DRDocumentWriter;
using dr::DRDocumentReader;

TEST(DRDocumentWriterReaderTest, StringId_FlatDocument) {
	ByteOutputStream byteOutputStream;
	DRDocumentWriter documentWriter(&byteOutputStream, FieldIdType::kString);

	String s = "id";
	documentWriter.appendInt64((void*) s.c_str(), 1);

	s = "name";
	documentWriter.appendCString((void*) s.c_str(), "muktadir");

	RawData rawData = byteOutputStream.getRawData();
	DataUtils::print(rawData.bytes, rawData.size);

	DRDocumentReader documentReader(ByteInputStream(rawData), FieldIdType::kString);

	ASSERT_EQ(documentReader.next(), true);
	ASSERT_EQ(String (documentReader.curFieldIdAsCString()), String("id"));
	ASSERT_EQ(documentReader.curValueAsInt64(), 1);

	ASSERT_EQ(documentReader.next(), true);
	ASSERT_EQ(String (documentReader.curFieldIdAsCString()), String("name"));
	ASSERT_EQ(String (documentReader.curValueAsString()), String("muktadir"));
}

TEST(DRDocumentWriterReaderTest, StringId_EmbeddedDocument) {
	ByteOutputStream osYetEmbedded;
	DRDocumentWriter yetEmbedded(&osYetEmbedded, FieldIdType::kString);
	String s = "name";
	yetEmbedded.appendCString((void*) s.c_str(), "muktadir");

	ByteOutputStream osEmbedded;
	DRDocumentWriter embedded(&osEmbedded, FieldIdType::kString);

	s = "name";
	embedded.appendCString((void*) s.c_str(), "muktadir");

	s = "yet_embedded";
	RawData rawDataYetEmbedded = osYetEmbedded.getRawData();
	embedded.appendDocument((void*) s.c_str(), rawDataYetEmbedded);

	ByteOutputStream os;
	DRDocumentWriter documentWriter(&os, FieldIdType::kString);

	s = "id";
	documentWriter.appendInt64((void*) s.c_str(), 1);

	s = "embedded";
	RawData rawDataEmbedded = osEmbedded.getRawData();
	documentWriter.appendDocument((void*) s.c_str(), rawDataEmbedded);

	RawData rawData = os.getRawData();
	DataUtils::print(rawData.bytes, rawData.size);

	ByteInputStream inputStream(rawData);
	DRDocumentReader readerTop(inputStream, FieldIdType::kString);

	ASSERT_EQ(readerTop.next(), true);
	ASSERT_EQ(String(readerTop.curFieldIdAsCString()), String("id"));
	ASSERT_EQ(readerTop.curFieldType(), FieldType.INT64);
	ASSERT_EQ(readerTop.curValueAsInt64(), 1);

	ASSERT_EQ(readerTop.next(), true);
	ASSERT_EQ(String(readerTop.curFieldIdAsCString()), String("embedded"));
	ASSERT_EQ(readerTop.curFieldType(), FieldType.DOCUMENT);

	DocumentReader* embeddedReader = readerTop.curValueAsDocument();
	ASSERT_EQ(embeddedReader->next(), true);
	ASSERT_EQ(embeddedReader->curFieldType(), FieldType.STRING);
	ASSERT_EQ(String(embeddedReader->curFieldIdAsCString()), String("name"));
	ASSERT_EQ(String(embeddedReader->curValueAsString()), String("muktadir"));
	ASSERT_EQ(embeddedReader->next(), true);
	ASSERT_EQ(String(embeddedReader->curFieldIdAsCString()), String("yet_embedded"));
	ASSERT_EQ(embeddedReader->curFieldType(), FieldType.DOCUMENT);

	DocumentReader* yetEmbeddedReader = embeddedReader->curValueAsDocument();
	ASSERT_EQ(yetEmbeddedReader->next(), true);
	ASSERT_EQ(String(yetEmbeddedReader->curFieldIdAsCString()), String("name"));
	ASSERT_EQ(String(yetEmbeddedReader->curValueAsString()), String("muktadir"));
}

}