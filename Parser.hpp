#include <string>
#include <cstdlib>


#ifndef INC_PARSER
#define INC_PARSER


#include "Prototipos.hpp"
#include "TabelaDeSimbolos.hpp"

/*TESTAR PRIMEIRO PURE SPECIFIER*/

using namespace std;


class Parser {
	private:
		int indexTabela;
		list< pair<Simbolo, string> >::iterator iterador;
	public:
		Parser() {
			indexTabela = 0;
		}
		
		int parse(list< pair<Simbolo, string> > elementos) {
			iterador = elementos.begin();
			program();
		}
		
		int program() {
			//typedef_name();
		}
		
		void getNextToken() {
			iterador++;
			if (iterador->first.getLexema() == "<<EOF>>") {
				cout << "Fim inesperado";
			}
		}
		
		bool compararTokenAtual(string str) {
			if (iterador->second == str) {
				getNextToken();
				return true;
			} else {
				return false;
			}
		}
		
		bool compararSimbolo(string str) {
			if (iterador->first.getLexema() == str) {
				getNextToken();
				return true;
			} else {
				return false;
			}
		}
		
		// Gramática
		bool typedef_name();
		bool namespace_name();
		bool class_name();
		bool class_name1();
		bool class_name2();
		bool enum_name();
		bool template_name();
		bool literal();
		bool boolean_literal();
		bool translation_unit();
		bool primary_expression();
		bool id_expression();
		bool unqualified_id();
		bool unqualified_id1();
		bool qualified_id();
		bool qualified_id1();
		bool qualified_id2();
		bool qualified_id3();
		bool nested_name_specifier();
		bool nested_name_specifier1();
		bool nested_name_specifier2();
		bool nested_name_specifier3();
		bool nested_name_specifier4();
		bool nested_name_specifier5();
		bool postfix_expression();
		bool postfix_expression1();
		bool postfix_expression2();
		bool postfix_expression3();
		bool postfix_expression4();
		bool postfix_expression5();
		bool expression_list();
		bool expression_list1();
		bool pseudo_destructor_name();
		bool pseudo_destructor_name1();
		bool pseudo_destructor_name2();
		bool unary_expression();
		bool unary_expression1();
		bool unary_operator();
		bool new_expression();
		bool new_expression1();
		bool new_expression2();
		bool new_expression3();
		bool new_placement();
		bool new_type_id();
		bool new_type_id1();
		bool new_declarator();
		bool new_declarator1();
		bool direct_new_declarator();
		bool direct_new_declarator1();
		bool new_initializer();
		bool new_initializer1();
		bool delete_expression();
		bool delete_expression1();
		bool delete_expression2();
		bool cast_expression();
		bool pm_expression();
		bool pm_expression1();
		bool multiplicative_expression();
		bool multiplicative_expression1();
		bool additive_expression();
		bool additive_expression1();
		bool shift_expression();
		bool shift_expression1();
		bool relational_expression();
		bool relational_expression1();
		bool equality_expression();
		bool equality_expression1();
		bool and_expression();
		bool and_expression1();
		bool exclusive_or_expression();
		bool exclusive_or_expression1();
		bool inclusive_or_expression();
		bool inclusive_or_expression1();
		bool logical_and_expression();
		bool logical_and_expression1();
		bool logical_or_expression();
		bool logical_or_expression1();
		bool conditional_expression();
		bool conditional_expression1();
		bool assignment_expression();
		bool assignment_operator();
		bool expression();
		bool expression1();
		bool constant_expression();
		bool statement();
		bool labeled_statement();
		bool expression_statement();
		bool compound_statement();
		bool compound_statement1();
		bool statement_seq();
		bool statement_seq1();
		bool selection_statement();
		bool selection_statement1();
		bool condition();
		bool iteration_statement();
		bool iteration_statement1();
		bool iteration_statement2();
		bool for_init_statement();
		bool jump_statement();
		bool jump_statement1();
		bool declaration_statement();
		bool declaration_seq();
		bool declaration_seq1();
		bool declaration();
		bool declaration1();
		bool declaration2();
		bool block_declaration();
		bool block_declaration1();
		bool simple_declaration();
		bool simple_declaration1();
		bool static_assert_declaration();
		bool decl_specifier();
		bool decl_specifier_seq();
		bool decl_specifier_seq1();
		bool storage_class_specifier();
		bool function_specifier();
		bool type_specifier();
		bool simple_type_specifier();
		bool simple_type_specifier1();
		bool simple_type_specifier2();
		bool type_name();
		bool type_name1();
		bool type_name2();
		bool elaborated_type_specifier();
		bool elaborated_type_specifier1();
		bool elaborated_type_specifier2();
		bool elaborated_type_specifier3();
		bool enum_specifier();
		bool enum_specifier1();
		bool enum_specifier2();
		bool enumerator_list();
		bool enumerator_list1();
		bool enumerator_definition();
		bool enumerator_definition1();
		bool enumerator();
		bool original_namespace_name();
		bool namespace_definition();
		bool namespace_definition1();
		bool original_namespace_definition();
		bool namespace_body();
		bool namespace_alias();
		bool namespace_alias_definition();
		bool qualified_namespace_specifier();
		bool qualified_namespace_specifier1();
		bool using_declaration();
		bool using_declaration1();
		bool using_declaration2();
		bool using_declaration3();
		bool using_directive();
		bool using_directive1();
		bool using_directive2();
		bool asm_definition();
		bool linkage_specification();
		bool linkage_specification1();
		bool linkage_specification2();
		bool init_declarator_list();
		bool init_declarator_list1();
		bool init_declarator();
		bool init_declarator1();
		bool declarator();
		bool direct_declarator();
		bool direct_declarator1();
		bool direct_declarator2();
		bool direct_declarator3();
		bool direct_declarator4();
		bool ptr_operator();
		bool ptr_operator1();
		bool cv_qualifier_seq();
		bool cv_qualifier_seq1();
		bool cv_qualifier();
		bool declarator_id();
		bool declarator_id1();
		bool type_id();
		bool type_id1();
		bool type_specifier_seq();
		bool type_specifier_seq1();
		bool abstract_declarator();
		bool abstract_declarator1();
		bool direct_abstract_declarator();
		bool direct_abstract_declarator0();
		bool direct_abstract_declarator1();
		bool direct_abstract_declarator2();
		bool direct_abstract_declarator3();
		bool direct_abstract_declarator4();
		bool parameter_declaration_clause();
		bool parameter_declaration_clause1();
		bool parameter_declaration_list();
		bool parameter_declaration_list1();
		bool parameter_declaration();
		bool parameter_declaration1();
		bool parameter_declaration2();
		bool parameter_declaration3();
		bool function_definition();
		bool function_definition1();
		bool function_body();
		bool initializer();
		bool initializer_clause();
		bool initializer_clause1();
		bool initializer_clause2();
		bool initializer_list();
		bool initializer_list1();
		bool class_specifier();
		bool class_specifier1();
		bool class_head();
		bool class_head1();
		bool class_head2();
		bool class_head3();
		bool class_head4();
		bool class_head5();
		bool class_key();
		bool member_specification();
		bool member_specification1();
		bool member_declaration();
		bool member_declaration1();
		bool member_declaration2();
		bool member_declaration3();
		bool member_declaration4();
		bool member_declarator_list();
		bool member_declarator_list1();
		bool member_declarator();
		bool member_declarator1();
		bool member_declarator2();
		bool pure_specifier();
		bool constant_initializer();
		bool base_clause();
		bool base_specifier_list();
		bool base_specifier_list1();
		bool base_specifier();
		bool base_specifier1();
		bool base_specifier2();
		bool base_specifier3();
		bool base_specifier4();
		bool base_specifier5();
		bool access_specifier();
		bool conversion_function_id();
		bool conversion_type_id();
		bool conversion_type_id1();
		bool conversion_declarator();
		bool conversion_declarator1();
		bool ctor_initializer();
		bool mem_initializer_list();
		bool mem_initializer_list1();
		bool mem_initializer();
		bool mem_initializer1();
		bool mem_initializer_id();
		bool mem_initializer_id1();
		bool mem_initializer_id2();
		bool operator_function_id();
		bool operator_function_id1();
		bool operator_function_id2();
		bool _operator();
		bool _operator1();
		bool template_declaration();
		bool template_parameter_list();
		bool template_parameter_list1();
		bool template_parameter();
		bool type_parameter();
		bool type_parameter1();
		bool type_parameter2();
		bool type_parameter3();
		bool type_parameter4();
		bool type_parameter5();
		bool type_parameter6();
		bool template_id();
		bool template_id1();
		bool template_argument_list();
		bool template_argument_list1();
		bool template_argument();
		bool typename_specifier();
		bool typename_specifier1();
		bool typename_specifier2();
		bool typename_specifier3();
		bool typename_specifier4();
		bool explicit_instantiation();
		bool explicit_specialization();
		bool try_block();
		bool function_try_block();
		bool function_try_block1();
		bool handler_seq();
		bool handler();
		bool exception_declaration();
		bool exception_declaration1();
		bool throw_expression();
		bool throw_expression1();
		bool exception_specification();
		bool exception_specification1();
		bool type_id_list();
		bool type_id_list1();
};

#include "Gramatica.hpp"
#endif

