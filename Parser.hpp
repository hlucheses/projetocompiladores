#include <string>
#include <cstdlib>


#ifndef INC_PARSER
#define INC_PARSER


#include "Prototipos.hpp"
#include "TabelaDeSimbolos.hpp"


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
			typedef_name();
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
};

#include "Gramatica.hpp"
#endif

