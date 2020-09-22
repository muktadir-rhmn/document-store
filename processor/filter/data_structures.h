//
// Created by Muktadir Rahman on 19/9/20.
//

#ifndef COMPILER_CPP_POC_DATA_STRUCTURES_H
#define COMPILER_CPP_POC_DATA_STRUCTURES_H

enum OpCode {
	EQUAL_,
	NOT_EQUAL_,
	GREATER_,
	GREATER_EQUAL_,
	LESS_,
	LESS_EQUAL_,

	AND_,
	OR_,

	PLUS_,
	MINUS_,
	MULTIPLY_,
	DIVIDE_,
	MODULUS_,
};

union Data {
	enum OpCode opCode;
	char* text;
	double dbl;
	long long ll;
	char bl;
};

enum NodeType {
	ARITHMETIC_OPERATOR_,
	RELATIONAL_OPERATOR_,
	BOOLEAN_OPERATOR_,

	BOOL_,
	INTEGER_,
	FLOAT_,

	STRING_,
	FIELD_NAME_,

	NULL_
};

struct ConditionTreeNode {
	enum NodeType nodeType;
	union Data data;

	struct ConditionTreeNode* first;
	struct ConditionTreeNode* second;
};

struct FieldName {
	char* text;

	struct FieldName* next;
};

struct Output {
	struct FieldName* fieldNameListHead;
	struct ConditionTreeNode** root;
};

#endif //COMPILER_CPP_POC_DATA_STRUCTURES_H
