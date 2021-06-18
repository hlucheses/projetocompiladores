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
		inserirErro("Esperava sinal de <", getLinha());
		return false;
	}
}

bool Parser::class_name2() {
	if (template_argument_list()) {
		if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
			return true;
		} else {
			inserirErro("Esperava >", getLinha());
			return false;
		}
	}else if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
		return true;
	} else {
		inserirErro("Esperava template-argument-list ou >", getLinha());
		return false;
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
				inserirErro("Esperava )", getLinha());
				return false;
			}
		} else {
			inserirErro("Esperava expression", getLinha());
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
			inserirErro("Esperava class-name", getLinha());
			return false;
		}
	} else if (template_id()) {
		return true;
	} else {
		inserirErro("Token inesperado após operator", getLinha());
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
	return false;
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
			inserirErro("Esperava ::", getLinha());
			return false;
		}
	} else if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OEPERATOR")) {
		if (nested_name_specifier2()) {
			return true;
		} else {
			return false;
		}
	} else {
		inserirErro("Esperava ::", getLinha());
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
		} else {
			inserirErro("Esperava identificador", getLinha());
			return false;
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
				inserirErro("Esperava ::", getLinha());
				return false;
			}
		} else {
			inserirErro("Esperava >", getLinha());
			return false;
		}
	} else if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
		if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
			return true;
		} else {
			inserirErro("Esperava ::", getLinha());
			return false;
		}
	} else {
		inserirErro("Esperava >", getLinha());
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
	} else if (typename_specifier()) {
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
	} else if (compararTokenAtual("TOKEN_KEYWORD_TYPEID")) {
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
				return true;
		}
	} else {
		return false;
	}
}

bool Parser::expression_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (assignment_expression()) {
			if (expression_list1()) {
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
	if (compararTokenAtual("TOKEN_MULTIPLICATION_OPERATOR")
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
	if (compararTokenAtual("TOKEN_ADDITION_OPERATOR")
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
	if (compararTokenAtual("TOKEN_SHIFT_BITS_LEFT_OPERATOR")
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
Regra antiga
relational-expression: shift-expression | relational-expression < shift-expression | relational-expression > shift-expression | relational-expression <= shift-expression | relational-expression >= shift-expression

71- relational-expression: shift-expression relational-expression1
    relational-expression1: < relational-expression2 shift-expression relational-expression1 | > relational-expression3  | vazio
    relational-expression2: shift-expression relational-expression1 | = shift-expression relational-expression1
*/

bool Parser::relational_expression() {
	if (shift_expression()) {
		if (relational_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::relational_expression1() {
	if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")
		|| compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")
		|| compararTokenAtual("TOKEN_LESS_THAN_OR_EQUAL_TO_OPERATOR")
		|| compararTokenAtual("TOKEN_GREATER_THAN_OR_EQUAL_TO_OPERATOR")) {
		if (shift_expression()) {
			if (relational_expression1()) {
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
equality-expression: relational-expression | equality-expression == relational-expression | equality-expression != relational-expression

72- equality-expression: relational-expression equality-expression1
    equality-expression1: == relational-expression equality-expression1 | != relational-expression equality-expression1 | vazio
*/

bool Parser::equality_expression() {
	if (relational_expression()) {
		if (equality_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::equality_expression1() {
	if (compararTokenAtual("TOKEN_EQUAL_TO_OPERATOR")
		|| compararTokenAtual("TOKEN_NOT_EQUAL_TO_OPERATOR")) {
		if (relational_expression()) {
			if (equality_expression1()) {
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
and-expression:equality-expression | and-expression & equality-expression

73- and-expression: equality and-expression1
    and-expression1: & equality-expression and-expression1 | vazio
*/

bool Parser::and_expression() {
	if (equality_expression()) {
		if (and_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::and_expression1() {
	if (compararTokenAtual("TOKEN_BITWISE_AND_OPERATOR")) {
		if (equality_expression()) {
			if (and_expression1()) {
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
exclusive-or-expression: and-expression | exclusive-or-expression ^ and-expression

74- exclusive-or-expression: and-expression exclusive-or-expression1
    exclusive-or-expression1: ^ and-expression exclusive-or-expression1 | vazio
*/

bool Parser::exclusive_or_expression() {
	if (and_expression()) {
		if (exclusive_or_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::exclusive_or_expression1() {
	if (compararTokenAtual("TOKEN_BITWISE_XOR_OPERATOR")) {
		if (and_expression()) {
			if (exclusive_or_expression1()) {
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
inclusive-or-expression: exclusive-or-expression | inclusive-or-expression | exclusive-or-expression

75- inclusive-or-expression: exclusive-or-expression inclusive-or-expression1
    inclusive-or-expression1: | exclusive-or-expression inclusive-or-expression1 | vazio
*/

bool Parser::inclusive_or_expression() {
	if (exclusive_or_expression()) {
		if (inclusive_or_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::inclusive_or_expression1() {
	if (compararTokenAtual("TOKEN_BITWISE_OR_OPERATOR")) {
		if (exclusive_or_expression()) {
			if (inclusive_or_expression1()) {
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
logical-and-expression: inclusive-or-expression | logical-and-expression && inclusive-or-expression

76- logical-and-expression: inclusive-or-expression logical-and-expression1
    logical-and-expression1: && inclusive-or-expression logical-and-expression1 | vazio
*/

bool Parser::logical_and_expression() {
	if (inclusive_or_expression()) {
		if (logical_and_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::logical_and_expression1() {
	if (compararTokenAtual("TOKEN_AND_OPERATOR")) {
		if (inclusive_or_expression()) {
			if (logical_and_expression1()) {
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
logical-or-expression:logical-and-expression | logical-or-expression || logical-and-expression

77- logical-or-expression: logical-and-expression logical-or-expression1
    logical-or-expression1: || logical-and-expression logical-or-expression1 | vazio
*/

bool Parser::logical_or_expression() {
	if (logical_and_expression()) {
		if (logical_or_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::logical_or_expression1() {
	if (compararTokenAtual("TOKEN_OR_OPERATOR")) {
		if (logical_and_expression()) {
			if (logical_or_expression1()) {
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
conditional-expression:logical-or-expression | logical-or-expression ? expression : assignment-expression

78- conditional-expression: logical-or-expression conditional-expression1
    conditional-expression1: ? expression : assignment-expressio | vazio
*/

bool Parser::conditional_expression() {
	if (logical_or_expression()) {
		if (conditional_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::conditional_expression1() {
	if (compararTokenAtual("TOKEN_CONDITIONAL_TERNARY_OPERATOR")) {
		if (expression()) {
			if (compararTokenAtual("TOKEN_COLON_OPERATOR")) {
				if (assignment_operator()) {
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
79- assignment-expression: conditional-expression | logical-or-expression assignment-operator assignment-expression | throw-expression
*/

bool Parser::assignment_expression() {
	if (conditional_expression()) {
		return true;
	} else if (logical_or_expression()) {
		if (assignment_operator()) {
			if (assignment_expression()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (throw_expression()) {
		return true;
	} else {
		return false;
	}
}

/*
80- assignment-operator: one of
= *= /= %= += -= >>= <<= &= ^= |=
*/

bool Parser::assignment_operator() {
	if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_MULTIPLICATION_COMPOUND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_DIVISION_COMPOUND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_MODULO_COMPOUND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_ADDITION_COMPOUND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_SUBTRACTION_COMPOUND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_SHIFT_BITS_RIGHT_COMPOUND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_SHIFT_BITS_LEFT_COMPOUND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_BITWISE_AND_COMPOUND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_BITWISE_XOR_COMPOUND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_BITWISE_OR_COMPOUND_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
expression: assignment-expression | expression , assignment-expression

81- expression: assignment-expression expression1
    expression1: , assignment-expressio expression1 | vazio
*/

bool Parser::expression() {
	/*if (assignment_expression()) {
		if (expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}*/
	return false;
}

bool Parser::expression1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (assignment_expression()) {
			if (expression1()) {
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
82- constant-expression: conditional-expression
*/
bool Parser::constant_expression() {
	if (conditional_expression()) {
		return true;
	} else {
		return false;
	}
}

/*
83- statement: labeled-statement | expression-statement |compound-statement | selection-statement |iteration-statement | jump-statement | declaration-statement | try-block
*/
bool Parser::statement() {
	if (labeled_statement()) {
		return true;
	} else if (expression_statement()) {
		return true;
	} else if (compound_statement()) {
		return true;
	} else if (selection_statement()) {
		return true;
	} else if (iteration_statement()) {
		return true;
	} else if (jump_statement()) {
		return true;
	} else if (declaration_statement()) {
		return true;
	} else if (try_block()) {
		return true;
	} else {
		return false;
	}
}

/*
84- labeled-statement: identifier : statement | case constant-expression : statement | default : statement
*/
bool Parser::labeled_statement() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (compararTokenAtual("TOKEN_COLON_OPERATOR")) {
			if (statement()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_CASE")) {
		if (constant_expression()) {
			if (compararTokenAtual("TOKEN_COLON_OPERATOR")) {
				if (statement()) {
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
	} else if (compararTokenAtual("TOKEN_KEYWORD_DEFAULT")) {
		if (compararTokenAtual("TOKEN_COLON_OPERATOR")) {
			if (statement()) {
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
expression-statement: expressionopt ;

85- expression-statement: expression ; | ;
*/

bool Parser::expression_statement() {
	if (expression()) {
		if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
		return true;
	} else {
		return false;
	} 
}

/*
Regra antiga
compound-statement: { statement-seqopt }

86- compound-statement: { compound-statement1
    compound-statement1: } | statement-seq }
*/

bool Parser::compound_statement() {
	if (compararTokenAtual("TOKEN_OPENING_BRACE_OPERATOR")) {
		if (compound_statement1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::compound_statement1() {
	if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
		return true;
	} else if (statement_seq()) {
		if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
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
statement-seq:statement | statement-seq statement

87- statement-seq: statement statement-seq1
    statement-seq1: statement statement-seq1 | vazio
*/

bool Parser::statement_seq() {
	if (statement()) {
		if (statement_seq1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::statement_seq1() {
	if (statement()) {
		if (statement_seq1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
Regra antiga
selection-statement: if ( condition ) statement | if ( condition ) statement else statement | switch ( condition ) statement

88- selection-statement: if ( condition ) statement selection-statement1 | switch (condition) statement
    selection-statement1: else statement | vazio
*/

bool Parser::selection_statement() {
	if (compararTokenAtual("TOKEN_KEYWORD_IF")) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (condition()) {
				if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
					if (statement()) {
						if (selection_statement1()) {
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
	} else if (compararTokenAtual("TOKEN_KEYWORD_SWITCH")) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (condition()) {
				if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
					if (statement()) {
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
}

bool Parser::selection_statement1() {
	if (compararTokenAtual("TOKEN_KEYWORD_ELSE")) {
		if (statement()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
89- condition: expression | type-specifier-seq declarator = assignment-expression
*/

bool Parser::condition() {
	if (expression()) {
		return true;
	} else if (type_specifier_seq()) {
		if (declarator()) {
			if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
				if (assignment_expression()) {
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
iteration-statement: while ( condition ) statement | do statement while ( expression ) ; | for ( for-init-statement conditionopt ; expressionopt ) statement

90- iteration-statement: while ( condition ) statement | do statement while ( expression ) ; | for ( for-init-statement iteration-statement1
    iteration-statement1: condition ; iteration-statement2 | ; iteration-statement2
    iteration-statement2: ) statement | expression ) statement
*/

bool Parser::iteration_statement() {
	if (compararTokenAtual("TOKEN_KEYWORD_WHILE")) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (condition()) {
				if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
					if (statement()) {
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
	} else if (compararTokenAtual("TOKEN_KEYWORD_DO")) {
		if (statement()) {
			if (compararTokenAtual("TOKEN_KEYWORD_WHILE")) {
				if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
					if (expression()) {
						if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
							if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
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
	} else if (compararTokenAtual("TOKEN_KEYWORD_FOR")) {
		if  (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (for_init_statement()) {
				if (iteration_statement1()) {
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

bool Parser::iteration_statement1() {
	if (condition()) {
		if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
			if (iteration_statement2()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
		if (iteration_statement2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::iteration_statement2() {
	if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
		if (statement()) {
			return true;
		} else {
			return false;
		}
	} else if (expression()) {
		if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
			if (statement()) {
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
91- for-init-statement: expression-statement | simple-declaration
*/

bool Parser::for_init_statement() {
	if (expression_statement()) {
		return true;
	} else if (simple_declaration()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
jump-statement: break ; | continue ; | return expressionopt ; | goto identifier ;

92- jump-statement: break ; | continue ; | goto identifier ; | return jump-statement1
    jump-statement1: ; | expression ;
*/

bool Parser::jump_statement() {
	if (compararTokenAtual("TOKEN_KEYWORD_BREAK")) {
		if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_CONTINUE")) {
		if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_GOTO")) {
		if (compararTokenAtual("TOKEN_IDENTIFIER")) {
			if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_RETURN")) {
		if (jump_statement1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::jump_statement1() {
	if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
		return true;
	} else if (expression()) {
		if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
93- declaration-statement: block-declaration
*/

bool Parser::declaration_statement() {
	if (block_declaration()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
declaration-seq: declaration | declaration-seq declaration

94- declaration-seq: declaration declaration-seq1
    declaration-seq1 : declaration declaration-seq1 | vazio
*/

bool Parser::declaration_seq() {
	/*if (declaration()) {
		if (declaration_seq1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}*/
	return false;
}

bool Parser::declaration_seq1() {
	if (declaration()) {
		if (declaration_seq1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
95- Regra antiga - ambiguidade indireta
declaration: block-declaration | function-definition | template-declaration | explicit-instantiation | explicit-specialization | linkage-specification | namespace-definition

declaration: decl-specifier-seq declaration1 | declaration1 |template declaration2| declaration2 |linkage-specification |namespace-definition
declaration1: block-declaration | function-definition
declaration2: explicit-instantiation | explicit-specialization | < template-parameter-list > declaration
*/

bool Parser::declaration() {
	if (decl_specifier_seq()) {
		if (declaration1()) {
			return true;
		} else {
			return false;
		}
	} else if (declaration1()) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (declaration2()) {
			return true;
		} else {
			return false;
		}
	} else if (declaration2()) {
		return true;
	} else if (linkage_specification()) {
		return true;
	} else if (namespace_definition()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::declaration1() {
	if (block_declaration()) {
		return true;
	} else if (function_definition()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::declaration2() {
	if (explicit_instantiation()) {
		return true;
	} else if (explicit_specialization()) {
		return true;
	} else if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
		if (template_parameter_list()) {
			if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
				if (declaration()) {
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
block-declaration: simple-declaration | asm-definition | namespace-alias-definition | using-declaration | using-directive | static_assert-declaration

97- block-declaration: simple-declaration | asm-definition | namespace-alias-definition |using block-declaration1 | static_assert-declaration
    block-declaration1: using-declaration | using-directive
*/

bool Parser::block_declaration() {
	if (simple_declaration()) {
		return true;
	} else if (asm_definition()) {
		return true;
	} else if (namespace_alias_definition()) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_USING")) {
		if (block_declaration1()) {
			return true;
		} else {
			return false;
		}
	} else if (static_assert_declaration()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::block_declaration1() {
	if (using_declaration()) {
		return true;
	} else if (using_directive()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
simple-declaration: decl-specifier-seqopt init-declarator-listopt ;

98- simple-declaration: decl-specifier-seq simple-declaration1 | simple-declaration1
    simple-declaration1: ; | init-declarator-list ; 
*/

bool Parser::simple_declaration() {
	if (decl_specifier_seq()) {
		if (simple_declaration1()) {
			return true;
		} else {
			return false;
		}
	} else if (simple_declaration1()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::simple_declaration1() {
	if (init_declarator_list()) {
		if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
99- static_assert-declaration: static_assert ( constant-expression , string-literal ) ;
*/

bool Parser::static_assert_declaration() {
	if (compararTokenAtual("TOKEN_KEYWORD_STATIC_ASSERT")) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (constant_expression()) {
				if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
					if (compararTokenAtual("TOKEN_STRING_LITERAL")) {
						if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
							if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
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
}

/*
100- decl-specifier: storage-class-specifier | type-specifier | function-specifier | friend | typedef
*/

bool Parser::decl_specifier() {
	if (storage_class_specifier()) {
		return true;
	} else if (type_specifier()) {
		return true;
	} /*else if (function_specifier()) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_FRIEND")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_TYPEDEF")) {
		return true;
	} */ else {
		return false;
	}
}

/*
Regra antiga
decl-specifier-seq: decl-specifier-seqopt decl-specifier

101- decl-specifier-seq: decl-specifier decl-specifier-seq1
     decl-specifier-seq1: decl-specifier dec-specifier-seq1 | vazio
*/

bool Parser::decl_specifier_seq() {
	if (decl_specifier()) {
		if (decl_specifier_seq1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::decl_specifier_seq1() {
	if (decl_specifier()) {
		if (decl_specifier_seq1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
102- storage-class-specifier:auto | register | static | extern | mutable
*/

bool Parser::storage_class_specifier() {
	if (compararTokenAtual("TOKEN_KEYWORD_AUTO")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_REGISTER")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_STATIC")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_EXTERN")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_MUTABLE")) {
		return true;
	} else {
		return false;
	}
}

/*
103- function-specifier: inline | virtual | explicit
*/

bool Parser::function_specifier() {
	if (compararTokenAtual("TOKEN_KEYWORD_INLINE")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_VIRTUAL")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_EXPLICIT")) {
		return true;
	} else {
		return false;
	}
}

/*
105- type-specifier: simple-type-specifier | class-specifier | enum-specifier | elaborated-type-specifier | typename-specifier | cv-qualifier
*/

bool Parser::type_specifier() {
	if (simple_type_specifier()) {
		return true;
	} else if (class_specifier()) {
		return true;
	} else if (enum_specifier()) {
		return true;
	} else if (elaborated_type_specifier()) {
		return true;
	} else if (typename_specifier()) {
		return true;
	} else if (cv_qualifier()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
simple-type-specifier: ::opt nested-name-specifieropt type-name | ::opt nested-name-specifier template template-id | char | wchar_t | bool | short | int | long | signed | unsigned | float | double | void

106- simple-type-specifier: :: simple-type-specifier1 | nested-name-specifier simple-type-specifier2
     simple-type-specifier1: type-name | nested-name-specifier simple-type-specifier2
     simple-type-specifier2: type-name | template template-id
*/

bool Parser::simple_type_specifier() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (simple_type_specifier1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_CHAR")
				|| compararTokenAtual("TOKEN_KEYWORD_WCHAR_T")
				|| compararTokenAtual("TOKEN_KEYWORD_BOOL")
				|| compararTokenAtual("TOKEN_KEYWORD_SHORT")
				|| compararTokenAtual("TOKEN_KEYWORD_INT")
				|| compararTokenAtual("TOKEN_KEYWORD_SIGNED")
				|| compararTokenAtual("TOKEN_KEYWORD_UNSIGNED")
				|| compararTokenAtual("TOKEN_KEYWORD_FLOAT")
				|| compararTokenAtual("TOKEN_KEYWORD_DOUBLE")
				|| compararTokenAtual("TOKEN_KEYWORD_VOID")) {
		return true;
	} else if (nested_name_specifier()) {
		if (simple_type_specifier2()) {
			return true;
		} else {
			return false;
		}
	}  else {
		return false;
	}
}

bool Parser::simple_type_specifier1() {
	if (type_name()) {
		return true;
	} else if (nested_name_specifier()) {
		if (simple_type_specifier2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::simple_type_specifier2() {
	if (type_name()) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (template_id()) {
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
type-name: class-name | enum-name | typedef-name

107- type-name: identifier type-name1
     type-name1: < type-name2 | vazio
     type-name2: template-argument-list > |  >
*/

bool Parser::type_name() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (type_name1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::type_name1() {
	if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
		if (type_name2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool Parser::type_name2() {
	if (template_argument_list()) {
		if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
elaborated-type-specifier: class-key ::opt nested-name-specifieropt identifier | class-key ::opt nested-name-specifieropt templateopt template-id | enum ::opt nested-name-specifieropt identifier

108- elaborated-type-specifier: class-key elaborated-type-specifier1 | enum elaborated-type-specifier1
     elaborated-type-specifier1: :: elaborated-type-specifier2 | elaborated-type-specifier2
     elaborated-type-specifier2: nested-name-specifier elaborated-type-specifier3 | elaborated-type-specifier3
     elaborated-type-specifier3: identifier | template template-id | template-id
*/

bool Parser::elaborated_type_specifier() {
	if (class_key()) {
		if (elaborated_type_specifier1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_ENUM")) {
		if (elaborated_type_specifier1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool Parser::elaborated_type_specifier1() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (elaborated_type_specifier2()) {
			return true;
		} else {
			return false;
		}
	} else if (elaborated_type_specifier2()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::elaborated_type_specifier2() {
	if (nested_name_specifier()) {
		if (elaborated_type_specifier3()) {
			return true;
		} else {
			return false;
		}
	} else if (elaborated_type_specifier3()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::elaborated_type_specifier3() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (template_id()) {
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
enum-specifier: enum identifieropt{ enumerator-listopt}

110- enum-specifier: enum enum-specifier1
     enum-specifier1: identifier { enum-specifier2 | { enum-specifier2
     enum-specifier2: enumerator-list } | }
*/

bool Parser::enum_specifier() {
	if (compararTokenAtual("TOKEN_KEYWORD_ENUM")) {
		if (enum_specifier1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::enum_specifier1() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (compararTokenAtual("TOKEN_OPENING_BRACE_OPERATOR")) {
			if (enum_specifier2()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_OPENING_BRACE_OPERATOR")) {
		if (enum_specifier2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::enum_specifier2() {
	if (enumerator_list()) {
		if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
enumerator-list: enumerator-definition | enumerator-list , enumerator-definition

111- enumerator-list: enumerator-definition enumerator-list1
     enumerator-list1: , enumerator-definition enumerator-list1 | vazio
*/

bool Parser::enumerator_list() {
	if (enumerator_definition()) {
		if (enumerator_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::enumerator_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (enumerator_definition()) {
			if (enumerator_list1()) {
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
enumerator-definition: enumerator | enumerator = constant-expression

112- enumerator-definition: enumerator enumerator-definition1
     enumerator-definition1: = constant-expression | vazio
*/

bool Parser::enumerator_definition() {
	if (enumerator()) {
		if (enumerator_definition1()){
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::enumerator_definition1() {
	if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
		if (constant_expression()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
113- enumerator: identifier
*/

bool Parser::enumerator() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else {
		return false;
	}
}

/*
115- original-namespace-name: identifier
*/

bool Parser::original_namespace_name() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
namespace-definition: named-namespace-definition | unnamed-namespace-definition

116- namespace-definition: namespace namespace-definition1
namespace-definition1: identifier { namespace-body } | original-namespace-name { namespace-body }| { namespace-body }
*/

bool Parser::namespace_definition() {
	if (compararTokenAtual("TOKEN_KEYWORD_NAMESPACE")) {
		if (namespace_definition1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::namespace_definition1() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (compararTokenAtual("TOKEN_OPENING_BRACE_OPERATOR")) {
			if (namespace_body()) {
				if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
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
	} else if (original_namespace_name()) {
		if (compararTokenAtual("TOKEN_OPENING_BRACE_OPERATOR")) {
			if (namespace_body()) {
				if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
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
	} else if (compararTokenAtual("TOKEN_OPENING_BRACE_OPERATOR")) {
		if (namespace_body()) {
			if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
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
118- namespace-body: declaration-seqopt | vazio
*/

bool Parser::namespace_body() {
	if (declaration_seq()) {
		return true;
	} else {
		return true;
	}
}

/*
119- namespace-alias: identifier
*/

bool Parser::namespace_alias() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		return true;
	} else {
		return false;
	}
}

/*
120- namespace-alias-definition: namespace identifier = qualified-namespace-specifier ;
*/

bool Parser::namespace_alias_definition() {
	if (compararTokenAtual("TOKEN_KEYWORD_NAMESPACE")) {
		if (compararTokenAtual("TOKEN_IDENTIFIER")) {
			if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
				if (qualified_namespace_specifier()) {
					if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
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
}


/*
Regra antiga
qualified-namespace-specifier: ::opt nested-name-specifieropt namespace-name

121- qualified-namespace-specifier: :: qualified-namespace-specifier1 | qualified-namespace-specifier1
qualified-namespace-specifier1: nested-name-specifieropt namespace-name | namespace-name
*/

bool Parser::qualified_namespace_specifier() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (qualified_namespace_specifier1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::qualified_namespace_specifier1() {
	if (nested_name_specifier()) {
		if (namespace_name()) {
			return true;
		} else {
			return false;
		}
	} else if (namespace_name()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
using-declaration: using typenameopt ::opt nested-name-specifier unqualified-id ; | using :: unqualified-id ;


122- using-declaration: using using-declaration1
     using-declaration1: typename using-declaration2 | using-declaration2 | :: using-declaration3
     using-declaration2:  :: nested-name-specifier unqualified-id ;
 | nested-name-specifier unqualified-id ;
     using-declaration3: unqualified-id ;
*/

bool Parser::using_declaration() {
	if (compararTokenAtual("TOKEN_KEYWORD_USING")) {
		if (using_declaration1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::using_declaration1() {
	if (compararTokenAtual("TOKEN_KEYWORD_TYPENAME")) {
		if (using_declaration2()) {
			return true;
		} else {
			return false;
		}
	} else if (using_declaration2()) {
		return true;
	} else if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (using_declaration3()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::using_declaration2() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (nested_name_specifier()) {
			if (unqualified_id()) {
				if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
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
	} if (nested_name_specifier()) {
		if (unqualified_id()) {
			if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
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

bool Parser::using_declaration3() {
	if (unqualified_id()) {
		if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
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
using-directive: using namespace ::opt nested-name-specifieropt namespace-name ;

123- using-directive: using namespace using-directive1
     using-directive1: using-directive2 | :: using-directive2
     using-directive2: nested-name-specifier namespace-name ; | namespace-name ;
*/

bool Parser::using_directive() {
	if (compararTokenAtual("TOKEN_KEYWORD_USING")) {
		if (compararTokenAtual("TOKEN_KEYWORD_NAMESPACE")) {
			if (using_directive1()) {
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

bool Parser::using_directive1() {
	if (using_directive2()) {
		return true;
	} else if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (using_directive2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::using_directive2() {
	if (nested_name_specifier()) {
		if (namespace_name()) {
			if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
			return true;
			} else {
				return false;
			}
		}
	} else if (namespace_name()) {
		if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}


/*
124- asm-definition: asm ( string-literal ) ;
*/

bool Parser::asm_definition() {
	if (compararTokenAtual("TOKEN_KEYWORD_ASM")) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (compararTokenAtual("TOKEN_STRING_LITERAL")) {
				if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
					if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
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
}

/*
Regra antiga
linkage-specification:extern string-literal { declaration-seqopt } | extern string-literal declaration

125- linkage-specification: extern string-literal linkage-specification1
     linkage-specification1: declaration | { linkage-specification2
     linkage-specification2: declaration-seq } | }
*/

bool Parser::linkage_specification() {
	if (compararTokenAtual("TOKEN_KEYWORD_EXTERN")) {
		if (compararTokenAtual("TOKEN_STRING_LITERAL")) {
			if (linkage_specification1()) {
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

bool Parser::linkage_specification1() {
	if (declaration()) {
		return true;
	} else if (compararTokenAtual("TOKEN_OPENING_BRACE_OPERATOR")) {
		if (linkage_specification2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::linkage_specification2() {
	if (declaration_seq()) {
		if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
init-declarator-list: init-declarator | init-declarator-list , init-declarator

126- init-declarator-list: init-declarator init-declarator-list1
     init-declarator-list1: , init-declarator init-declarator-list1 | vazio
*/

bool Parser::init_declarator_list() {
	if (init_declarator()) {
		if (init_declarator_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::init_declarator_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (init_declarator()) {
			if (init_declarator_list1()) {
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
init-declarator: declarator initializeropt

127- init-declarator:declarator init-declarator1
     init-declarator1: initializer | vazio
*/

bool Parser::init_declarator() {
	if (declarator()) {
		if (init_declarator1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::init_declarator1() {
	if (initializer()) {
		return true;
	} else {
		return true;
	}
}

/*
128- declarator: direct-declarator | ptr-operator declarator
*/

bool Parser::declarator() {
	if (direct_declarator()) {
		return true;
	} else if (ptr_operator()) {
		if (declarator()) {
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
direct-declarator: declarator-id | direct-declarator ( parameter-declaration-clause ) cv-qualifier-seqopt exception-specificationopt | direct-declarator [ constant-expressionopt ] | ( declarator )

129- direct-declarator: declarator-id direct-declarator1 | ( declarator ) direct-declarator1
     direct-declarator1: ( parameter-declaration-clause )direct-declarator2  | [ direct-declarator4 | vazio
     direct-declarator2: cv-qualifier-seq direct-declarator3 | direct-declarator3
     direct-declarator3: exception-specification direct-declarator1 | direct-declarator1
     direct-declarator4: constant-expression ] direct-declarator1 | ] direct-declarator1
*/

bool Parser::direct_declarator() {
	if (declarator_id()) {
		if (direct_declarator1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (declarator()) {
			if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
				if (direct_declarator1()) {
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

bool Parser::direct_declarator1() {
	if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (parameter_declaration_clause()) {
			if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
				if (direct_declarator2()) {
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
	} else if (compararTokenAtual("TOKEN_LEFT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (direct_declarator4()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool Parser::direct_declarator2() {
	if (cv_qualifier_seq()) {
		if (direct_declarator3()) {
			return true;
		} else {
			return false;
		}
	} else if (direct_declarator3()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::direct_declarator3() {
	if (exception_specification()) {
		if (direct_declarator1()) {
			return true;
		} else {
			return false;
		}
	} else if (direct_declarator1()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::direct_declarator4() {
	if (constant_expression()) {
		if (compararTokenAtual("TOKEN_RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
			if (direct_declarator1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (direct_declarator1()) {
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
ptr-operator: * cv-qualifier-seqopt | & | ::opt nested-name-specifier * cv-qualifier-seqopt

130- ptr-operator:  * ptr-operator1 | & | :: nested-name-specifier * ptr-operator1 | nested-name-specifier * ptr-operator1
     ptr-operator1: cv-qualifier-seq | vazio
*/

bool Parser::ptr_operator() {
	if (compararTokenAtual("TOKEN_MULTIPLICATION_OPERATOR")) {
		if (ptr_operator1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_BITWISE_AND_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (nested_name_specifier()) {
			if (compararTokenAtual("TOKEN_MULTIPLICATION_OPERATOR")) {
				if (ptr_operator1()) {
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
	} else if (nested_name_specifier()) {
		if (compararTokenAtual("TOKEN_MULTIPLICATION_OPERATOR")) {
			if (ptr_operator1()) {
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

bool Parser::ptr_operator1() {
	if (cv_qualifier_seq()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
cv-qualifier-seq: cv-qualifier cv-qualifier-seqopt

131- cv-qualifier-seq: cv-qualifier cv-qualifier-seq1
     cv-qualifier-seq1: cv-qualifier-seq | vazio
*/

bool Parser::cv_qualifier_seq() {
	if (cv_qualifier()) {
		if (cv_qualifier_seq1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::cv_qualifier_seq1() {
	if (cv_qualifier_seq()) {
		return true;
	} else {
		return false;
	}
}

/*
132-cv-qualifier: const | volatile
*/

bool Parser::cv_qualifier() {
	if (compararTokenAtual("TOKEN_KEYWORD_CONST")
		|| compararTokenAtual("TOKEN_KEYWORD_VOLATILE")) {
		return true;	
	} else {
		return false;
	}
}

/*
Regra antiga
declarator-id: id-expression | ::opt nested-name-specifieropt class-name

133- declarator-id: id-expression | :: declarator-id1 | nested-name-specifier class-name | class-name
     declarator-id1: nested-name-specifier class-name | class-name
*/

bool Parser::declarator_id() {
	if (id_expression()) {
		return true;
	} else if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (declarator_id1()) {
			return true;
		} else {
			return false;
		}
	} else if (nested_name_specifier()) {
		if (class_name()) {
			return true;
		} else {
			return false;
		}
	} else if (class_name()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::declarator_id1() {
	if (nested_name_specifier()) {
		if (class_name()) {
			return true;
		} else {
			return false;
		}
	} else if (class_name()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
type-id: type-specifier-seq abstract-declaratoropt 

134- type-id: type-specifier-seq  type-id1
     type-id1: abstract-declarator | vazio
*/

bool Parser::type_id() {
	if (type_specifier_seq()) {
		if (type_id1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::type_id1() {
	if (abstract_declarator()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
type-specifier-seq: type-specifier type-specifier-seqopt

135- type-specifier-seq:type-specifier type-specifier-seq1
     type-specifier-seq1: type-specifier-seq | vazio
*/

bool Parser::type_specifier_seq() {
	if (type_specifier()) {
		if (type_specifier_seq1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::type_specifier_seq1() {
	if (type_specifier_seq()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
abstract-declarator: ptr-operator abstract-declaratoropt | direct-abstract-declarator

136- abstract-declarator: ptr-operator abstract-declarator1 | direct-abstract-declarator
     abstract-declarator1: abstract-declarator | vazio
*/

bool Parser::abstract_declarator() {
	if (ptr_operator()) {
		if (abstract_declarator1()) {
			return true;
		} else {
			return false;
		}
	} else if (direct_abstract_declarator()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::abstract_declarator1() {
	if (abstract_declarator()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
direct-abstract-declarator: direct-abstract-declaratoropt | ( parameter-declaration-clause ) cv-qualifier-seqopt exception-specificationopt | direct-abstract-declaratoropt[ constant-expressionopt ] | ( abstract-declarator )


137- direct-abstract-declarator: (direct-abstract-declarator0  | direct-abstract-declarator1 | vazio
    direct-abstract-declarator0: abstract-declarator ) direct-abstract-declarator1 |  parameter-declaration-clause ) direct-abstract-declarator2
	direct-abstract-declarator1: [ direct-abstract-declarator4
    direct-abstract-declarator2: cv-qualifier-seq direct-abstract-declarator3 | exception-specification direct-abstract-declarator1| direct-abstract-declarator1
    direct-abstract-declarator3: exception-specification direct-abstract-declarator1 | direct-abstract-declarator1
    direct-abstract-declarator4: constant-expression ] direct-abstract-declarator1 | ] direct-abstract-declarator1
*/

bool Parser::direct_abstract_declarator() {
	if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (direct_abstract_declarator0()) {
			return true;
		} else {
			return false;
		}
	} else if (direct_abstract_declarator1()) {
		return true;
	} else {
		return true;
	}
}

bool Parser::direct_abstract_declarator0() {
	if (abstract_declarator()) {
		if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
			if (direct_abstract_declarator1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (parameter_declaration_clause()) {
		if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
			if (direct_abstract_declarator2()) {
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

bool Parser::direct_abstract_declarator1() {
	if (compararTokenAtual("TOKEN_LEFT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (direct_abstract_declarator4()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::direct_abstract_declarator2() {
	if (cv_qualifier_seq()) {
		if (direct_abstract_declarator3()) {
			return true;
		} else {
			return false;
		}
	} else if (exception_specification()) {
		if (direct_abstract_declarator1()) {
			return true;
		} else {
			return false;
		}
	} else if (direct_abstract_declarator1()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::direct_abstract_declarator3() {
	if (exception_specification()) {
		if (direct_abstract_declarator1()) {
			return true;
		} else {
			return false;
		}
	} else if (direct_abstract_declarator1()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::direct_abstract_declarator4() {
	if (constant_expression()) {
		if (compararTokenAtual("TOKEN_RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
			if (direct_abstract_declarator1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (direct_abstract_declarator1()) {
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
parameter-declaration-clause: parameter-declaration-listopt ...opt | parameter-declaration-list , ...


138- parameter-declaration-clause: parameter-declaration-list parameter-declaration-clause1 | ... | vazio
     parameter-declaration-clause1:  , ... | ... | vazio
*/

bool Parser::parameter_declaration_clause() {
	if (parameter_declaration_list()) {
		if (parameter_declaration_clause1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
		if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
			if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
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

bool Parser::parameter_declaration_clause1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
			if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
				if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
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
	} else if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
		if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
			if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
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
parameter-declaration-list: parameter-declaration | parameter-declaration-list , parameter-declaration

139- parameter-declaration-list: parameter-declaration parameter-declaration-list1
     parameter-declaration-list1: , parameter-declaration parameter-declaration-list1 | vazio
*/

bool Parser::parameter_declaration_list() {
	if (parameter_declaration()) {
		if (parameter_declaration_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::parameter_declaration_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (parameter_declaration()) {
			if (parameter_declaration_list1()) {
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
parameter-declaration: decl-specifier-seq declarator | decl-specifier-seq declarator = assignment-expression | decl-specifier-seq abstract-declaratoropt | decl-specifier-seq abstract-declaratoropt = assignment-expression

140- parameter-declaration: decl-specifier-seq parameter-declaration1
     parameter-declaration1: declarator   parameter-declaration2 | abstract-declarator  parameter-declaration3 |  parameter-declaration3 | vazio
     parameter-declaration2: = assignment-expression | vazio
      parameter-declaration3: = assignment-expression
*/

bool Parser::parameter_declaration() {
	if (decl_specifier_seq()) {
		if (parameter_declaration1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::parameter_declaration1() {
	if (declarator()) {
		if (parameter_declaration2()) {
			return true;
		} else {
			return false;
		}
	} else if (abstract_declarator()) {
		if (parameter_declaration3()) {
			return true;
		} else {
			return false;
		}
	} else if (parameter_declaration3()) {
		return true;
	} else {
		return true;
	}
}

bool Parser::parameter_declaration2() {
	if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
		if (assignment_expression()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool Parser::parameter_declaration3() {
	if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
		if (assignment_expression()) {
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

function-definition: decl-specifier-seqopt declarator ctor-initializeropt function-body | decl-specifier-seqopt declarator function-try-block

141- function-definition: decl-specifier-seq declarator function-definition1 | declarator function-definition1
     function-definition1: function-try-block | ctor-initializer function-body | function-body
*/

bool Parser::function_definition() {
	if (decl_specifier_seq()) {
		if (declarator()) {
			if (function_definition1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (declarator()) {
		if (function_definition1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::function_definition1() {
	if (function_try_block()) {
		return true;
	} else if (ctor_initializer()) {
		if (function_body()) {
			return true;
		} else {
			return false;
		}
	} else if (function_body()) {
		return true;
	} else {
		return false;
	}
}

/*
142- function-body: compound-statement
*/

bool Parser::function_body() {
	if (compound_statement()) {
		return true;
	} else {
		return false;
	}
}

/*
143- initializer: = initializer-clause | ( expression-list )
*/

bool Parser::initializer() {
	if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
		if (initializer_clause()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (expression_list()) {
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
Regra antiga
initializer-clause: assignment-expression | { initializer-list ,opt } | { }

144- initializer-clause: assignment-expression | { initializer-clause1
     initializer-clause1: initializer-list initializer-clause2 | }
     initializer-clause2: , } | } 
*/

bool Parser::initializer_clause() {
	if (assignment_expression()) {
		return true;
	} else if (compararTokenAtual("TOKEN_OPENING_BRACE_OPERATOR")) {
		if (initializer_clause1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::initializer_clause1() {
	if (initializer_list()) {
		if (initializer_clause2()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

bool Parser::initializer_clause2() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
initializer-list:
initializer-clause
initializer-list , initializer-clause

145-initializer-list: initializer-clause initializer-list1
    initializer-list1: , initializer-clause | vazio
*/

bool Parser::initializer_list() {
	if (initializer_clause()) {
		if (initializer_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::initializer_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (initializer_clause()) {
			if (initializer_list1()) {
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
class-specifier: class-head { member-specificationopt }

147- class-specifier: class-head { class-specifier1
     class-specifier1: member-specification } | }
*/

bool Parser::class_specifier() {
	if (class_head()) {
		if (compararTokenAtual("TOKEN_OPENING_BRACE_OPERATOR")) {
			if (class_specifier1()) {
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

bool Parser::class_specifier1() {
	if (member_specification()) {
		if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_CLOSING_BRACE_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
class-head: class-key identifieropt base-clauseopt | class-key nested-name-specifier identifier base-clauseopt | class-key nested-name-specifieropt template-id base-clauseopt

148- class-head: class-key  class-head1
     class-head1: identifier class-head2 | class-head3 
     class-head2: base-clause | vazio | nested-name-specifier1 class-head4 | < class-head5
     class-head3: base-clause | vazio
     class-head4: base-clause | vazio | < class-head5 
     class-head5: template-argument-list > class-head3 | > class-head3
*/

bool Parser::class_head() {
	if (class_key()) {
		if (class_head1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::class_head1() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (class_head2()) {
			return true;
		} else {
			return false;
		}
	} else if (class_head3()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::class_head2() {
	if (base_clause()) {
		return true;
	} else if (nested_name_specifier1()) {
		if (class_head4()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
		if (class_head5()) {
			return true;
		} else {
			return false;
		}
	} else if (class_head4()) {
		return true;
	} else {
		return true;
	}
}

bool Parser::class_head3() {
	if (base_clause()) {
		return true;
	} else {
		return false;
	} 
}

bool Parser::class_head4() {
	if (base_clause()) {
		return true;
	} else if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
		if (class_head5()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool Parser::class_head5() {
	if (template_argument_list()) {
		if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
			if (class_head3()) {
				return true;
			} else {
				return false;	
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
		if (class_head3()) {
			return true;
		} else {
			return false;	
		}
	} else {
		return false;
	}
}

/*
149- class-key: class | struct | union
*/

bool Parser::class_key() {
	if (compararTokenAtual("TOKEN_KEYWORD_CLASS")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_STRUCT")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_UNION")) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
member-specification: member-declaration member-specificationopt | access-specifier : member-specificationopt

150- member-specification:  member-declaration member-specification1 | access-specifier : member-specification1 
member-specificartion1: member-specification | vazio
*/

bool Parser::member_specification() {
	if (member_declaration()) {
		if (member_specification1()) {
			return true;
		} else {
			return false;
		}
	} else if (access_specifier()) {
		if (compararTokenAtual("TOKEN_COLON_OPERATOR")) {
			if (member_specification1()) {
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

bool Parser::member_specification1() {
	if (member_specification()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
member-declaration: decl-specifier-seqopt member-declarator-listopt ; | function-definition ;opt | ::opt nested-name-specifier templateopt | unqualified-id ; |using-declaration | static_assert-declaration | template-declaration

151- member-declaration: decl-specifier-seq member-declaration4 | member-declaration1 | :: nested-name-specifier member-declaration3 | nested-name-specifier member-declaration3 | using-declaration | static_assert_declaration | template declaration

member-declaration4: member-declaration1 | declarator function1 member-declaration2 
member-declaration1: member-declarator-list ; | ;
member-declaration2: ; | vazio
member-declaration3: template | vazio
*/

bool Parser::member_declaration() {
	if (decl_specifier_seq()) {
		if (member_declaration4()) {
			return true;
		} else {
			return false;
		}
	} else if (member_declaration1()) {
		return true;
	} else if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (nested_name_specifier()) {
			if (member_declaration3()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (nested_name_specifier()) {
		if (member_declaration3()) {
			return true;
		} else {
			return false;
		}
	} else if (using_declaration()) {
		return true;
	} else if (static_assert_declaration()) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (declaration()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::member_declaration4() {
	if (member_declaration1()) {
		return true;
	} else if (declarator()) {
		if (function_definition1()) {
			if (member_declaration2()) {
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

bool Parser::member_declaration1() {
	if (member_declarator_list()) {
		if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

bool Parser::member_declaration2() {
	if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
		return true;
	} else {
		return true;
	}
}

bool Parser::member_declaration3() {
	if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		return true;
	} else {
		return true;
	} 
}

/*
Regra antiga
member-declarator-list: member-declarator | member-declarator-list , member-declarator

152- member-declarator-list: member-declarator  member-declarator-list1
     member-declarator-list1: , member-declarator member-declarator-list1 | vazio
*/

bool Parser::member_declarator_list() {
	if (member_declarator()) {
		if (member_declarator_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::member_declarator_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (member_declarator()) {
			if (member_declarator_list1()) {
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
member-declarator: declarator pure-specifieropt | declarator constant-initializeropt | identifieropt : constant-expression

153- member-declarator: declarator member-declarator1 | identifier member-declarator2 | member-declarator2
     member-declarator1: pure-specifier | constant-initializer | vazio
     member-declarator2:  : constant-expression
*/

bool Parser::member_declarator() {
	if (declarator()) {
		if (member_declarator1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (member_declarator2()) {
			return true;
		} else {
			return false;
		}
	} else if (member_declarator2()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::member_declarator1() {
	if (pure_specifier()) {
		return true;
	} else if (constant_initializer()) {
		return true;
	} else {
		return true;
	}
}

bool Parser::member_declarator2() {
	if (compararTokenAtual("TOKEN_COLON_OPERATOR")) {
		if (constant_expression()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
154- pure-specifier: = 0
*/

bool Parser::pure_specifier() {
	 if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
	 	if (compararSimbolo("0")) {
	 		return true;
		 } else {
		 	return false;
		 }
	 } else {
	 	return false;
	 }
}

/*
155- constant-initializer: = constant-expression
*/

bool Parser::constant_initializer() {
	if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
	 	if (constant_expression()) {
	 		return true;
		 } else {
		 	return false;
		 }
	 } else {
	 	return false;
	 }
}

/*
156- base-clause: : base-specifier-list
*/

bool Parser::base_clause() {
	if (compararTokenAtual("TOKEN_COLON_OPERATOR")) {
		if (base_specifier_list()) {
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
base-specifier-list: base-specifier | base-specifier-list , base-specifier

157- base-specifier-list: base-specifier base-specifier-list1
     base-specifier-list1: , base-specifier base-specifier-list1 | vazio
*/

bool Parser::base_specifier_list() {
	if (base_specifier()) {
		if (base_specifier_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::base_specifier_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (base_specifier()) {
			if (base_specifier_list1()) {
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
base-specifier: ::opt nested-name-specifieropt class-name | virtual access-specifieropt ::opt nested-name-specifieropt class-name | access-specifier virtualopt ::opt nested-name-specifieropt class-name

158- base-specifier: :: base-specifier1 | base-specifier1 | virtual base-specifier2 | access-specifier base-specifier5
     base-specifier1: nested-name-specifier class-name | class-name
     base-specifier2: access-specifier base-specifier3 | base-specifier3
     base-specifier3:  :: base-specifier4 | base-specifier4
     base-specifier4: nested-name-specifier class-name | class-name
     base-specifier5: virtual base-specifier6 | base-specifier6
     base-specifier6: :: base-specifier4 | base-specifier4
*/

bool Parser::base_specifier() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (base_specifier1()) {
			return true;
		} else {
			return false;
		}
	} else if (base_specifier1()) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_VIRTUAL")) {
		if (base_specifier2()) {
			return true;
		} else {
			return false;
		}
	} else if (access_specifier()) {
		if (base_specifier5()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::base_specifier1() {
	if (nested_name_specifier()) {
		if (class_name()) {
			return true;
		} else {
			return false;
		}
	} else if (class_name()) {
		return true;
	}
}

bool Parser::base_specifier2() {
	if (access_specifier()) {
		if (base_specifier3()) {
			return true;
		} else {
			return false;
		}
	} else if (base_specifier3()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::base_specifier3() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (base_specifier4()) {
			return true;
		} else {
			return false;
		}
	} else if (base_specifier4()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::base_specifier4() {
	if (nested_name_specifier()) {
		if (class_name()) {
			return true;
		} else {
			return false;
		}
	} else if (class_name()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::base_specifier5() {
	if (compararTokenAtual("TOKEN_KEYWORD_VIRTUAL")) {
		if (base_specifier3()) {
			return true;
		} else {
			return false;
		}
	} else if (base_specifier3()) {
		return true;
	} else {
		return false;
	}
}

/*
159- access-specifier: private | protected | public
*/

bool Parser::access_specifier() {
	if (compararTokenAtual("TOKEN_KEYWORD_PRIVATE")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_PROTECTED")) {
		return true;
	} else if (compararTokenAtual("TOKEN_KEYWORD_PUBLIC")) {
		return true;
	} else {
		return false;
	}
}

/*
160- conversion-function-id: operator conversion-type-id
*/

bool Parser::conversion_function_id() {
	/*if (compararTokenAtual("TOKEN_KEYWORD_OPERATOR")) {
		if (conversion_type_id()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}*/
	return false;
}

/*
Regra antiga
conversion-type-id: type-specifier-seq conversion-declaratoropt

161- conversion-type-id: type-specifier-seq  conversion-type-id1
     conversion-type-id1: conversion-declarator | vazio
*/

bool Parser::conversion_type_id() {
	if (type_specifier_seq()) {
		if (conversion_type_id1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::conversion_type_id1() {
	if (conversion_declarator()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
conversion-declarator: ptr-operator conversion-declaratoropt
162- conversion-declarator: ptr-operator conversion-declarator1
     conversion-declarator1: conversion-declarator | vazio
*/

bool Parser::conversion_declarator() {
	if (ptr_operator()) {
		if (conversion_declarator1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::conversion_declarator1() {
	if (conversion_declarator()) {
		return true;
	} else {
		return true;
	}
} 

/*
163- ctor-initializer: : mem-initializer-list
*/

bool Parser::ctor_initializer() {
	if (compararTokenAtual("TOKEN_COLON_OPERATOR")) {
		if (mem_initializer_list()) {
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
mem-initializer-list: mem-initializer | mem-initializer , mem-initializer-list

164- mem-initializer-list: mem-initializer mem-initializer-list1
     mem-initializer-list1: , mem-initializer mem-initializer-list1 | vazio
*/

bool Parser::mem_initializer_list() {
	if (mem_initializer()) {
		if (mem_initializer_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::mem_initializer_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (mem_initializer()) {
			if (mem_initializer_list1()) {
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
mem-initializer: mem-initializer-id ( expression-listopt )

165- mem-initializer: mem-initializer-id ( mem-initializer1
     mem-initializer1: expression-list ) | ) 
*/

bool Parser::mem_initializer() {
	if (mem_initializer_id()) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (mem_initializer1()) {
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

bool Parser::mem_initializer1() {
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
mem-initializer-id: ::opt nested-name-specifieropt class-name | identifier

166- mem-initializer-id: identifier mem-initializer-id2 | :: mem-initializer-id1 | class-name
     mem-initializer-id1: nested-name-specifier class-name | class-name
     mem-initializer-id2: nested-name-specifier1 class-name | vazio
*/

bool Parser::mem_initializer_id() {
	if (compararTokenAtual("TOKEN_IDENTIFIFER")) {
		if (mem_initializer_id2()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (mem_initializer_id1()) {
			return true;
		} else {
			return false;
		}
	} else if (class_name()) {
		return true;
	} else {
		return false;
	}
} 

bool Parser::mem_initializer_id1() {
	if (nested_name_specifier()) {
		if (class_name()) {
			return true;
		} else {
			return false;
		}
	} else if (class_name()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::mem_initializer_id2() {
	if (nested_name_specifier()) {
		if (class_name()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
Regra antiga
operator-function-id: operator operator |operator operator < template-argument-listopt >

167- operator-function-id: operator operator operator-function-id1
     operator-function-id1: < operator-function-id2 | vazio
     operator-function-id2: template-argument-list > | > 
*/

bool Parser::operator_function_id() {
	/*if (compararTokenAtual("TOKEN_KEYWORD_OPERATOR")) {
		if (_operator()) {
			if (operator_function_id()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}*/ return false;
}

bool Parser::operator_function_id1() {
	if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
		if (operator_function_id2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool Parser::operator_function_id2() {
	if (template_argument_list()) {
		if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
		return true;
	} else {
		return false;
	}
}

/*
operator: one of
new delete new[] delete[]
+ - * / % ^ & | ~
! = < > += -= *= /= %=
^= &= |= << >> >>= <<= == !=
<= >= && || ++ -- , ->* ->
() []
*/

bool Parser::_operator() {
	if (compararTokenAtual("TOKEN_KEYWORD_NEW")
		|| compararTokenAtual("TOKEN_KEYWORD_DELETE")) {
		if (_operator1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_ADDITION_OPERATOR")
		|| compararTokenAtual("TOKEN_SUBTRACTION_OPERATOR")
		|| compararTokenAtual("TOKEN_MULTIPLICATION_OPERATOR")
		|| compararTokenAtual("TOKEN_DIVISION_OPERATOR")
		|| compararTokenAtual("TOKEN_MODULO_OPERATOR")
		|| compararTokenAtual("TOKEN_BITWISE_XOR_OPERATOR")
		|| compararTokenAtual("TOKEN_BITWISE_AND_OPERATOR")
		|| compararTokenAtual("TOKEN_BITWISE_OR_OPERATOR")
		|| compararTokenAtual("TOKEN_BITWISE_NOT_OPERATOR")
		|| compararTokenAtual("TOKEN_NOT_OPERATOR")
		|| compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")
		|| compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")
		|| compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")
		|| compararTokenAtual("TOKEN_ADDITION_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_SUBTRACTION_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_MULTIPLICATION_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_DIVISION_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_MODULO_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_BITWISE_XOR_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_BITWISE_AND_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_BITWISE_OR_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_SHIFT_BITS_LEFT_OPERATOR")
		|| compararTokenAtual("TOKEN_SHIFT_BITS_RIGHT_OPERATOR")
		|| compararTokenAtual("TOKEN_SHIFT_BITS_LEFT_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_SHIFT_BITS_RIGHT_COMPOUND_OPERATOR")
		|| compararTokenAtual("TOKEN_EQUAL_TO_OPERATOR")
		|| compararTokenAtual("TOKEN_NOT_EQUAL_TO_OPERATOR")
		|| compararTokenAtual("TOKEN_LESS_THAN_OR_EQUAL_TO_OPERATOR")
		|| compararTokenAtual("TOKEN_GREATER_THAN_OR_EQUAL_TO_OPERATOR")
		|| compararTokenAtual("TOKEN_AND_OPERATOR")
		|| compararTokenAtual("TOKEN_OR_OPERATOR")
		|| compararTokenAtual("TOKEN_INCREMENT_OPERATOR")
		|| compararTokenAtual("TOKEN_DECREMENT_OPERATOR")
		|| compararTokenAtual("TOKEN_COMMA_OPERATOR")
		|| compararTokenAtual("TOKEN_ACCESS_POINTER2_OPERATOR")
		|| compararTokenAtual("TOKEN_MEMBER_ACCESS2_OPERATOR")) {
		return true;
	} else if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
		if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_LEFT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (compararTokenAtual("TOKEN_RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::_operator1() {
	if (compararTokenAtual("TOKEN_LEFT_SQUARE_PARENTHESIS_OPERATOR")) {
		if (compararTokenAtual("TOKEN_RIGHT_SQUARE_PARENTHESIS_OPERATOR")) {
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
template-declaration: exportopt template < template-parameter-list > declaration

168-  template-declaration: export template < template-parameter-list> | template < template-parameter-list>
*/

bool Parser::template_declaration() {
	if (compararTokenAtual("TOKEN_KEYWORD_EXPORT")) {
		if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
			if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
				if (template_parameter_list()) {
					if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
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
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
			if (template_parameter_list()) {
				if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
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
template-parameter-list:template-parameter | template-parameter-list , template-parameter

169- template-parameter-list: template-parameter template-parameter-list1 
     template-parameter-list1: , template-parameter template-parameter-list1 | vazio
*/

bool Parser::template_parameter_list() {
	if (template_parameter()) {
		if (template_parameter_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::template_parameter_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (template_parameter()) {
			if (template_parameter_list1()) {
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
170- template-parameter: type-parameter | parameter-declaration
*/

bool Parser::template_parameter() {
	if (type_parameter()) {
		return true;
	} else if (parameter_declaration()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
type-parameter: class identifieropt | class identifieropt = type-id | typename identifieropt | typename identifieropt = type-id | template <template-parameter-list > class identifieropt | template < template-parameter-list > class identifieropt = id-expression

171- type-parameter: class type-parameter1 | typename type-parameter3 | template type-parameter4
     type-parameter1: identifier type-parameter2 | type-parameter2 | vazio
     type-parameter2: = type-id | vazio
     type-parameter3: identifier type-parameter2 | type-parameter2 
     type-parameter4: < template-parameter-list > class type-parameter5
     type-parameter5: identifier type-parameter6 | vazio | = id-expression
     type-parameter6: = id-expression | vazio
*/

bool Parser::type_parameter() {
	if (compararTokenAtual("TOKEN_KEYWORD_CLASS")) {
		if (type_parameter1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_TYPENAME")) {
		if (type_parameter3()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (type_parameter4()) {
			return true;
		} else {
			return false;
		}
	}
}

bool Parser::type_parameter1() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (type_parameter2()) {
			return true;
		} else {
			return false;
		}
	} else if (type_parameter2()) {
		return true;
	} else {
		return true;
	}
}

bool Parser::type_parameter2() {
	if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
		if (type_id()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool Parser::type_parameter3() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (type_parameter2()) {
			return true;
		} else {
			return false;
		}
	} if (type_parameter2()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::type_parameter4() {
	if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
		if (template_parameter_list()) {
			if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
				if (compararTokenAtual("TOKEN_KEYWORD_CLASS")) {
					if (type_parameter5()) {
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
}

bool Parser::type_parameter5() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (type_parameter6()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
		if (id_expression()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

bool Parser::type_parameter6() {
	if (compararTokenAtual("TOKEN_ASSIGNMENT_OPERATOR")) {
		if (id_expression()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
Regra antiga
template-id: template-name < template-argument-listopt >

172- template-id: template-name < template-id1
     template-id1: template-argument-list > | >
*/

bool Parser::template_id() {
	/*if (template_name()) {
		if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
			if (template_id1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else {
		return false;
	}*/
}

bool Parser::template_id1() {
	if (template_argument_list()) {
		if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
			if (template_id1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
		if (template_id1()) {
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
template-argument-list: template-argument | template-argument-list , template-argument

174- template-argument-list: template-argument  template-argument-list1
      template-argument-list1:  template-argument  template-argument-list1 | vazio
*/

bool Parser::template_argument_list() {
	/*if (template_argument()) {
		if (template_argument_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}*/
	return false;
}

bool Parser::template_argument_list1() {
	if (template_argument()) {
		if (template_argument_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
175- template-argument: assignment-expression | type-id | id-expression
*/
bool Parser::template_argument() {
	if (assignment_expression()) {
		return true;
	} else if (type_id()) {
		return true;
	} else if (id_expression()) {
		return true;
	} else {
		return false;
	}
}

/*
Regra antiga
typename-specifier: typename ::opt nested-name-specifier identifier | typename ::opt nested-name-specifier templateopt template-id

176-  typename-specifier: typename typename-specifier1
      typename-specifier1: :: nested-name-specifier typename-specifier2 | nested-name-specifier typename-specifier2
      typename-specifier2: identifier typename-specifier3 | template typename-specifier4
      typename-specifier3: template-id1 | vazio
      typename-specifier4: template-id
*/

bool Parser::typename_specifier() {
	if (compararTokenAtual("TOKEN_KEYWORD_TYPENAME")) {
		if (typename_specifier1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::typename_specifier1() {
	if (compararTokenAtual("TOKEN_SCOPE_QUALIFIER_OPERATOR")) {
		if (nested_name_specifier()) {
			if (typename_specifier2()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (nested_name_specifier()) {
		if (typename_specifier2()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::typename_specifier2() {
	if (compararTokenAtual("TOKEN_IDENTIFIER")) {
		if (typename_specifier3()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (typename_specifier4()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::typename_specifier3() {
	if (template_id1()) {
		return true;
	} else {
		return true;
	}
}

bool Parser::typename_specifier4() {
	if (template_id1()) {
		return true;
	} else {
		return false;
	} 
}

/*
177- explicit-instantiation: template declaration
*/

bool Parser::explicit_instantiation() {
	if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (declaration()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
178- explicit-specialization: template < > declaration
*/

bool Parser::explicit_specialization() {
	if (compararTokenAtual("TOKEN_KEYWORD_TEMPLATE")) {
		if (compararTokenAtual("TOKEN_LESS_THAN_OPERATOR")) {
			if (compararTokenAtual("TOKEN_GREATER_THAN_OPERATOR")) {
				if (declaration()) {
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
179- try-block: try compound-statement handler-seq
*/
bool Parser::try_block() {
	if (compararTokenAtual("TOKEN_KEYWORD_TRY")) {
		if (compound_statement()) {
			if (handler_seq()) {
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
function-try-block:
try ctor-initializeropt function-body handler-seq

180- function-try-block: try function-try-block1
     function-try-block1: ctor-initializer function-body handler-seq | function-body handler-seq
*/

bool Parser::function_try_block() {
	if (compararTokenAtual("TOKEN_KEYWORD_TRY")) {
		if (function_try_block1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::function_try_block1() {
	if (ctor_initializer()) {
		if (function_body()) {
			if (handler_seq()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (function_body()) {
		if (handler_seq()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

/*
181- handler-seq: handler handler-seq | vazio
*/

bool Parser::handler_seq() {
	if (handler()) {
		if (handler_seq()) {
			return true;
		} else {
			return false;
		}
	} else {
		return true;
	}
}

/*
182- handler: catch ( exception-declaration ) compound-statement
*/

bool Parser::handler() {
	if (compararTokenAtual("TOKEN_KEYWORD_CATCH")) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (exception_declaration()) {
				if (compararTokenAtual("TOKEN_RIGHT_PARENTHESIS_OPERATOR")) {
					if (compound_statement()) {
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
}


/*
Regra antiga
exception-declaration: type-specifier-seq declarator | type-specifier-seq abstract-declarator | type-specifier-seq | ...

183- exception-declaration: type-specifier-seq exception-declaration1 | ...
     exception-declaration1: declarator | abstract-declarator | vazio
*/

bool Parser::exception_declaration() {
	if (type_specifier_seq()) {
		if (exception_declaration1()) {
			return true;
		} else {
			return false;
		}
	} else if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
		if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
			if (compararTokenAtual("TOKEN_MEMBER_ACESS_OPERATOR")) {
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

bool Parser::exception_declaration1() {
	if (declarator()) {
		return true;
	} else if (abstract_declarator()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
throw-expression: throw assignment-expressionopt

184- throw-expression: throw throw-expression1
     throw-expression1: assignment-expression | vazio
*/

bool Parser::throw_expression() {
	if (compararTokenAtual("TOKEN_KEYWORD_THROW")) {
		if (throw_expression1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::throw_expression1() {
	if (assignment_expression()) {
		return true;
	} else {
		return true;
	}
}

/*
Regra antiga
exception-specification: throw ( type-id-listopt )

185- exception-specification: throw ( exception-specification1
     exception-specification1: type-id-list ) | )
*/

bool Parser::exception_specification() {
	if (compararTokenAtual("TOKEN_KEYWORD_THROW")) {
		if (compararTokenAtual("TOKEN_LEFT_PARENTHESIS_OPERATOR")) {
			if (exception_specification1()) {
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

bool Parser::exception_specification1() {
	if (type_id_list()) {
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
type-id-list: type-id | type-id-list , type-id

186- type-id-list: type-id type-id-list1
     type-id-list1: , type-id type-id-list1 | type-id-list1
*/

bool Parser::type_id_list() {
	if (type_id()) {
		if (type_id_list1()) {
			return true;
		} else {
			return false;
		}
	} else {
		return false;
	}
}

bool Parser::type_id_list1() {
	if (compararTokenAtual("TOKEN_COMMA_OPERATOR")) {
		if (type_id()) {
			if (type_id_list1()) {
				return true;
			} else {
				return false;
			}
		} else {
			return false;
		}
	} else if (type_id_list1()) {
		return true;
	} else {
		return false;
	}
}

bool Parser::gambiarra() {
	if (simple_type_specifier()) {
		if (compararTokenAtual("TOKEN_IDENTIFIER")) {
			if (compararTokenAtual("TOKEN_SEMI_COLON_OPERATOR")) {
				return true;
			} else {
				inserirErro("Esperava ; !", iterador->first.getNumeroLinha());
			}
		} else {
			inserirErro("Esperava identificador!", iterador->first.getNumeroLinha());
		}
	} else {
		inserirErro("Esperava tipo de dados!", iterador->first.getNumeroLinha());
	}
}

#endif

