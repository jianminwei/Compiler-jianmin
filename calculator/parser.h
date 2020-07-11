#pragma once
#ifndef parser_h
#define parser_h

#include "ast.h"
#include "scanner.h"

class ParseError : public std::exception
{
public:
	virtual char const* what() const { return "Bad token."; }
};


class Parser{
public :
Parser(istream * in);
 ~Parser();

 AST* parse();

 private :
	 AST * Prog();
	 AST* Expr();
	 AST* RestExpr(AST* e);
	 AST* Term();
	 AST* RestTerm(AST* t);
	 AST* Storable();
	 AST* Factor();

	 Scanner* scan;
};

#endif
