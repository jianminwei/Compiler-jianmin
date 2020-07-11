#include <iostream>
#include "parser.h"
#include "ast.h"
#include "Token.h"

using namespace std;

/***************************************************************
Prog -> Expr EOF
Expr -> Term RestExpr
RestExpr -> + Term RestExpr | - Term RestExpr | <null>
Term -> Storable RestTerm
RestTerm -> * Storable RestTerm | / Storable RestTerm | <null>
Storable -> Factor S | Factor
Factor -> number | R | (Expr)
****************************************************************/

AST* Parser::Prog() {
	AST* result = Expr();
	Token* t = scan->getToken();

	if(t->getType() != eof) {
		cout << "Syntax Error: Expected EOF, found token "
			<< "at column " << t->getCol() << endl;
		throw ParseError();
	}

	return result;
}

AST* Parser::Expr() {
	return RestExpr(Term());
}

AST* Parser::RestExpr(AST* e) {
	Token* t = scan->getToken();

	if(t->getType() == ADD) {
		return RestExpr(new AddNode(e, Term()));
	}

	if(t->getType() == SUB)
		return RestExpr(new SubNode(e, Term()));

	scan->putBackToken();

	return e;
}

AST* Parser::Term() {
	return RestTerm(Storable());
}

AST* Parser::RestTerm(AST* e) {
	Token* t = scan->getToken();

	if (t->getType() == TIMES) {
		return RestTerm(new MultiNode(e, Storable()));
	}

	if (t->getType() == DIVIDE)
		return RestTerm(new DivideNode(e, Storable()));

	scan->putBackToken();

	return e;
}

AST* Parser::Storable() {
	Token* t = scan->getToken();

	if (t->getType() == NUMBER) {
		return Factor();
	}

	scan->putBackToken();

	return nullptr;  /*Jianmin, need to fix. Leave it for now*/
}

AST* Parser::Factor() {
	return Factor();
}



