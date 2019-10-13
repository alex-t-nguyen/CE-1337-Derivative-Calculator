/*
	@author Alex Nguyen
	Net Id: atn170001
	CE 1337.002
*/
#pragma once

#include "Node.h"
#include <iostream>

using namespace std;

class LinkedList
{
private:
	Node* head;

public:
	LinkedList();
	LinkedList(Node*);
	~LinkedList();
	void appendList(Node*);	
	Node* operator++();
	Node* operator[](int);
	Node* getHead();
	int getLength(Node* head);
	friend ostream& operator<<(ostream&, LinkedList &);
	void sort2(LinkedList&);
};

