#pragma once
#ifndef ast_h
#define ast_h

using namespace std;

class AST{
public :
	AST();
	virtual ~AST() = 0;
	 virtual int evaluate() = 0;
};

class BinaryNode : public AST{
public :
	BinaryNode(AST * left, AST * right);
	~BinaryNode();
	AST* getLeftSubTree() const;
	AST* getRightSubTree() const;
private :
	AST * leftTree;
	AST* rightTree;
};

class UnaryNode : public AST{
public :
	UnaryNode(AST * sub);
	~UnaryNode();
	AST* getSubTree() const;
private :
	AST * subTree;
};

class AddUnaryNode : public UnaryNode {
public:
	AddUnaryNode(AST* tree);

	int evaluate();
};


class AddNode : public BinaryNode{
public :
AddNode(AST * left, AST * right);

int evaluate();
};

class SubNode : public BinaryNode {
public:
	SubNode(AST* left, AST* right);

	int evaluate();
};

class MultiNode : public BinaryNode {
public:
	MultiNode(AST* left, AST* right);

	int evaluate();
};

class DivideNode : public BinaryNode {
public:
	DivideNode(AST* left, AST* right);

	int evaluate();
};



#endif
