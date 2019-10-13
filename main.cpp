/*
	@author Alex Nguyen
	Net Id: atn170001
	CE 1337.002
*/

#include <iostream>
#include <fstream>
#include "LinkedList.h"
#include "Node.h"
#include <string>
#include <sstream>

using namespace std;

void getDerivative(LinkedList*, ofstream &);
void setValues(string, Node*, char);
bool isTrig(string);
void readFile();

int main()
{

	/** For TRIG FUNCTIONS
		1. Read in to c-string
		2. if first character in array is letter (isalpha())
				loop through c-string until '\0' and identify the trig function
		3.		if(trig == 'sin' c-string)
					nodeName->setTrig("cos")
				else if()...Continue for all trig functions (including inverse)

		For CHAIN RULE, (only applies to trig functions):
		1. Pass trig->getNextNode() as parameter
		2. Create new node
		3. newNode->setOuterCoefficient([trig->getNext()->(getExponent)] * [trig->getNext()->getOuterCoefficient()])
		4. if([trig->getNext()->(getExponent)] == 1)
				trig->setExponent(0) and somehow delete the info completely
				OR
  				don't output an exponent and inner coefficient
		   else
				newNode->setExponent([trig->getNext()->(getExponent)] - 1)
				OUTPUT an newNode->getOuterCoefficient() << newNode->getInnerCoefficient() << '^' << newNode->getExponent() 
		5. Insert newNode right before node of trig function (no spaces between)

		----------------------------------------TAKING DERIVATIVE------------------------------------------------------
		totalCoeff = coeff * power; // Get actual coeff (exponent * coefficient)

		n->setOuterCoefficient(totalCoeff / 10 * 10); // Get "tens" place of coefficient
		n->setInnerCoefficient(totalCoeff % 10); //Get "ones" place of coefficient
		n->setExponent(--power); // Reduce exponent by 1

		// TO OUTPUT AS SINGLE COEFFICIENT -> outterCoefficient + innerCoefficient
		cout << "Derivative: " << n->getOuterCoefficient() + n->getInnerCoefficient() << "x^" << n->getExponent();
	*/
	cout << "DERIVATIVE PROGRAM" << endl;
	readFile();
	return 0;
}

void readFile()
{
	ifstream inFile;
	ofstream outFile;
	inFile.open("functions.txt");
	outFile.open("derive.txt");
	if (!inFile || !outFile)
	{
		cout << "Either one or both files could not be opened." << endl;
		outFile << "Either one or both files could not be opened." << endl;
	}
	else
	{
		string value;
		string buffer;
		while (getline(inFile, buffer))
		{
			LinkedList* equation = new LinkedList();
			istringstream term(buffer);
			char mathOperator = ' ';
			cout << "\nequation: " << buffer << endl;
			while (term >> value)
			{
				
				Node* newNode = new Node();
				if (value == "+")
				{
					mathOperator = '+';
					continue;
				}
				else if (value == "-")
				{
					mathOperator = '-';
					continue;
				}
				else
				{
					setValues(value, newNode, mathOperator);
					equation->appendList(newNode);			
				}
				mathOperator = ' ';
			}		
			LinkedList *copyList = new LinkedList(equation[0]); // Creates copy of original Linked List
		
			Node* iter = copyList->getHead();
			while (iter != nullptr)
			{
				iter = iter->getNext();
			}
			Node* originalHead = copyList->getHead();
			
			copyList->sort2(*copyList);
			getDerivative(copyList, outFile);
		}
	}
	inFile.close();
	outFile.close();
}

void setValues(string equation, Node* n, char mathOperator)
{
	// Checks if the read in term has a trig function in it
	if (!(isTrig(equation)))
	{
		char* coeffStr2 = new char[4];
		int j = 0;
		int i;
		long int totalCoeff;
		bool onlyNum = true;
		
		for (i = 0; i < equation.size(); i++)
		{
			if (isalpha(equation[i]))
				onlyNum = false;
		}
		if (onlyNum)
		{
			n->setOuterCoefficient(0);
			n->setInnerCoefficient(0);
			n->setExponent(1);
		}
		else // If there is an x-variable
		{
			for (i = 0; equation[i] != 'x' && (isdigit(equation[i]) || equation[i] == '-'); i++)
			{
				
				coeffStr2[j] = equation[i];
				j++;
			}

			long int coeff = atol(coeffStr2);
			if (i == 0) // If no coefficient before x (coefficient = 1)
			{
				char* powStr2 = new char[3];
				int j = 0;
				for (i = i + 2; i < equation.size(); i++) // Skips 2 characters to ignore the 'x' and '^'
				{
					powStr2[j] = equation[i];
					j++;
				}
				long int power = atol(powStr2);
				if (mathOperator == '-')
				{
					n->setOuterCoefficient(0); // Get "tens" place of coefficient
					n->setInnerCoefficient(-1); //Get "ones" place of coefficient
				}
				else// if (mathOperator == '+')
				{
					n->setOuterCoefficient(0); // Get "tens" place of coefficient
					n->setInnerCoefficient(1); //Get "ones" place of coefficient
				}

				if (power == 0)
					n->setExponent(1); // Get exponent
				else
					n->setExponent(power);
				delete[] powStr2;
			}
			else // If x has a coefficient
			{
				
				char* powStr2 = new char[3];
				int j = 0;
				for (i = i + 2; i < equation.size(); i++) // Skips 2 characters to ignore the 'x' and '^'
				{
					
					powStr2[j] = equation[i];
					j++;
				}
				long int power = atol(powStr2);
				if (mathOperator == '-')
				{
					n->setOuterCoefficient((coeff / 10) * -10); // Get "tens" place of coefficient
					n->setInnerCoefficient((coeff % 10) * -1); //Get "ones" place of coefficient
				}
				else// if (mathOperator == '+')
				{
					n->setOuterCoefficient((coeff / 10) * 10); // Get "tens" place of coefficient
					n->setInnerCoefficient((coeff % 10) * 1); //Get "ones" place of coefficient
				}

				if (power == 0)
					n->setExponent(1); // Get exponent
				else
					n->setExponent(power);
				delete[] powStr2;
			}
		}
		delete[] coeffStr2;
	}
	else // If read in term has trig function
	{
		/*	Sets trig identifier of equation in file to coressponding node
			1. Get the inner and outer coefficient of trig function from file equation
			2. Copy trig characters of file equation into char array
			3. Assign trig characters in array to the trigIdentifier data member of node
		*/
		string coeffStr = "";
		int i;
		long int totalCoeff;
		for (i = 0; isdigit(equation[i]) || equation[i] == '-'; i++)
		{
			coeffStr.push_back(equation[i]); // Copy only the coefficient part of string
		}
		if (i != 0)
		{
			long int coeff = atol(coeffStr.c_str());
			if (mathOperator == '-')
			{
				n->setOuterCoefficient((coeff / 10) * -10); // Get "tens" place of coefficient
				n->setInnerCoefficient((coeff % 10) * -1); //Get "ones" place of coefficient
			}
			else
			{
				n->setOuterCoefficient((coeff / 10) * 10); // Get "tens" place of coefficient
				n->setInnerCoefficient((coeff % 10) * 1); //Get "ones" place of coefficient
			}
		}
		else
		{
			if (mathOperator == '-')
			{
				n->setOuterCoefficient(0); // Get "tens" place of coefficient
				n->setInnerCoefficient(-1); //Get "ones" place of coefficient
			}
			else
			{
				n->setOuterCoefficient(0); // Get "tens" place of coefficient
				n->setInnerCoefficient(1); //Get "ones" place of coefficient
			}
		}
		char* newEquation = new char[10];
		int index = 0;
		for (; i < equation.size(); i++)
		{
			newEquation[index] = equation[i];
			 // Assigns all of the  characters of trig function to trigIdentifier of node
			index++;
		}
		newEquation[index] = '\0';
		n->setTrigIdentifier(newEquation);
		
		delete [] newEquation;
	}
}

void getDerivative(LinkedList* copyList, ofstream& outFile)
{
	long int outerCoeffD;
	long int innerCoeffD;
	int power;
	long int totalCoeff;
	int i = 0;
	outFile << *copyList << endl;
}

bool isTrig(string equation)
{
	bool trigFunction = true;
	bool isOnlyNum = true;
	for (int t = 0; t < equation.size(); t++)
	{
		if (equation[t] != 'x')
		{
			if (isdigit(equation[t]))
				trigFunction = false;
			else
				trigFunction = true;
		}
		else
			return false;
	}
	return trigFunction;
}