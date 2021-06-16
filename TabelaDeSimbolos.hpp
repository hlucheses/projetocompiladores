#include <iostream>
#include <list>
#include <string>
#include <utility>
#include <cstdio>

#ifndef INC_TABELA_DE_SIMBOLOS
#define INC_TABELA_DE_SIMBOLOS

#include "Prototipos.hpp"
#include "Simbolo.hpp"
#include "Token.hpp"
#include "Parser.hpp"

using namespace std;

class TabelaDeSimbolos {
	private:
		Parser *parser;
		// Atributos
		list< pair<Simbolo, string> > elementos;
	public:
		// Métodos
		TabelaDeSimbolos() {
			parser = (Parser *) malloc(sizeof(Parser));
			*parser = Parser();
		}
		
		void add(Simbolo simbolo) {
			pair<Simbolo, string> par(simbolo, Token::getToken(simbolo.getLexema()));
			elementos.push_back(par);
		}
		
		void imprimir(void) {
			cout << "LINHA\tLEXEMA\t\tTOKEN";
	
			for (list< pair<Simbolo, string> >::iterator i = elementos.begin();
					i != elementos.end(); ++i) {
						
				cout << endl << (*i).first.getNumeroLinha() << "\t";
				cout << (*i).first.getLexema() << "\t";
				cout << (*i).second;
			}
			
			cout << endl << endl;
		}
		
		void parse(void) {
			parser->parse(elementos);
		}
};

#endif
