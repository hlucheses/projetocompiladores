#include <string>

#ifndef INC_UTILITARIOS
#define INC_UTILITARIOS

using namespace std;

string toUpperCase(string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = toupper(str[i]);
	}
	
	return str;
}

bool comparacoesValidas(char caractere) {
	return (isalpha(caractere) || caractere == '_') || (isspace(caractere)) ||
		((caractere >= '!' && caractere <= '/' && caractere != '$')
		|| (caractere >= ':' && caractere <= '?') || (caractere == '['
		|| caractere == ']' || caractere == '^') || (caractere >= '{'
		&& caractere <= '~'));
}

bool isBitwiseOrArithmetic(string str) {
	string arithmeticAndBitwiseOperators[][2] = {
					{"=", "ASSIGNMENT"}, {"+", "ADDITION"},
					{"-", "SUBTRACTION"}, {"*", "MULTIPLICATION"},
					{"/", "DIVISION"}, {"%", "MODULO"},
					{"&", "BITWISE_AND"}, {"|", "BITWISE_OR"},
					{"^", "BITWISE_XOR"}, {"~", "BITWISE_NOT"},
					{"<<", "SHIFT_BITS_LEFT"},
					{">>", "SHIFT_BITS_RIGHT"}};
					
	for (int i = 0; i < 12; i++) {
		if (str == arithmeticAndBitwiseOperators[i][0]) {
			return true;
		}
	}
	
	return false;
}

#endif

