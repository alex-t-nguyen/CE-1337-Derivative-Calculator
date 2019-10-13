/*
	@author Alex Nguyen
	Net Id: atn170001
	CE 1337.002
*/
#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

#include <iostream>

using namespace std;

class Node {
private:
	int outerCoefficient;
	char innerCoefficient;
	int exponent;
	char* trigIdentifier;
	Node* next;

public:
	Node();
	Node(int outCf, int inCf, int exponent);
	int getOuterCoefficient();
	int getInnerCoefficient();
	int getExponent();
	char* getTrigIdentifier();
	void setOuterCoefficient(int val);
	void setInnerCoefficient(int val);
	void setExponent(int val);
	void setTrigIdentifier(char* trig);
	Node* getNext();
	void setNext(Node* n);
	friend ostream& operator << (ostream& output, Node*& Node);
};
#endif // NODE_H_INCLUDED
