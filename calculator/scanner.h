#pragma once
#ifndef scanner_h
#define scanner_h

#include<iostream>
#include "Token.h"


class UnrecognizedToken : public std::exception
{
public:
	virtual char const* what() const { return "Bad token."; }
};


class Scanner {
public:
	std::istream* inStream;
	int	lineCount;
	int	colCount;
	bool needToken;
	Token* lastToken;
	Scanner(istream* in);
	~Scanner();

	Token* getToken();
	void putBackToken();

private:


	Scanner();
};

#endif scanner_h

