//
// Created by Muktadir Rahman on 22/9/20.
//

#ifndef DOCUMENT_STORE_FILTER_H
#define DOCUMENT_STORE_FILTER_H


#include "../../typedefs.h"
#include "../../storage/api/field_name_id_map.h"
#include "../../document/document_reader.h"
#include "data_structures.h"

using document::DocumentReader;

class Filter {
public:
	Filter(ccstring conditionString, FieldNameIDMap* fieldNameIdMap);
	~Filter();
	bool satisfyCondition(DocumentReader* documentReader);

private:
	FieldNameIDMap* fieldNameIdMap_;
	Map<int, ConditionTreeNode> fieldIdValueMap_;
	ConditionTreeNode* conditionTreeRoot_;

	template <typename T1, typename T2>
	byte doRelationalOperation(enum OpCode opCode, T1 val1, T2 val2) {
		bool boolVal;
		switch (opCode) {
			case EQUAL_:
				boolVal = val1 == val2;
				break;
			case NOT_EQUAL_:
				boolVal = val1 != val2;
				break;
			case GREATER_:
				boolVal = val1 > val2;
				break;
			case GREATER_EQUAL_:
				boolVal = val1 >= val2;
				break;
			case LESS_:
				boolVal = val1 < val2;
				break;
			case LESS_EQUAL_:
				boolVal = val1 <= val2;
				break;
			default:
				assert(false);
		}
		return boolVal;
	}

	byte doBooleanOperation(enum OpCode opCode, bool  val1, bool val2) {
		bool boolVal;
		switch (opCode) {
			case AND_:
				boolVal = val1 && val2;
				break;
			case OR_:
				boolVal = val1 || val2;
				break;
			default:
				assert(false);
		}
		return boolVal;
	}

	template <typename T1, typename T2>
	T1 doArithmeticOperation(enum OpCode opCode, T1 val1, T2 val2) {
		T1 result = -1;
		switch (opCode) {
			case PLUS_:
				result = val1 + val2;
				break;
			case MINUS_:
				result = val1 - val2;
				break;
			case MULTIPLY_:
				result = val1 * val2;
				break;
			case DIVIDE_:
				result = val1 / val2;
				break;
			default:
				assert(false);
		}
		return result;
	}

	bool isOperator(NodeType nodeType) {
		return nodeType == ARITHMETIC_OPERATOR_ || nodeType == RELATIONAL_OPERATOR_ || nodeType == BOOLEAN_OPERATOR_;
	}

	ConditionTreeNode evaluate(ConditionTreeNode* root);

	void releaseConditionTree(ConditionTreeNode* root);
};


#endif //DOCUMENT_STORE_FILTER_H
