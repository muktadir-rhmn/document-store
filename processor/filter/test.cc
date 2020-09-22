//
// Created by Muktadir Rahman on 22/9/20.
//

#include "gtest/gtest.h"
#include "../../storage/api/field_name_id_map.h"
#include "../../document/dr/dr_document_writer.h"
#include "../../document/dr/dr_document_reader.h"
#include "filter.h"
#include "../../utils/data/data_utils.h"

using document::dr::DRDocumentWriter;
using document::dr::DRDocumentReader;

TEST(DocumentFilterTest, IntegerType) {
	FieldNameIDMap fieldNameIdMap;
	fieldNameIdMap.putPair("id", 0);

	ByteOutputStream os;
	DRDocumentWriter writer(&os);

	document::fieldId_t id = 0;
	writer.appendInt64(&id, 0);

	RawData rawData = os.getRawData();
	DataUtils::print(rawData.bytes, rawData.size);
	DRDocumentReader reader(ByteInputStream{rawData});
	{
		Filter filter("id + 2 > 0", &fieldNameIdMap);
		ASSERT_EQ(filter.satisfyCondition(&reader), true);
	}
}