#include <iostream>
#include <string>

#ifndef INC_SIMBOLO
#define INC_SIMBOLO

using namespace std;

class Simbolo {
	public:
		Simbolo(string lex, int nLinha);
		void imprimir(void);
		string getLexema(void);
		int getNumeroLinha(void);
		void setLexema(string lex);
		void setNumeroLinha(int nLinha);
	private:
		string lexema;
		int numeroLinha;
};

Simbolo::Simbolo(string lex, int nLinha) {
	numeroLinha = nLinha;
	lexema = lex;
}

void Simbolo::imprimir(void) {
	cout << lexema << "\t" << numeroLinha;
}

string Simbolo::getLexema(void) {
	return lexema;
}

int Simbolo::getNumeroLinha(void) {
	return numeroLinha;
}

void Simbolo::setLexema(string lex) {
	lexema = lex;
}

void Simbolo::setNumeroLinha(int nLinha) {
	numeroLinha = nLinha;
}

#endif

