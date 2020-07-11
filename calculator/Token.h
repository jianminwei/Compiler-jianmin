#pragma once
#include<string>

using namespace std;

enum TokenType {
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
};

class Token
{
public:
	Token();
	Token(TokenType typ, int line, int col);
	virtual ~Token();
	TokenType getType() const;
	int getLine() const;
	int getCol() const;

private:
	TokenType type;
	int line;
	int col;
};

class LexicalToken : public Token {
public:
	LexicalToken(TokenType typ, string* lex, int line, int col);
	~LexicalToken();
	virtual string getLex() const;
private:
	string* lexeme;
};


