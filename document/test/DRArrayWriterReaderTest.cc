//
// Created by Muktadir Rahman on 19/9/20.
//

#include "gtest/gtest.h"
#include "../dr/dr_array_writer.h"
#include "../dr/dr_array_reader.h"
#include "../dr/dr_document_writer.h"
#include "../dr/dr_document_reader.h"
#include "../../utils/data/data_utils.h"

namespace document {
using dr::DRArrayWriter;
using dr::DRArrayReader;

TEST(DRArrayWriterReaderTest, simple_Type) {
	ByteOutputStream os;
	DRArrayWriter arrayWriter(&os);

	arrayWriter.appendInt64(1);
	arrayWriter.appendCString("Muktadir");
	arrayWriter.appendCString("Rahman");
	arrayWriter.appendCString("kandipara");
	arrayWriter.appendCString("mymensingh");

	RawData rawData = os.getRawData();
	DataUtils::print(rawData.bytes, rawData.size);

	DRArrayReader arrayReader(rawData);
	ASSERT_EQ(arrayReader.next(), true);
	ASSERT_EQ(arrayReader.curElementType(), FieldType.INT64);
	ASSERT_EQ(arrayReader.curValueAsInt64(), 1);

	ASSERT_EQ(arrayReader.next(), true);
	ASSERT_EQ(arrayReader.curElementType(), FieldType.STRING);
	ASSERT_EQ(String(arrayReader.curValueAsString()), String("Muktadir"));

	ASSERT_EQ(arrayReader.next(), true);
	ASSERT_EQ(arrayReader.curElementType(), FieldType.STRING);
	ASSERT_EQ(String(arrayReader.curValueAsString()), String("Rahman"));

	ASSERT_EQ(arrayReader.next(), true);
	ASSERT_EQ(arrayReader.curElementType(), FieldType.STRING);
	ASSERT_EQ(String(arrayReader.curValueAsString()), String("kandipara"));

	ASSERT_EQ(arrayReader.next(), true);
	ASSERT_EQ(arrayReader.curElementType(), FieldType.STRING);
	ASSERT_EQ(String(arrayReader.curValueAsString()), String("mymensingh"));

}

}