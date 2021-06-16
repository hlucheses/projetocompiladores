#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <iostream>
#include <fstream>

#include "TabelaDeSimbolos.hpp"

using namespace std;

TabelaDeSimbolos analex(string nomeDoArquivo) {
	
	char caractere = 0;
	char carTemp = 0;
	string strSimbolo = "";
	int linha = 1;
	
	ifstream arquivo(/*nomeDoArquivo*/"programa.txt");
	
	if (!arquivo.is_open()) {
		cerr << "Impossível abrir o ficheiro - '" << nomeDoArquivo << "'"
			 << endl;
		exit(EXIT_FAILURE);
	}
	
	TabelaDeSimbolos tabela;
	int posLinha = 0;
	
	
	while (arquivo.peek() != EOF) {
		
		arquivo.get(caractere);
		
		// Caso seja um identificador ou palavra reservada
		if 	(isalpha(caractere) || caractere == '_') {
			do {
				
				strSimbolo += caractere;
				carTemp = arquivo.peek();
				
				if (!isalnum(carTemp) && carTemp != '_') {
					break;
				}
				
				arquivo.get(caractere);
				
			} while (1);
		} else if (isspace(caractere) && caractere != '\n') {
			do {
				strSimbolo = "  ";
				carTemp = arquivo.peek();
				
				if (!isspace(carTemp) || carTemp == '\n') {
					break;
				}
				
				arquivo.get(caractere);
			} while(1);
		} else if (caractere == '\n') {
			strSimbolo = " ";
		} else if ((caractere >= '!' && caractere <= '/' && caractere != '$')
						|| (caractere >= ':' && caractere <= '?')
						|| (caractere == '[' || caractere == ']'
						|| caractere == '^') 
						|| (caractere >= '{' && caractere <= '~')) {
			strSimbolo = caractere;
			
			if (strSimbolo == "<" || strSimbolo == ">") {
				if (arquivo.peek() == strSimbolo[0]
					|| arquivo.peek() == '=') {
					arquivo.get(caractere);
					strSimbolo += caractere;
				}
			}
			
			if (strSimbolo == "!") {
				if (arquivo.peek() == '=') {
					arquivo.get(caractere);
					strSimbolo += caractere;
				}
			}
			
			if (strSimbolo == "+" || strSimbolo == "-" || strSimbolo == "="
				|| strSimbolo == "|" || strSimbolo == "&" || strSimbolo == ":"
				|| strSimbolo == "/") {
				if (arquivo.peek() == strSimbolo[0]) {
					arquivo.get(caractere);
					strSimbolo += caractere;
				}
			}
			
			if (strSimbolo == "-") {
				if (arquivo.peek() == '>') {
					arquivo.get(caractere);
					strSimbolo += caractere;
				}
			}
			
			if (strSimbolo == "." || strSimbolo == "->") {
				if (arquivo.peek() == '*') {
					arquivo.get(caractere);
					strSimbolo += caractere;
				}
			}
			
			if (isBitwiseOrArithmetic(strSimbolo)) {
				if (arquivo.peek() == '=') {
					arquivo.get(caractere);
					strSimbolo += caractere;
				}
			}
			
			if (strSimbolo == "#" && posLinha == 0) {
				strSimbolo = "";
				do {
					strSimbolo += caractere;
					carTemp = arquivo.peek();
					
					if (carTemp == '\n' || carTemp == EOF) {
						break;
					}
					
					arquivo.get(caractere);
				} while (1);
			}
			
			if (strSimbolo == "'") {
				strSimbolo = "";
				do {
					strSimbolo += caractere;
					carTemp = arquivo.peek();
					
					if (carTemp == '\n' || carTemp == EOF || carTemp == '\'') {
						if (carTemp == '\'') {
							arquivo.get(caractere);
							strSimbolo += caractere;
						}
						break;
					}
					
					arquivo.get(caractere);
				} while (1);
			}
				
			if (strSimbolo == "\"") {
				strSimbolo = "";
				do {
					strSimbolo += caractere;
					carTemp = arquivo.peek();
				
					if (carTemp == '\n' || carTemp == EOF || carTemp == '\"') {
						if (carTemp == '\"') {
							arquivo.get(caractere);
							strSimbolo += caractere;
						}
						break;
					}
				
					arquivo.get(caractere);
				} while (1);
			}
			
			if (strSimbolo == "//") {
				strSimbolo = "/";
				do {
					strSimbolo += caractere;
					carTemp = arquivo.peek();
				
					if (carTemp == '\n' || carTemp == EOF) {
						break;
					}
				
					arquivo.get(caractere);
				} while (1);
			}
			
			if (strSimbolo == "/") {
				if (arquivo.peek() == '*') {
					arquivo.get(caractere);
					strSimbolo += caractere;
				}
				
				arquivo.get(caractere);
				
				do {
					strSimbolo += caractere;
					carTemp = arquivo.peek();
					
					if (carTemp == EOF) {
						break;
					}
					
					if (caractere == '*' && carTemp == '/') {
						arquivo.get(caractere);
						strSimbolo += caractere;
						strSimbolo.erase(remove(strSimbolo.begin(),
							strSimbolo.end(), '\n'), strSimbolo.end());
						break;
					}
					
					arquivo.get(caractere);
				} while (1);
			}
		} else if (isdigit(caractere)) {
			bool containsE = false;
			bool containsPoint = false;
			bool containsSecondPoint = false;
			
			do {
				
				strSimbolo += caractere;
				carTemp = arquivo.peek();
				
				if (!isdigit(carTemp)) {
					
					if (tolower(carTemp) == 'e' && !containsE) {
						containsE = true;
						containsPoint = true;
						
					} else if (carTemp == '.' && !containsPoint) {
						containsPoint = true;
						
					} else if (carTemp == '.' && containsPoint
						&& containsE && !containsSecondPoint) {
						containsSecondPoint = true;
						
					} else if (tolower(carTemp) == 'l'
						|| tolower(carTemp) == 'f' && !containsE
						&& !containsPoint) {

						arquivo.get(caractere);
						strSimbolo += caractere;
						break;
					} else {
						break;
					}
				}
				
				arquivo.get(caractere);
			} while (1);
		} else {
			do {
				
				strSimbolo += caractere;
				carTemp = arquivo.peek();
				
				if (comparacoesValidas(carTemp) || carTemp == EOF) {
					break;
				}
				
				arquivo.get(caractere);
			} while (1);
		} 
		
		Simbolo simbolo(strSimbolo, linha);
		strSimbolo = "";
		tabela.add(simbolo);
		
		posLinha++;
		
		if (caractere == '\n') {
			linha++;
			posLinha = 0;
		}
	}
	
	Simbolo simbolo("<<EOF>>", linha);
	tabela.add(simbolo);
	return tabela;
}

int main(void) {
	string nomeDoArquivo("programa.txt");
	TabelaDeSimbolos tabela = analex(nomeDoArquivo);
	tabela.imprimir();
	tabela.parse();
	return 0;
}
