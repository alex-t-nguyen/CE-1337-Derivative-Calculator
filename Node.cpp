/*
	@author Alex Nguyen
	Net Id: atn170001
	CE 1337.002
*/

#include "Node.h"
#include <iostream>

using namespace std;

Node::Node() 
{
	outerCoefficient = 0;
	innerCoefficient = 0;
	exponent = 0;
	trigIdentifier = nullptr;
	next = nullptr;
}

Node::Node(int outC, int inC, int exp)
{
	outerCoefficient = outC;
	innerCoefficient = inC;
	exponent = exp;
	trigIdentifier = nullptr;
	next = nullptr;
}

int Node::getOuterCoefficient() { return outerCoefficient; }

int Node::getInnerCoefficient(){ return innerCoefficient; }

int Node::getExponent(){ return exponent; }

char* Node::getTrigIdentifier() { return trigIdentifier; }

void Node::setOuterCoefficient(int num){ outerCoefficient = num; }

void Node::setInnerCoefficient(int num){ innerCoefficient = num; }

void Node::setExponent(int num){ exponent = num; }

void Node::setTrigIdentifier(char* trig)
{ 
	int size = 0;
	while (trig[size] != '\0')
		size++;
	trigIdentifier = new char[size + 1];
	size = 0;
	while (trig[size] != '\0')
	{
		trigIdentifier[size] = trig[size];
		size++;
	}
	trigIdentifier[size] = '\0';
}

Node* Node::getNext(){ return next; }

void Node::setNext(Node* n) { next = n; }

ostream& operator << (ostream& output, Node*& node)
{
	if (node->getTrigIdentifier() == nullptr)
	{
		if (node->getExponent() != 0)
		{
			if (node->getOuterCoefficient() != 0)
				return output << node->getOuterCoefficient() << node->getInnerCoefficient() << "x^" << node->getExponent() << endl;
			else if (node->getInnerCoefficient() != 1)
				return output << node->getInnerCoefficient() << "x^" << node->getExponent() << endl;
			else
				return output << "x^" << node->getExponent() << endl;
		}
		else if (node->getExponent() == 1)
			return output << node->getOuterCoefficient() << node->getInnerCoefficient() << "x" << endl;
		else
			return output << node->getOuterCoefficient() << node->getInnerCoefficient() << endl;
	}
	else
	{
		if (node->getOuterCoefficient() != 0 && node->getInnerCoefficient() == 1)
			return output << node->getTrigIdentifier() << endl;
		else
			return output << node->getOuterCoefficient() << node->getInnerCoefficient() << node->getTrigIdentifier() << endl;
	}
	
}