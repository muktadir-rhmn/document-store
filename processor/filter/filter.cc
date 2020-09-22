//
// Created by Muktadir Rahman on 22/9/20.
//

#include "filter.h"
#include "data_structures.h"
#include "../../document/bson_constants.h"

extern "C" {
	int condition_parse (struct Output* po);
	struct yy_buffer_state * condition__scan_string (const char *yy_str);
}

Filter::Filter(ccstring conditionString, FieldNameIDMap* fieldNameIdMap) {
	fieldNameIdMap_ = fieldNameIdMap;

	condition__scan_string(conditionString);

	Output output;
	output.fieldNameListHead = nullptr;
	output.root = &conditionTreeRoot_;
	condition_parse(&output);

	for (FieldName* t = output.fieldNameListHead; t ; ) {
		int fieldId = fieldNameIdMap->getFieldId(t->text);
		fieldIdValueMap_[fieldId] = ConditionTreeNode{NULL_};

		FieldName* tt = t->next;
		free(t);
		t = tt;
	}
}

bool Filter::satisfyCondition(DocumentReader* documentReader) {
	for (auto & itr : fieldIdValueMap_) {
		itr.second.nodeType = NULL_;
	}

	using document::FieldType;
	while (documentReader->next()) {
		auto fieldId = documentReader->curFieldIdAsInt();
		ConditionTreeNode* node = &fieldIdValueMap_[fieldId];

		auto fieldType = documentReader->curFieldType();
		if (fieldType == FieldType.INT64) {
			node->nodeType = INTEGER_;
			node->data.ll = documentReader->curValueAsInt64();
		}
		//todo: add other types
	}

	ConditionTreeNode result = evaluate(conditionTreeRoot_);
	return result.data.bl != 0;
}

ConditionTreeNode Filter::evaluate(ConditionTreeNode* root) {
	if (!isOperator(root->nodeType)) {
		if (root->nodeType == FIELD_NAME_) {
			return fieldIdValueMap_[fieldNameIdMap_->getFieldId(root->data.text)];
		} else {
			return *root;
		}
	}

	ConditionTreeNode left = evaluate(root->first);
	ConditionTreeNode right = evaluate(root->second);
	NodeType opType = root->nodeType;
	OpCode opCode = root->data.opCode;

	ConditionTreeNode result;
	if (opType == BOOLEAN_OPERATOR_) {
		assert(left.nodeType == BOOL_);
		assert(right.nodeType == BOOL_);

		result.nodeType = BOOL_;
		result.data.bl = doBooleanOperation(opCode, left.data.bl, right.data.bl);

		return result;
	} else if (opType == ARITHMETIC_OPERATOR_ && opCode == MODULUS_) {
		assert(left.nodeType == INTEGER_);
		assert(right.nodeType == INTEGER_);

		result.nodeType = INTEGER_;
		result.data.ll = left.data.ll % right.data.ll;

		return result;
	}

	//todo: handle the case of string comparisons and operations

	if (left.nodeType == INTEGER_) {
		long long leftVal  = left.data.ll;

		if (right.nodeType == INTEGER_) {
			long long rightVal = right.data.ll;

			if (opType == ARITHMETIC_OPERATOR_) {
				result.nodeType = INTEGER_;
				result.data.ll = doArithmeticOperation(opCode, leftVal, rightVal);
			} else if (opType == RELATIONAL_OPERATOR_) {
				result.nodeType = BOOL_;
				result.data.bl = doRelationalOperation(opCode, leftVal, rightVal);
			}

		} else if (right.nodeType == FLOAT_){
			double rightVal = right.data.dbl;

			if (opType == ARITHMETIC_OPERATOR_) {
				result.nodeType = FLOAT_;
				result.data.dbl = doArithmeticOperation(opCode, rightVal, leftVal);
			} else if (opType == RELATIONAL_OPERATOR_) {
				result.nodeType = BOOL_;
				result.data.bl = doRelationalOperation(opCode, leftVal, rightVal);
			}

		}

	} else if (left.nodeType == FLOAT_){
		double leftVal = left.data.dbl;
		if (right.nodeType == INTEGER_) {
			long long rightVal = right.data.ll;

			if (opType == ARITHMETIC_OPERATOR_) {
				result.nodeType = FLOAT_;
				result.data.dbl = doArithmeticOperation(opCode, leftVal, rightVal);
			} else if (opType == RELATIONAL_OPERATOR_) {
				result.nodeType = BOOL_;
				result.data.bl = doRelationalOperation(opCode, leftVal, rightVal);
			}

		} else if (right.nodeType == FLOAT_) {
			double rightVal = right.data.dbl;

			if (opType == ARITHMETIC_OPERATOR_) {
				result.nodeType = FLOAT_;
				result.data.dbl = doArithmeticOperation(opCode, leftVal, rightVal);
			} else if (opType == RELATIONAL_OPERATOR_) {
				result.nodeType = BOOL_;
				result.data.bl = doRelationalOperation(opCode, leftVal, rightVal);
			}

		}
	}

	return result;
}

Filter::~Filter() {
	releaseConditionTree(conditionTreeRoot_);

}

void Filter::releaseConditionTree(ConditionTreeNode* root) {
	if (!isOperator(root->nodeType)) {
		if (root->nodeType == STRING_) free(root->data.text);
		free(root);
		return;
	}

	releaseConditionTree(root->first);
	releaseConditionTree(root->second);
	free(root);
}
