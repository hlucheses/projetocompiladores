#ifndef INC_GRAMATICA
#define INC_GRAMATICA

/*
1- typedef-name: identifier

Regra antiga
 namespace-name: original-name-space | namespace-alias
 original-name-space : identifier
 namespace-alias : identifier
*/
bool Parser::typedef_name() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else {
		return false;
	}
}

/*
2- namespace-name : identifier
*/
bool Parser::namespace_name() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else {
		return false;
	}
}

/*
3- class-name : identifier class-name1
   class-name1: < class-name2
   class-name2: template-argument-list > | > 
*/

bool Parser::class_name() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (class_name1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::class_name1() {
	if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
		if (class_name2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::class_name2() {
	if (template_argument_list()) {
		if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
		return true;
	} else {
		return 0;
	}
}

/*
4- enum-name : identifier
*/
bool Parser::enum_name() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else {
		return false;
	}
}

/*
5- template-name : identifier
*/
bool Parser::template_name() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
literal: integer-literal | character-literal | floating-literal | string-literal |boolean-literal

22- literal : integer-literal | character-literal | floating-literal | string-literal | boolean-literal
*/
bool Parser::literal() {
	if (compararTokenAtual("TOKEN_INTEGER_LITERAL")) {
		return true;
	} else if (compararTokenAtual("TOKEN_CHAR_LITERAL")) {
		return true;
	} else if (compararTokenAtual("TOKEN_FLOATING_POINT_LITERAL")) {
		return true;
	} else if (compararTokenAtual("TOKEN_STRING_LITERAL")) {
		return true;
	} else if (boolean_literal()) {
		return true;
	} else {
		return false;
	}
}

/*
47- boolean-literal: true | false
*/
bool Parser::boolean_literal() {
	if (compararTokenAtual("TOKEN_KEYWORD_TRUE")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_FALSE")) {
		return true;
	} else {
		return false;
	}
}

/*
48- translation-unit: declaration-seq | vazio
*/
bool Parser::translation_unit() {
	if (declaration_seq()) {
		return true;
	} else {
		return true;
	}
}

/*
49- primary-expression: literal | this | ( expression ) | id-expression
*/
bool Parser::primary_expression() {
	if (literal()) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_THIS")) {
		return true;
	} else if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (expression()) {
			if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (id_expression()) {
		return true;
	} else {
		return false;
	}
}

/*
50- id-expression: unqualified-id | qualified-id
*/
bool Parser::id_expression() {
	if (unqualified_id()) {
		return true;
	} else if (qualified_id()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
unqualified-id: identifier | operator-function-id | conversion-function-id| ~ class-name |template-id

51- unqualified-id: identifier | operator unqualified-id1
	unqualified-id1: operator-function-id | conversion-function-id | ~ class-name | template-id
*/
bool Parser::unqualified_id() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_OPERATOR")){
		if (unqualified_id1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::unqualified_id1() {
	if (operator_function_id()) {
		return true;
	} else if (conversion_function_id()) {
		return true;
	} else if (compararTokenAtual("TOKEN_BITWISE_NOT_OPERATOR")) {
		if (class_name()) {
			return true;
		} else {
			return false;
		}
	} else if (template_id()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
qualified-id: ::opt nested-name-specifier templateopt unqualified-id | :: identifier | :: operator-function-id | :: template-id

52- qualified-id: :: qualified-id1 | qualified-id2
    qualified-id1: qualified-id2 | identifier | operator-function-id | template-id
    qualified-id2: nested-name-specifier qualified-id3
    qualified-id3: template unqualified-id | unqualified-id
*/
bool Parser::qualified_id() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (qualified_id1()) {
			return true;
		} else {
			return false;
		}
	} else if (qualified_id2()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::qualified_id1() {
	if (qualified_id2()) {
		return true;
	} else if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else if (operator_function_id()) {
		return true;
	} else if (template_id()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::qualified_id2() {
	if (nested_name_specifier()) {
		if (qualified_id3()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::qualified_id3() {
	if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (unqualified_id()) {
			return true;
		} else {
			return false;
		}
	} else if (unqualified_id()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
nested-name-specifier: type-name :: | namespace-name :: | nested-name-specifier | identifier :: | nested-name-specifier templateopt template-id ::

53-  nested-name-specifier: identifier nested-name-specifier1
     nested-name-specifier1: type-name  :: nested-name-specifier2 | :: nested-name-specifier2
     nested-name-specifier2: identifier nested-name-specifier3 | template identifier nested-name-specifier5
     nested-name-specifier3: :: | < nested-name-specifier4
     nested-name-specifier4:  template-argument-list > :: | > ::
     nested-name-specifier5: < nested-name-specifier4
*/

bool Parser::nested_name_specifier() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (nested_name_specifier1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::nested_name_specifier1() {
	if (type_name()) {
		if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OEPERATOR")) {
			if (nested_name_specifier2()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OEPERATOR")) {
		if (nested_name_specifier2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::nested_name_specifier2() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (nested_name_specifier3()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (compararTokenAtual("TOKEN_IDENTIFIER")) {
			if (nested_name_specifier5()) {
				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}

bool Parser::nested_name_specifier3() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
		if (nested_name_specifier4()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::nested_name_specifier4() {
	if (template_argument_list()) {
		if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
			if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
		if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::nested_name_specifier5() {
	if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
		if (nested_name_specifier5()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
Regra antiga

postfix-expression:primary-expression |
postfix-expression [ expression ] |
postfix-expression ( expression-listopt ) |
simple-type-specifier ( expression-listopt ) |
typename-specifier ( expression-listopt ) |
postfix-expression . templateopt id-expression |
postfix-expression -> templateopt id-expression |
postfix-expression . pseudo-destructor-name |
postfix-expression -> pseudo-destructor-name |
postfix-expression ++ |
postfix-expression -- |
dynamic_cast < type-id > ( expression ) |
static_cast < type-id > ( expression ) |
reinterpret_cast < type-id > ( expression ) |
const_cast < type-id > ( expression ) |
typeid ( expression ) |
typeid ( type-id )

54- postfix-expression: primary-expression postfix-expression1 | simple-type-specifier ( postfix-expression2 | typename-specifier ( postfix-expression2 | dinamic_cast <type-id> (expression) postfix-expression1 | static_cast <type-id> ( expression )postfix-expression1  | reinterpret_cast <type-id> ( expression )postfix-expression1  | const_cast <type-id> ( expression ) postfix-expression1 | typeid ( postfix-expression3
postfix-expression1: [ expression ] postfix-expression1 | ( postfix-expression4 | -- postfix-expression1 | ++ postfix-expression1 | -> postfix-expression5 | . postfix-expression6 | vazio
postfix-expression2: ) postfix-expression1 | expression-list )postfix-expression1 
postfix-expression3: expression ) postfix-expression1  | type-id ) postfix-expression1 
postfix-expression4: expression-list) postfix-expression1 | ) postfix-expression1 
postfix-expression5: pseudo-destructor-name postfix-expression1  | id-expression postfix-expression1  | template id expression postfix-expression1
*/

bool Parser::postfix_expression() {
	if (primary_expression()) {
		if (postfix_expression1()) {
			return true;
		} else {
			return false;
		}
	} else if (simple_type_specifier()) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (postfix_expression2()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (type_name_specifier()) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (postfix_expression2()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_DYNAMIC_CAST")
				|| compararTokenAtual("TOKEN_KEYWORD_STATIC_CAST")
				|| compararTokenAtual("TOKEN_KEYWORD_REINTERPRET_CAST")
				|| compararTokenAtual("TOKEN_KEYWORD_CONST_CAST")) {
		if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
			if (type_id()) {
				if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
					if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
						if (expression()) {
							if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
								if (postfix_expression1()) {
									return true;
								} else {
									return false;
								}
							} else {
								return false;
							}
						} else {
							return false;
						}
					} else {
						return false;
					}
				} else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (type_id()) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (postfix_expression3()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::postfix_expression1() {
	if (compararTokenAtual("LEFT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (expression()) {
			if (compararTokenAtual("RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
				if (postfix_expression1()) {
					return true;
				} else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (postfix_expression4()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_INCREMENT_OPERATOR")
				|| compararTokenAtual("TOKEN_DECREMENT_OPERATOR")) {
		if (postfix_expression1()) {
			return true;
		} else {
			return false;
		}				
	} else if (compararTokenAtual("TOKEN_MEMBER_ACCESS2_OPERATOR")
				|| compararTokenAtual("TOKEN_MEMBER_ACCESS_OPERATOR")) {
		if (postfix_expression5()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool Parser::postfix_expression2() {
	if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
		if (postfix_expression1()) {
			return true;
		} else {
			return false;
		}
	} else if (expression_list()) {
		if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
			if (postfix_expression1()) {
				return true;
			} else {
				return false;
			}
		} 
	}
}

bool Parser::postfix_expression3() {
	if (expression() || type_id()) {
		if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
			if (postfix_expression1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::postfix_expression4() {
	if (expression_list()) {
		if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
			if (postfix_expression1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
		if (postfix_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::postfix_expression5() {
	if (pseudo_destructor_name()) {
		if (postfix_expression1()) {
			return true;
		} else {
			return false;
		}
	} else if (id_expression()) {
		if (postfix_expression1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (id_expression()) {
			if (postfix_expression1()) {
				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}


/*
55- expression-list: assignment-expression expression-list1
    expression-list1: , assignment-expression expression-list1 | vazio
*/
bool Parser::expression_list() {
	if (assignment_expression()) {
		if (expression_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::expression_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (assignment_expression()) {
			if (expression_list1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
Regra antiga
pseudo-destructor-name: ::opt nested-name-specifieropt type-name | :: ~ type-name |::opt nested-name-specifier template template-id | :: ~ type-name |::opt nested-name-specifieropt ~ type-name

56- pseudo-destructor-name: :: pseudo-destructor-name1 | pseudo-desturctor-name1
    pseudo-desturctor-name1: nested-name-specifier pseudo-desturctor-name2 | pseudo-desturctor-name2
   pseudo-desturctor-name2: type-name :: ~type-name | ~ type-name | template template-id :: ~ type-name
*/

bool Parser::pseudo_destructor_name() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (pseudo_destructor_name1()) {
			return true;
		} else {
			return false;
		}
	} else if (pseudo_destructor_name1()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::pseudo_destructor_name1() {
	if (nested_name_specifier()) {
		if (pseudo_destructor_name2()) {
			return true;
		} else {
			return false;
		}
	} else if (pseudo_destructor_name2()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::pseudo_destructor_name2() {
	if (type_name()) {
		if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
			if (compararTokenAtual("TOKEN_BITWISE_NOT_OPERATOR")) {
				if (type_name()) {
					return true;
				} else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_BITWISE_NOT_OPERATOR")) {
		if (type_name()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (template_id()) {
			if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
				if (compararTokenAtual("TOKEN_BITWISE_NOT_OPERATOR")) {
					if (type_name()) {
						return true;
					} else {
						return false;
					}
				} else {
					return false;
				}
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
Regra antiga
unary-expression: postfix-expression | ++ cast-expression |-- cast-expression | unary-operator cast-expression | sizeof unary-expression |sizeof ( type-id ) | new-expression | delete-expression
57- unary-expression: postfix-expression | ++ cast-expression | -- cast-expression | unary-operator cast-expression |sizeof unary-expression1 | new-expression |delete-expression
unary-expression1: unary-expression | (type-id)
*/

bool Parser::unary_expression() {
	if (postfix_expression()) {
		return true;
	} else if (compararTokenAtual("TOKEN_INCREMENT_OPERATOR")
				|| compararTokenAtual("TOKEN_DECREMENT_OPERATOR")) {
		if (cast_expression()) {
			return true;
		} else {
			return false;
		}
	} else if (unary_operator()) {
		if (cast_expression()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_SIZEOF")) {
		if (unary_expression1()) {
			return true;
		} else {
			return false;
		}
	} else if (new_expression()) {
		return true;
	} else if (delete_expression()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::unary_expression1() {
	if (unary_expression()) {
		return true;
	} else if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (type_id()) {
			if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
58- unary-operator: * | & | + | - | ! | ~
*/

bool Parser::unary_operator() {
	if (compararTokenAtual("TOKEN_MULTIPLICATION_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_BITWISE_AND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_ADDITION_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_SUBTRACTION_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_NOT_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_BITWISE_NOT_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
new-expression: ::opt new new-placementopt new-type-id new-initializeropt | ::opt new new-placementopt ( type-id ) new-initializeropt

59- new-expression: :: new new-expression1 | new new-expression1
    new-expression1 : new-placement new-expression2 | new-expression2
    new-expression2: new-type-id new-expression3 | ( type-id ) new-expression3
    new-expression3: new-initializer | vazio
*/

bool Parser::new_expression() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (compararTokenAtual("TOKEN_KEYWORD_NEW")) {
			if (new_expression1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (new_expression1()) {
		if (compararTokenAtual("TOKEN_KEYWORD_NEW")) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::new_expression1() {
	if (new_placement()) {
		if (new_expression2()) {
			return true;
		} else {
			return false;
		}
	} else if (new_expression2()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::new_expression2() {
	if (new_type_id()) {
		if (new_expression3()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (type_id()) {
			if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
				if (new_expression3()) {
					return true;
				} else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::new_expression3() {
	if (new_initializer()) {
		return true;
	} else {
		return false;
	}
}

/*
60- new-placement: ( expression-list )
*/

bool Parser::new_placement() {
	if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (expression_list()) {
			if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS")) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
Regra antiga
new-type-id: type-specifier-seq new-declaratoropt

61- new-type-id: type-specifier-seq new-type-id1
    new-type-id1: new-declarator | vazio
*/

bool Parser::new_type_id() {
	if (type_specifier_seq()) {
		if (new_type_id1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::new_type_id1() {
	if (new_declarator()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
new-declarator: ptr-operator new-declaratoropt | direct-new-declarator

62- new-declarator: ptr-operator new-declarator1 | direct-new-declarator
    new-declarator1: new-declarator | vazio
*/
bool Parser::new_declarator() {
	if (ptr_operator()) {
		if (new_declarator1()) {
			return true;
		} else {
			return false;
		}
	} else if (direct_new_declarator()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::new_declarator1() {
	if (new_declarator()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
direct-new-declarator: [ expression ] | direct-new-declarator [ constant-expression ]
63- direct-new-declarator: [ expression ] direct-new-declarator1
    direct-new-declarator1: [ constant-expression ]direct-new-declarator1 | vazio
*/

bool Parser::direct_new_declarator() {
	if (compararTokenAtual("TOKEN_LEFT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (expression()) {
			if (compararTokenAtual("TOKEN_RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
				if (direct_new_declarator1()) {
					return true;
				} else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::direct_new_declarator1() {
	if (compararTokenAtual("TOKEN_LEFT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (constant_expression()) {
			if (compararTokenAtual("TOKEN_RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
				if (direct_new_declarator1()) {
					return true;
				} else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
Regra antiga
new-initializer: ( expression-listopt )

64- new-initializer: ( new-initializer1
    new-initializer1: expression-list ) | )
*/

bool Parser::new_initializer() {
	if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (new_initializer1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::new_initializer1() {
	if (expression_list()) {
		if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
delete-expression: ::opt delete cast-expression | ::opt delete [ ] cast-expression

65- delete-expression: :: delete-expression1 | delete-expression1
    delete-expression1: delete delete-expression2
    delete-expression2: cast-expression | [ ] cast-expression
*/

bool Parser::delete_expression() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (delete_expression1()) {
			return true;
		}
	} else if (delete_expression1()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::delete_expression1() {
	if (compararTokenAtual("TOKEN_KEYWORD_DELETE")) {
		if (delete_expression2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::delete_expression2() {
	if (cast_expression()) {
		return true;
	} else if (compararTokenAtual("TOKEN_LEFT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (compararTokenAtual("TOKEN_RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
			if (cast_expression()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
66- cast-expression: unary-operator | ( type-id ) cast-expression
*/

bool Parser::cast_expression() {
	if (unary_operator()) {
		return true;
	} else if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (type_id()) {
			if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
				if (cast_expression()) {
					return true;
				} else {
					return false;
				}
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
Regra antiga
pm-expression: cast-expression | pm-expression .* cast-expression |pm-expression ->* cast-expression

67- pm-expression: cast-expression pm-expression1
    pm-expression1: .* cast-expression pm-expression1 | ->* cast-expression pm-expression1 | vazio
*/

bool Parser::pm_expression() {
	if (cast_expression()) {
		if (pm_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::pm_expression1() {
	if (compararTokenAtual("TOKEN_ACCESS_POINTER_OPERATOR")
		|| compararTokenAtual("TOKEN_ACCESS_POINTER2_OPERATOR")) {
		if (cast_expression()) {
			if (pm_expression1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}	
	} else {
		return true;
	}
}

/*
Regra antiga
multiplicative-expression: pm-expression | multiplicative-expression * pm-expression | multiplicative-expression / pm-expression | multiplicative-expression % pm-expression

68- multiplicative-expression: pm-expression multiplicative-expression1
    multiplicative-expression1: * pm-expression multiplicative-expression1 | / pm-expression multiplicative-expression1 | % pm-expression multiplicative-expression1 | vazio
*/

bool Parser::multiplicative_expression() {
	if (pm_expression()) {
		if (multiplicative_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::multiplicative_expression1() {
	if ((compararTokenAtual("TOKEN_MULTIPLICATION_OPERATOR")
		|| compararTokenAtual("TOKEN_DIVISION_OPERATOR")
		|| compararTokenAtual("TOKEN_MODULO_OPERATOR")) {
		if (pm_expression()) {
			if (multiplicative_expression1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
Regra antiga
additive-expression: multiplicative-expression | additive-expression + multiplicative-expression | additive-expression - multiplicative-expression

69- additive-expression: multiplicative-expression additive-expression1
    additive-expression1: + multiplicative-expression additive-expression1 | - multiplicative-expression additive-expression1 | vazio
*/

bool Parser::additive_expression() {
	if (multiplicative_expression()) {
		if (additive_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::additive_expression1() {
	if ((compararTokenAtual("TOKEN_ADDITION_OPERATOR")
		|| compararTokenAtual("TOKEN_SUBTRACTION_OPERATOR")) {
		if (multiplicative_expression()) {
			if (additive_expression1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
Regra antiga
shift-expression: additive-expression | shift-expression << additive-expression | shift-expression >> additive-expression

70- shift-expression: additive-expression shift-expression1
    shift-expression1: << additive-expression shift-expression1 | >> additive-expression shift-expression1 | vazio
*/

bool Parser::shift_expression() {
	if (additive_expression()) {
		if (shift_expression()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::shift_expression1() {
	if ((compararTokenAtual("TOKEN_SHIFT_BITS_LEFT_OPERATOR")
		|| compararTokenAtual("TOKEN_SHIFT_BITS_RIGHT_OPERATOR")) {
		if (additive_expression()) {
			if (shift_expression1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*

*/

#endif

