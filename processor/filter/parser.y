%{
   #include <stdio.h>
   #include <string.h>
   #include <stdlib.h>
   #include "data_structures.h"

   #define CONDITION_STYPE struct ConditionTreeNode   /* type for yacc stack */

	int condition_lex (void);
   int yyerror(struct Output* po, const char * s);

   int addFieldName(struct Output* po, char* fieldNameStr) {
        struct FieldName* fieldName = (struct FieldName*) malloc(sizeof(struct FieldName));
        int len = strlen(fieldNameStr);
        fieldName->text = (char*) malloc(len + 1);
        strcpy(fieldName->text, fieldNameStr);

        fieldName->next = po->fieldNameListHead;
        po->fieldNameListHead = fieldName;

        return len;
   }

   void addChildren(struct ConditionTreeNode* root, struct ConditionTreeNode* first, struct ConditionTreeNode* second) {
   		root->first = (struct ConditionTreeNode*) malloc(sizeof(struct ConditionTreeNode));
   		*(root->first) = *first;
   		root->second = (struct ConditionTreeNode*) malloc(sizeof(struct ConditionTreeNode));
   		*(root->second) = *second;
   }

%}
%define api.prefix {condition_}

%token INTEGER FLOAT STRING IN BETWEEN NAME_STRING OPENING_BRACKET CLOSING_BRACKET OPENING_CURLY CLOSING_CURLY QUOTE COMMA DOT AND OR PLUS MINUS MULTIPLY DIVIDE MODULUS EQUAL NOT_EQUAL GREATER GREATER_EQUAL LESS LESS_EQUAL
%left OR
%left AND
%left PLUS MINUS
%left MULTIPLY DIVIDE MODULUS
%parse-param {struct Output* po}

%%
start : conditions {
            *po->root = (struct ConditionTreeNode*) malloc(sizeof(struct ConditionTreeNode));
            **po->root = $1;
        }
      ;

conditions : condition  {
					printf("conditions->condition\n");

					$$ = $1;
				}
           | conditions AND conditions {
           			printf("conditions->conditions AND conditions\n");

           			$$.nodeType = BOOLEAN_OPERATOR_;
           			$$.data.opCode = AND_;
           			addChildren(&$$, &$1, &$3);
           		}
           | conditions OR conditions{
					printf("conditions->conditions OR conditions\n");

					$$.nodeType = BOOLEAN_OPERATOR_;
					$$.data.opCode = OR_;
					addChildren(&$$, &$1, &$3);
				}
           | OPENING_BRACKET conditions CLOSING_BRACKET {
           			printf("conditions->(conditions)\n");

           			$$ = $2;
           		}
           ;

condition  : expression comparator expression {
                    printf("condition->expression comparator expression\n");

                    $$.nodeType = RELATIONAL_OPERATOR_;
                    $$.data.opCode = $2.data.opCode;
                    addChildren(&$$, &$1, &$3);
               }
//           | expression IN OPENING_BRACKET expression_list CLOSING_BRACKET {printf("c->e in (elist) \n");}
//           | expression BETWEEN number AND number {printf("c->e between n1 and n2\n");}
           ;

//expression_list : expression
//                | expression COMMA expression_list
//                ;


expression  : field_value {
                    printf("expression->field_value\n");
                    $$ = $1;
              }
            | expression PLUS expression {
                    printf("expression->expression PLUS expression\n");

                    $$.nodeType = ARITHMETIC_OPERATOR_;
					$$.data.opCode = PLUS_;
					addChildren(&$$, &$1, &$3);
                }
            | expression MINUS expression {
                    printf("expression->expression MINUS expression\n");

                    $$.nodeType = ARITHMETIC_OPERATOR_;
                    $$.data.opCode = MINUS_;
                    addChildren(&$$, &$1, &$3);
                }
            | expression MULTIPLY expression {
                	printf("expression->expression MULTIPLY expression\n");

                	$$.nodeType = ARITHMETIC_OPERATOR_;
                	$$.data.opCode = MULTIPLY_;
                	addChildren(&$$, &$1, &$3);
            	}
            | expression DIVIDE expression {
            		printf("expression->expression DIVIDE expression\n");

            		$$.nodeType = ARITHMETIC_OPERATOR_;
            		$$.data.opCode = DIVIDE_;
            		addChildren(&$$, &$1, &$3);
            	}
            | expression MODULUS expression {
            		printf("expression->expression MODULUS expression\n");

            		$$.nodeType = ARITHMETIC_OPERATOR_;
            		$$.data.opCode = MODULUS_;
            		addChildren(&$$, &$1, &$3);
            	}
            | OPENING_BRACKET expression CLOSING_BRACKET {
            		printf("(expression)\n");

            		$$ = $2;
            	}
            ;

comparator : EQUAL {
					printf("comparator->EQUAL\n");

					$$.nodeType = RELATIONAL_OPERATOR_;
					$$.data.opCode = EQUAL_;
				}
           | NOT_EQUAL{
					printf("comparator->NOT_EQUAL\n");

					$$.nodeType = RELATIONAL_OPERATOR_;
					$$.data.opCode = NOT_EQUAL_;
				}
           | GREATER  {
           			printf("comparator->GREATER\n");

                    $$.nodeType = RELATIONAL_OPERATOR_;
                    $$.data.opCode = GREATER_;
                }
           | GREATER_EQUAL {
					printf("comparator->GREATER_EQUAL\n");

					$$.nodeType = RELATIONAL_OPERATOR_;
                    $$.data.opCode = GREATER_EQUAL_;
           		}
           | LESS {
           			printf("comparator->LESS\n");

           			$$.nodeType = RELATIONAL_OPERATOR_;
           			$$.data.opCode = LESS_;
           		}
           | LESS_EQUAL {
           			printf("comparator->LESS_EQUAL\n");

           			$$.nodeType = RELATIONAL_OPERATOR_;
           			$$.data.opCode = LESS_EQUAL_;
           		}
           ;

field_value : NAME_STRING {
					printf("field_Value->NAME_STRING\n");

					int len = addFieldName(po, $1.data.text);

					$$.nodeType = FIELD_NAME_;

					$$.data.text = (char*) malloc(len + 1);
					strcpy($$.data.text, $1.data.text);
					$$.second = $$.first = 0;
				}
            | QUOTE STRING QUOTE {
            		printf("field_Value->QUOTE STRING QUOTE\n");

            		$$.nodeType = STRING_;

            		size_t len = strlen($1.data.text);
            		$$.data.text = (char*) malloc(len + 1);
                    strcpy($$.data.text, $1.data.text);
            	}
            | number {
                    printf("field_value->number\n");
                    $$ = $1;
                }
            ;

number : INTEGER  {
				printf("number->INTEGER\n");

				$$.nodeType = INTEGER_;
				$$.data.ll = atoi($1.data.text);
			}
        | FLOAT {
        		printf("number->FLOAT\n");

				$$.nodeType = FLOAT_;
                $$.data.ll = strtof($1.data.text, NULL);
        	}
        ;

%%

#include "lex.condition_.c"

int yyerror(struct Output* po, const char * s){
 fprintf (stderr, "%s\n", s);
 return 0;
}

