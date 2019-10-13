/*
	@author Alex Nguyen
	Net Id: atn170001
	CE 1337.002
*/

#include "LinkedList.h"
#include <iostream>
#include <fstream>

using namespace std;

enum Trig { SIN, COS, TAN, COT, SEC, CSC };
Trig convert(char* trigIdentifier);
void getTrigDerivative(Node* function);

LinkedList::LinkedList()
{
	head = nullptr;
}

LinkedList::LinkedList(Node* originalNode)
{
	Node* current = originalNode;

	// Check if original list has at least 1 node
	if (originalNode != nullptr)
	{
		Node* copy = new Node();
		copy->setOuterCoefficient(current->getOuterCoefficient());
		copy->setInnerCoefficient(current->getInnerCoefficient());
		copy->setExponent(current->getExponent());
		copy->setTrigIdentifier(current->getTrigIdentifier());
		copy->setNext(nullptr);

		// Keep track of head node
		Node* const src = copy;

		// 1st element already copied from above
		current = current->getNext();
		while (current != nullptr)
		{
			// Allocate a new node and iterate copy to the new node
			copy->setNext(new Node());
			copy = copy->getNext();

			// Copy Node contents to the new node
			copy->setOuterCoefficient(current->getOuterCoefficient());
			copy->setInnerCoefficient(current->getInnerCoefficient());
			copy->setExponent(current->getExponent());
			copy->setTrigIdentifier(current->getTrigIdentifier());
			// No next element
			copy->setNext(nullptr);
			current = current->getNext();
		}
	}
}
LinkedList::~LinkedList()
{
	Node* current = head;
	Node* prev;
	while (current != nullptr)
	{
		prev = current;
		current = current->getNext();
		delete prev;
	}
}


void LinkedList::appendList(Node* n)
{
	if (head != nullptr)
	{
		Node* iter = head;
		while (iter->getNext() != nullptr)
		{
			iter = iter->getNext();
		}
		iter->setNext(n);
	}
	else
	{
		head = n;
		head->setNext(nullptr);
	}
}

void LinkedList::sort2(LinkedList& list)
{
	LinkedList* tempList = new LinkedList();
	Node* current = list.getHead();
	Node* originalHead = list.getHead();
	int t = 0;
	Node* prevprev = nullptr;
	Node* trigTemp = nullptr;
	Node* trigArgTemp = nullptr;
	if (current == nullptr)
		return;
	Node* iter = list.getHead();
	Node* tail;
	bool allTrig = true;
	bool remainingIsTrig = true;
	while (iter->getNext() != nullptr)
	{
		t++;
		iter = iter->getNext();
	}
	int i = 0;
	tail = iter;
	iter = list.getHead();
	while (iter != nullptr)
	{
		if (iter->getTrigIdentifier() == nullptr)
		{
			allTrig = false;
		}
		else
		{
			if (iter->getNext() == tail)
				break;
			else
			{
				iter = iter->getNext()->getNext();
				while (iter != nullptr)
				{
					if (iter->getTrigIdentifier() == nullptr)
					{
						allTrig = false;
						remainingIsTrig = false;
						break;
					}
					else
						break;
					iter = iter->getNext()->getNext();
				}
				break;
			}
		}
		iter = iter->getNext();
	}
	Node* last = tail;
	Node* prev = nullptr;
	Node* prev2 = nullptr;
	bool trigIsLast = false;
	if (!allTrig && !remainingIsTrig)
	{
		while (i < t)
		{
			if (current->getTrigIdentifier() != nullptr && prev2 == nullptr)
			{
				for (int j = 0; j < 2; j++) // Repeat twice for trig function and its argument
				{
					prev = current;
					current = current->getNext();
					head = current;
					last->setNext(prev);
					last = last->getNext();
					last->setNext(nullptr);
					prev = nullptr;				
				}				
			}
			else
			{
				if (current->getTrigIdentifier() != nullptr && current->getNext()->getNext() == nullptr)
					trigIsLast = true;
				else if (current->getTrigIdentifier() != nullptr && prev2 != nullptr)
				{
					for (int i = 0; i < 2; i++)
					{
						prev = current;
						current = current->getNext();
						prev2->setNext(current);
						last->setNext(prev);
						last = last->getNext();
						last->setNext(nullptr);
					}
				}
				else
				{
					prev2 = current;
					current = current->getNext();
				}
			}
			i++;
		}
	}
	int numTrig = 0;
	iter = originalHead;
	while (iter != nullptr)
	{
		if (iter->getTrigIdentifier() != nullptr)
		{
				
			numTrig += 2;
			iter = iter->getNext()->getNext();
		}
		else
			iter = iter->getNext();
	}
	int temp;
	char* tempTrig;
	int length = getLength(list.getHead());
	for (int i = length - numTrig - 1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if ((list)[j]->getExponent() < (list)[j + 1]->getExponent())
			{
				temp = (list)[j]->getOuterCoefficient();
				(list)[j]->setOuterCoefficient((list)[j + 1]->getOuterCoefficient());
				(list)[j + 1]->setOuterCoefficient(temp);

				temp = (list)[j]->getInnerCoefficient();
				(list)[j]->setInnerCoefficient((list)[j + 1]->getInnerCoefficient());
				(list)[j + 1]->setInnerCoefficient(temp);

				temp = (list)[j]->getExponent();
				(list)[j]->setExponent((list)[j + 1]->getExponent());
				(list)[j + 1]->setExponent(temp);
					
			}
		}
	}
}

Node* LinkedList::operator++()
{	
	Node* ptr = new Node();
	
	ptr->setNext(head);
	head = ptr;
	return head;
}
Node* LinkedList::operator[](int index)
{
	int i = 0;
	Node* iter = head;
	while (i != index)
	{
		iter = iter->getNext();
		i++;
	}
	return iter;
}

ostream &operator<<(ostream& os, LinkedList& list)
{
	long int outerCoeffD;
	long int innerCoeffD;
	int power;
	long int totalCoeff;
	int i = 0;
	while (list[i] != nullptr)
	{
		if (list[i]->getTrigIdentifier() != nullptr)
		{
			if (list[i]->getInnerCoefficient() > 0)
			{
				getTrigDerivative(list[i]);
				// Inner and Outer Coefficients are negative for these 3 trig functions because the derivative is negative
				if (strcmp(list[i]->getTrigIdentifier(), "sin") == 0 || strcmp(list[i]->getTrigIdentifier(), "csc^2") == 0 || strcmp(list[i]->getTrigIdentifier(), "csccot") == 0)
				{
					if (list[i] != list.getHead() && list[i]->getNext()->getExponent() > 0 && list[i-1]->getInnerCoefficient() != 0)
					{
						os << "- ";
					}
					else if (list[i] != list.getHead() && list[i]->getNext()->getExponent() < 0 && list[i - 1]->getInnerCoefficient() != 0)
					{
						os << "+ ";
					}
					else // If node is head
					{
						list[i]->setOuterCoefficient(-1 * list[i]->getOuterCoefficient());
						list[i]->setInnerCoefficient(-1 * list[i]->getInnerCoefficient());
					}

					if (list[i]->getExponent() == 0)
					{
						if (abs(list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient()) != 1)
							os << (-1 * (list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient()));
						
						if (strcmp(list[i]->getTrigIdentifier(), "csccot") == 0)
						{
							os << "csc "; 
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
							os << "cot ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
						else
						{
							os << list[i]->getTrigIdentifier() << " ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
					}
					else if (list[i]->getExponent() >= 1 || list[i]->getExponent() <= 1)
					{
						os << (-1 * (list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient())) << "x";
						
						if (strcmp(list[i]->getTrigIdentifier(), "csccot") == 0)
						{
							os << "csc ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
							os << "cot ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
						else
						{
							os << list[i]->getTrigIdentifier() << " ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
					}
				}
				else // If trig derivative is positive
				{
					if (list[i] != list.getHead() && list[i]->getNext()->getExponent() > 0 && list[i - 1]->getInnerCoefficient() != 0)
					{
						os << "+ ";
					}
					else if (list[i] != list.getHead() && list[i]->getNext()->getExponent() < 0 && list[i - 1]->getInnerCoefficient() != 0)
						os << "- ";

					if (list[i]->getExponent() == 0)
					{
						
						if (abs(list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient()) != 1)
							os << list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient();
						if (strcmp(list[i]->getTrigIdentifier(), "sectan") == 0)
						{
							os << "sec ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient();
							os << "x ";
							os << "tan ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
						else
						{
							os << list[i]->getTrigIdentifier() << " ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
					}
					else if (list[i]->getExponent() >= 1 || list[i]->getExponent() <= 1)
					{
						os << list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient() << "x";
						
						if (strcmp(list[i]->getTrigIdentifier(), "sectan") == 0)
						{
							os << "sec ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
							os << "tan ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
						else
						{
							os << list[i]->getTrigIdentifier() << " ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
					}
				}
			i++; // Skips next node
			}
			else // If operator before trig function is '-' or negative coefficient for head node
			{
				getTrigDerivative(list[i]);
				
				// Inner and Outer Coefficients are negative for these 3 trig functions because the derivative is negative
				if (strcmp(list[i]->getTrigIdentifier(), "sin") == 0 || strcmp(list[i]->getTrigIdentifier(), "csc^2") == 0 || strcmp(list[i]->getTrigIdentifier(), "csccot") == 0)
				{
					if (list[i] != list.getHead() && list[i]->getNext()->getExponent() > 0 && list[i - 1]->getInnerCoefficient() != 0)
					{
						os << "+ ";
					}
					else if (list[i] != list.getHead() && list[i]->getNext()->getExponent() < 0 && list[i - 1]->getInnerCoefficient() != 0)
						os << "- ";
					else // If node is head
					{
						list[i]->setOuterCoefficient(-1 * list[i]->getOuterCoefficient());
						list[i]->setInnerCoefficient(-1 * list[i]->getInnerCoefficient());
					}

					if (list[i]->getExponent() == 0)
					{
						
						if (abs(list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient()) != 1)
							os << (1 * (list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient()));
						
						if (strcmp(list[i]->getTrigIdentifier(), "csccot") == 0)
						{
							os << "csc ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient();
							os << "x ";
							os << "cot ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
						else
						{
							os << list[i]->getTrigIdentifier() << " ";

							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient();
							os << "x ";
						}
						
					}
					else if (list[i]->getExponent() >= 1 || list[i]->getExponent() <= 1)
					{
						os << (1 * (list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient())) << "x";
						
						if (strcmp(list[i]->getTrigIdentifier(), "csccot") == 0)
						{
							os << "csc ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
							os << "cot ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
						else
						{
							os << list[i]->getTrigIdentifier() << " ";

							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1) // Coefficient doesn't show up as negative because it is equal to 1 -> Replace with minus sign in output
								os << list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient();
							os << "x^" << list[i]->getNext()->getExponent() << " ";
						}
						
					}
				}

				else // If trig derivative is positive
				{
					if (list[i] != list.getHead() && list[i]->getNext()->getExponent() > 0 && list[i - 1]->getInnerCoefficient() != 0)
						os << "- ";
					else if (list[i] != list.getHead() && list[i]->getNext()->getExponent() < 0 && list[i - 1]->getInnerCoefficient() != 0)
						os << "+ ";

					if (list[i]->getExponent() == 0)
					{

						if (abs(list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient()) != 1)
							os << -1 * (list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient());
						if (strcmp(list[i]->getTrigIdentifier(), "sectan") == 0)
						{
							os << "sec ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
							os << "tan ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
						else
						{
							os << list[i]->getTrigIdentifier() << " ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient();
							os << "x ";
						}
				
					}
					else if (list[i]->getExponent() >= 1 || list[i]->getExponent() <= 1)
					{
						os << -1 * (list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient()) << "x";
						
						if (strcmp(list[i]->getTrigIdentifier(), "sectan") == 0)
						{
							os << "sec ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
							os << "tan ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << (1 * (list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()));
							os << "x ";
						}
						else
						{
							os << list[i]->getTrigIdentifier() << " ";
							if (abs(list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient()) != 1)
								os << list[i]->getNext()->getOuterCoefficient() + list[i]->getNext()->getInnerCoefficient();
							os << "x^" << list[i]->getNext()->getExponent() << " ";
						}					
					}
				}
			i++; // Skips next node
			}
		}
		else // Not trig function
		{
			if (list[i]->getInnerCoefficient() == 0 && list[i]->getOuterCoefficient() == 0) // If node has no value
			{
				
				i++;
				continue;
			}
			outerCoeffD = list[i]->getOuterCoefficient();
			innerCoeffD = list[i]->getInnerCoefficient();
			power = list[i]->getExponent();

			//Taking derivative
			totalCoeff = (outerCoeffD + innerCoeffD) * power; // Get actual coeff (exponent * coefficient)
			list[i]->setOuterCoefficient(totalCoeff / 10 * 10); // Get "tens" place of coefficient
			list[i]->setInnerCoefficient(totalCoeff % 10); //Get "ones" place of coefficient
			list[i]->setExponent(--power); // Reduce exponent by 1
			
			if (list[i]->getInnerCoefficient() > 0)
			{
				if (list[i] != list.getHead() && power > 0)
					os << "+ ";
				//else if (list[i] != list.getHead() && power < 0)
				//	os << "- ";
				else if (list[i] == list.getHead())
				{
					list[i]->setOuterCoefficient(list[i]->getOuterCoefficient());
					list[i]->setInnerCoefficient(list[i]->getInnerCoefficient());
				}
				else
					os << "+ ";

				if (list[i]->getExponent() == 0)
					os << list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient() << " ";
				else if (list[i]->getExponent() == 1)
					os << list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient() << "x" << " ";
				else
					os << list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient() << "x^" << list[i]->getExponent() << " ";

			}
			else if (list[i]->getInnerCoefficient() < 0)
			{
				if (list[i] != list.getHead())// && power > 0)
					os << "- ";
				//else if (list[i] != list.getHead() && power < 0)
					
				else// if (list[i] == list.getHead())
				{
					list[i]->setOuterCoefficient(-1 * list[i]->getOuterCoefficient());
					list[i]->setInnerCoefficient(-1 * list[i]->getInnerCoefficient());
				}
				//else
				//	os << "- ";

				if (list[i]->getExponent() == 0)
					os << (-1 * (list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient())) << " ";
				else if (list[i]->getExponent() == 1)
					os << (-1 * (list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient())) << "x" << " ";
				else
					os << (-1 * (list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient())) << "x^" << list[i]->getExponent() << " ";
			}
			else // Inner Coefficient equals 0
			{
				if (list[i]->getExponent() == 0)
					os << list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient() << " ";
				else
					os << list[i]->getOuterCoefficient() + list[i]->getInnerCoefficient() << "x^" << list[i]->getExponent() << " ";
			}
		}
		i++;
	}
	return os;
}

Node* LinkedList::getHead()
{
	return head;
}

void getTrigDerivative(Node* function)
{
	Node* nextNode = function->getNext();

	long int outerCoeffD = nextNode->getOuterCoefficient();
	long int innerCoeffD = nextNode->getInnerCoefficient();
	long int power = nextNode->getExponent();
	//Taking derivative
	long int currentTotalCoeff = function->getOuterCoefficient() + function->getInnerCoefficient();
	long int totalCoeff = currentTotalCoeff * ((outerCoeffD + innerCoeffD) * power); // Get actual coeff (exponent * coefficient)

	function->setOuterCoefficient(totalCoeff / 10 * 10); // Get "tens" place of coefficient
	function->setInnerCoefficient(totalCoeff % 10); //Get "ones" place of coefficient
	function->setExponent(--power);
	
	Trig functionName = convert(function->getTrigIdentifier());
	
	switch (functionName)
	{
	case SIN:
	{
		char f[] = "cos";
		function->setTrigIdentifier(f);
		break;
	}
	case COS:
	{
		char f[] = "sin";
		function->setOuterCoefficient(function->getOuterCoefficient() * -1);
		function->setInnerCoefficient(function->getInnerCoefficient() * -1);
		function->setTrigIdentifier(f);
		break;
	}
	case TAN:
	{
		char f[] = "sec^2";
		function->setTrigIdentifier(f);
		break;
	}
	case COT:
	{
		char f[] = "csc^2";
		function->setOuterCoefficient(function->getOuterCoefficient() * -1);
		function->setInnerCoefficient(function->getInnerCoefficient() * -1);
		function->setTrigIdentifier(f);
		break;
	}
	case SEC:
	{
		char f[] = "sectan";
		function->setTrigIdentifier(f);
		break;
	}
	case CSC:
	{
		char f[] = "csccot";
		function->setOuterCoefficient(function->getOuterCoefficient() * -1);
		function->setInnerCoefficient(function->getInnerCoefficient() * -1);
		function->setTrigIdentifier(f);
		break;
	}
	}
}

Trig convert(char* trigIdentifier)
{
	if (strcmp(trigIdentifier, "sin") == 0)
		return SIN;
	else if (strcmp(trigIdentifier, "cos") == 0)
		return COS;
	else if (strcmp(trigIdentifier, "tan") == 0)
		return TAN;
	else if (strcmp(trigIdentifier, "cot") == 0)
		return COT;
	else if (strcmp(trigIdentifier, "sec") == 0)
		return SEC;
	else if(strcmp(trigIdentifier, "csc") == 0)
		return CSC;
}

int LinkedList::getLength(Node* head)
{
	if (head == nullptr)
		return 0;
	return 1 + getLength(head->getNext());
}
