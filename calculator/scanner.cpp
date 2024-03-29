# include "scanner.h"
//# include "calcex.h"
#include "Token.h"
# include <iostream>
# include <string>

using namespace std;

//Uncomment this to get debug information
//#define debug

const int numberOfKeywords = 2;

const std::string keywd[numberOfKeywords] = {
	string("S"), string("R")
};

int isLetter(char c) {
	return((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int isDigit(char c) {
	return(c >= '0' && c <= '9');
}

int isWhiteSpace(char c) {
	return(c == ' ' || c == '\t' || c == '\n');
}

Scanner::Scanner(istream* in) :
	inStream(in),
	lineCount(1),
	colCount(-1),
	needToken(true),
	lastToken(0)
{}

Scanner::~Scanner() {
	try{
		delete inStream;
	} catch(...) {}
}


void Scanner::putBackToken() {
	needToken = false;
}

Token* Scanner::getToken() {
	if(!needToken) {
		needToken = true;
		return lastToken;
	}

	Token* t;
	int state = 0;
	bool foundOne = false;
	char c;
	string lex;
	TokenType type;
	int k;
	int column, line;

	c = inStream->get();

	while(!foundOne) {
		colCount++;
		switch(state) {
			case 0 :
				lex = "";
				column = colCount;
				line = lineCount;

				/******
				IDENTIFIER,
				KEYWORD,
				NUMBER,
				ADD,
				SUB,
				TIMES,
				DIVIDE,
				LPAREN,
				RPAREN,
				eof,
				unrecognized
				****/

				if(isLetter(c)) state = 1;
				else if(isDigit(c)) state = 2;
				else if(c == '+') state = 3;
				else if(c == '-') state = 4;
				else if(c == '*') state = 5;
				else if(c == '/') state = 6;
				else if(c == '(') state = 7;
				else if(c == ')') state = 8;
				else if(c == '\n') {
					colCount = -1;
					lineCount++;
				}
				else if(isWhiteSpace(c));
				else if(inStream->eof()) {
					foundOne = true;
					type = eof;
				}
				else{
					cout << "Unrecognized Token found at line " <<
					line << " and column " << column << endl;
					throw UnrecognizedToken();
				}
				break;
			case 1 :
				if(isLetter(c) || isDigit(c)) state = 1;
				else{
					for(k = 0; k < numberOfKeywords; k++)
						if(lex == keywd[k]) {
							foundOne = true;
							 type = KEYWORD;
						}

					 if(!foundOne) {
						 type = IDENTIFIER;
						 foundOne = true;
					 }
				}
				break;
			case 2 :
				if(isDigit(c)) state = 2;
				else{
					type = NUMBER;
					foundOne = true;
				}
				break;
			case 3 :
				type = ADD;
				foundOne = true;
				break;
			case 4 :
				type = SUB;
				foundOne = true;
				break;
			case 5 :
				type = TIMES;
				foundOne = true;
				break;
			case 6 :
				type = DIVIDE;
				foundOne = true;
				break;
			case 7 :
				type = LPAREN;
				foundOne = true;
				break;
			case 8 :
				type = RPAREN;
				foundOne = true;
			break;
		}

		if(!foundOne) {
			lex = lex + c;
			c = inStream->get();
		}
	}

	inStream->putback(c);
	colCount--;
	if(type == NUMBER || type == IDENTIFIER || type == KEYWORD) {
		t = new LexicalToken(type, new string(lex), line, column);
	}
	else{
		t = new Token(type, line,column);
	}

	#ifdef debug
		cout << "just found " << lex << " with type " << type << endl;
	# endif

	lastToken = t;
	return t;

}