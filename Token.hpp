#include <algorithm>
#include <iostream>
#include <string>

#ifndef INC_TOKEN
#define INC_TOKEN

#include "Utilitarios.hpp"

using namespace std;

class Token {
	public:
		static string getTokenKeyword(string lexema) {
			
			string palavrasReservadas[] = {"alignas", "continue", "friend",
				"register", "true", "alignof", "decltype", "goto",
				"reinterpret_cast", "try", "asm", "default", "if", "return",
				"typedef", "auto", "delete", "inline", "short", "typeid",
				"bool", "do", "int", "signed", "typename", "break", "double",
				"long", "sizeof", "union", "case", "dynamic_cast", "mutable",
				"static", "unsigned", "catch", "else", "namespace",
				"static_assert", "using", "char", "enum", "new", "static_cast",
				"virtual", "char16_t", "explicit", "noexcept", "struct",
				"void", "char32_t", "export", "nullptr", "switch", "volatile",
				"class", "extern", "operator", "template", "wchar_t", "const",
				"false", "private", "this", "while", "constexpr", "float",
				"protected", "thread_local", "const_cast", "for", "public",
				"throw", "final", "override"};
			string operadoresBitwise[] = {"and", "and_eq", "bitand", "bitor",
				"compl", "not", "not_eq", "or", "or_eq", "xor", "xor_eq"};
			
			for (int i = 0; i < 75; i++)  {
				if (palavrasReservadas[i].compare(lexema) == 0) {
					return "TOKEN_KEYWORD_" + toUpperCase(lexema);
				}
			}
			
			for (int i = 0; i < 11; i++)  {
				if (operadoresBitwise[i].compare(lexema) == 0) {
					return "TOKEN_BITWISE_OPERATOR_" + toUpperCase(lexema);
				}
			}
			
			return "";
		}
		
		static string getToken(string lexema) {
	
			if (lexema.compare("<<EOF>>") == 0) {
				return "TOKEN_END_OF_FILE";
			}
	
			if (isalpha(lexema[0]) || lexema[0] == '_') {
				string tokenKeyword = getTokenKeyword(lexema);
	
				if (!tokenKeyword.empty()) {
					return tokenKeyword;
				} else {
					return "TOKEN_IDENTIFIER";
				}
			}
			
			if (lexema == "  ") {
				return "TOKEN_SPACE";
			}
			
			if (lexema == " ") {
				return "TOKEN_NEW_LINE";
			}
			
			if ((lexema[0] >= '!' && lexema[0] <= '/' && lexema[0] != '$')
				|| (lexema[0] >= ':' && lexema[0] <= '?')
				|| (lexema[0] == '[' || lexema[0] == ']' || lexema[0] == '^')
				|| (lexema[0] >= '{' && lexema[0] <= '~')) {
			
			
				string arithmeticBitwiseOperators[][2] = {
					{"=", "ASSIGNMENT"}, {"+", "ADDITION"},
					{"-", "SUBTRACTION"}, {"*", "MULTIPLICATION"},
					{"/", "DIVISION"}, {"%", "MODULO"},
					{"&", "BITWISE_AND"}, {"|", "BITWISE_OR"},
					{"^", "BITWISE_XOR"}, {"~", "BITWISE_NOT"},
					{"<<", "SHIFT_BITS_LEFT"},
					{">>", "SHIFT_BITS_RIGHT"}
				};
					
				string comparisonOperators[][2] = {
					{"==", "EQUAL_TO"}, {"!=", "NOT_EQUAL_TO"},
					{"<", "LESS_THAN"}, {">", "GREATER_THAN"},
					{"<=", "LESS_THAN_OR_EQUAL_TO"},
					{">=", "GREATER_THAN_OR_EQUAL_TO"}};
					
				string logicalOperators[][2] = {
					{"!", "NOT"}, {"&&", "AND"},
					{"||", "OR"}, {"?", "CONDITIONAL_TERNARY"},
					{",", "COMMA"}, {".", "MEMBER_ACCESS"}};
					
				string otherOperators[][2] = {
					{"::", "SCOPE_QUALIFIER"}, {"(", "LEFT_PARENTHESIS"},
					{")", "RIGHT_PARENTHESIS"},
					{"[", "LEFT_SQUARE_PARENTHESIS"},
					{"]", "RIGHT_SQUARE_PARENTHESIS"}, {"->", "MEMBER_ACCESS2"},
					{".*", "ACCESS_POINTER"}, {"->*", "ACCESS_POINTER2"},
					{"{", "OPENING_BRACE"}, {"}", "CLOSING_BRACE"},
					{":", "COLON"}, {";", "SEMI_COLON"}
				};
				
				for (int i = 0; i < 12; i++) {
					if (arithmeticBitwiseOperators[i][0] == lexema) {
						return "TOKEN_" + arithmeticBitwiseOperators[i][1]
							+ "_OPERATOR";
					} else if (i > 0 && lexema.length() ==
						(arithmeticBitwiseOperators[i][0].length() + 1)
						&& lexema.find(arithmeticBitwiseOperators[i][0]) !=
						string::npos && lexema[lexema.length() - 1] == '='
						&& lexema[0] != '=') {
							return "TOKEN_"
								+ arithmeticBitwiseOperators[i][1]
								+ "_COMPOUND_OPERATOR";
						}
							
				}
				
				for (int i = 0; i < 12; i++) {
					if (comparisonOperators[i][0] == lexema) {
						return "TOKEN_" + comparisonOperators[i][1]
							+ "_OPERATOR";
					}
				}
				
				for (int i = 0; i < 5; i++) {
					if (logicalOperators[i][0] == lexema) {
						return "TOKEN_" + logicalOperators[i][1] + "_OPERATOR";
					}
				}
				
				for (int i = 0; i < 12; i++) {
					if (otherOperators[i][0] == lexema) {
						return "TOKEN_" + otherOperators[i][1] + "_OPERATOR";
					}
				}
				
				if (lexema == "++") {
					return "TOKEN_INCREMENT_OPERATOR";
				} else if (lexema == "--") {
					return "TOKEN_DECREMENT_OPERATOR";
				}
				
				if (lexema[0] == '#') {
					if (lexema.length() > 1) {
						return "TOKEN_PREPROCESSOR_GIBBERISH";
					} else {
						return "TOKEN_UNKNOWN_INVALID_SYMBOL";
					}
				}
				
				if (lexema[0] == '\'') {
					if (lexema.length() > 1 && lexema[lexema.length()-1] == '\'') {
						return "TOKEN_CHAR_LITERAL";
					} else {
						return "TOKEN_UNKNOWN_INVALID_SYMBOL";
					}
				}
				
				if (lexema[0] == '\"') {
					if (lexema.length() > 1 && lexema[lexema.length()-1] == '\"') {
						return "TOKEN_STRING_LITERAL";
					} else {
						return "TOKEN_UNKNOWN_INVALID_SYMBOL";
					}
				}
				
				if (lexema[0] == lexema[1] && lexema[1] == '/') {
					return "TOKEN_ONE_LINE_COMMENT";
				}
				
				if (lexema[0] == '/' && lexema[1] == '*') {
					return "TOKEN_MULTIPLE_LINE_COMMENT";
				}
				
				return "TOKEN_SPECIAL_CHAR";
			}
			
			if (isdigit(lexema[0])) {
				if (lexema.find(".") == string::npos
					&& lexema.find("e") == string::npos
					&& lexema.find("f") == string::npos) {
					return "TOKEN_INTEGER_LITERAL";
				}
				return "TOKEN_FLOATING_POINT_LITERAL";
				
			}
			
			return "";
		}
};

#endif

