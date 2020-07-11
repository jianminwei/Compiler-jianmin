#include "ast.h"
#include <iostream>
#include "calculator.h"

//uncomment the next line to see the destructor calls
//#define debug

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right) :
	AST(), leftTree(left), rightTree(right)
{}

BinaryNode::~BinaryNode() {
	#ifdef debug
		cout << "In BinaryNode destructor" << endl;
	#endif
	try{
		delete leftTree;
	} catch(...) {}

	try{
	delete rightTree;
	} catch(...) {}
}

AST* BinaryNode::getLeftSubTree() const {
	return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
	return rightTree;
}

UnaryNode::UnaryNode(AST* sub) :
	AST(), subTree(sub)
{}

AST* UnaryNode::getSubTree() const {
	return subTree;
};

UnaryNode::~UnaryNode() {
	#ifdef debug
		cout << "In UnaryNode destructor" << endl;
	#endif
	try{
		delete subTree;
	} catch(...) {}
}

AddUnaryNode::AddUnaryNode(AST* sub) :
	UnaryNode(sub)
{}

int AddUnaryNode::evaluate() {
	return getSubTree()->evaluate();
}

AddNode::AddNode(AST* left, AST* right) :
	BinaryNode(left, right)
{}

int AddNode::evaluate() {
	return getLeftSubTree()->evaluate() +
		getRightSubTree()->evaluate();
}

SubNode::SubNode(AST* left, AST* right) :
	BinaryNode(left, right)
{}

int SubNode::evaluate() {
	return getLeftSubTree()->evaluate() -
		getRightSubTree()->evaluate();
}

MultiNode::MultiNode(AST* left, AST* right) :
	BinaryNode(left, right)
{}

int MultiNode::evaluate() {
	return getLeftSubTree()->evaluate() *
		getRightSubTree()->evaluate();
}

DivideNode::DivideNode(AST* left, AST* right) :
	BinaryNode(left, right)
{}

int DivideNode::evaluate() {
	return getLeftSubTree()->evaluate() /
		getRightSubTree()->evaluate();
}



