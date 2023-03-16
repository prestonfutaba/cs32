
#include "Set.h"  // with ItemType being a type alias for char
#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

bool isValidInfix(string exp) 
{
	stack<char> pstack; // initialize postfix stack to empty
	stack<char> ostack; // intialize the operator stack to empty
	ostack.push('!'); 

	for (int i = 0; i < exp.length(); i++) 
	{
		const char ch = exp[i];
		const char top = ostack.top();

		switch (ch) 
		{
		case ' ': // nothing to do
			break;
		case '(':
			if (isalpha(top) || top == ')')
				return false;
			ostack.push(ch);
			pstack.push(ch);
			//cout << "( case" << endl;
			//cout << "char = " << ch << " " << endl;
			//cout << "top of o stack = " << ostack.top() << endl;
			//cout << "top of p stack = " << pstack.top() << endl << endl;
			break;
		case ')':
			if (!isalpha(top) && top != ')')
				return false;
			ostack.push(ch);
			//cout << ") case" << endl;
			//cout << "char = " << ch << " " << endl;
			//cout << "top of o stack = " << ostack.top() << endl;
			//cout << "top of p stack = " << pstack.top() << endl << endl;
			if (pstack.empty())
				return false;
			pstack.pop();
			//cout << "char = " << ch << " " << endl;
			//cout << "top of o stack = " << ostack.top() << endl;
			//cout << "top of p stack = " << pstack.top() << endl << endl;
			break;
		case '|':
		case '&':
			if (!isalpha(top) && top != ')')
				return false;
			ostack.push(ch);
			//cout << "& case" << endl;
			//cout << "char = " << ch << " " << endl;
			//cout << "top of o stack = " << ostack.top() << endl;
			//cout << "top of p stack = " << pstack.top() << endl << endl;
			break;
		case '!':
			if (isalpha(top) || top == ')')
				return false;
			ostack.push(ch);
			//cout << "! case" << endl;
			//cout << "char = " << ch << " " << endl;
			//cout << "top of o stack = " << ostack.top() << endl;
			//cout << "top of p stack = " << pstack.top() << endl << endl;
			break;
		default:
			if (!isalpha(ch) || !islower(ch) || isalpha(top) || top == ')')
				return false;
			ostack.push(ch);
			//cout << "default case" << endl;
			//cout << "char = " << ch << " " << endl;
			//cout << "top of o stack = " << ostack.top() << endl;
			//cout << "top of p stack = " << pstack.top() << endl << endl;
		}
	}

	

	while (ostack.top() == ')')
		ostack.pop();
	if (!isalpha(ostack.top()))
		return false;

	return pstack.empty();
}

int precedence(char ch) // ! then & then | left to right
{
	switch (ch) 
	{
	case '!':
		return 3;
	case '&':
		return 2;
	case '|':
		return 1;
	default:
		return 4;
	}
}

int evaluate(string infix, const Set& trueValues, const Set& falseValues,
	string& postfix, bool& result) 
{
	if (!isValidInfix(infix)) // check if valid infix
		return 1;


	// checking if an operand doesnt exist within truevalues/falsevalues or exists within both
	for (int i = 0; i < infix.length(); i++) {
		if (isalpha(infix[i])) {
			if (!trueValues.contains(infix[i]) && !falseValues.contains(infix[i]))
				return 2;
			if (trueValues.contains(infix[i]) && falseValues.contains(infix[i]))
				return 3;
		}
	}

	// creating postfix expression (from Carrano pseudocode)
	postfix = ""; // initialize postfix to empty
	stack<char> ostack; // initialize empty operator stack
	for (int i = 0; i < infix.length(); i++) // iterate through given infix
	{
		const char chh = infix[i];
		switch (chh) 
		{
		case ' ':
			break;
		case '(':
			ostack.push('('); // push the ( onto operator stack 
			break;
		case ')':;
			while (ostack.top() != '(') // while stack top is not (
			{
				postfix += ostack.top(); // append stack top to postfix
				ostack.pop(); // pop stack
			}
			ostack.pop(); // remove ( when found in stack
			break;
		case '|': // operators case
		case '&':
		case '!':
			while (!ostack.empty() && ostack.top() != '(' && precedence(infix[i]) <= precedence(ostack.top()))
			{
				// while stack is not empty and top of stack is not (
				postfix += ostack.top();
				ostack.pop();
			}
			ostack.push(chh);
			break;
		default: // case operand
			if (!trueValues.contains(chh) && !falseValues.contains(chh))
				return 1;
			postfix += chh;
			break;
		}
	}

	while (!ostack.empty()) // while stack is not empty
	{
		postfix += ostack.top(); // append stack top to postfix
		ostack.pop(); // pop operator stack
	}

	// evaluate postfix expression (from Carrano pseudocode)
	stack<bool> operandstack; // initialize empty operand stack

	for (int i = 0; i < postfix.length(); i++) // iterate through each character ch in postfix
	{
		char ch = postfix[i];
		if (isalpha(ch)) // operand case
		{
			if (trueValues.contains(ch)) 
				operandstack.push(true); // push that value onto operand stack
			else
				operandstack.push(false);
		}
		else // else ch is a binary operator
		{
			char operand2 = operandstack.top(); // set operand2 to the top of the operand stack 
			operandstack.pop(); // pop stack 
			char operand1 = operandstack.top(); // set operand1 to the top of the operand stack
			operandstack.pop(); // pop stack

			if (ch == '|') // evaluation of binary operators in compiler
			{
				operandstack.push(operand1 || operand2);
			}
			else if (ch == '&') 
			{
				operandstack.push(operand1 && operand2);
			}
			else 
			{
				operandstack.push(operand1);
				operandstack.push(!operand2);
			}
		}
	}
	result = operandstack.top(); // one item, result of evaluating expression
	return 0; // success
}

int main()
{
	string trueChars = "tywz";
	string falseChars = "fnx";
	Set trues;
	Set falses;
	for (int k = 0; k < trueChars.size(); k++)
		trues.insert(trueChars[k]);
	for (int k = 0; k < falseChars.size(); k++)
		falses.insert(falseChars[k]);

	string pf;
	bool answer;
	//isValidInfix("(n&(t|y))");
	
	
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && answer);
	assert(evaluate("y|", trues, falses, pf, answer) == 1);
	assert(evaluate("n t", trues, falses, pf, answer) == 1);
	assert(evaluate("nt", trues, falses, pf, answer) == 1);
	assert(evaluate("()", trues, falses, pf, answer) == 1);
	assert(evaluate("()z", trues, falses, pf, answer) == 1);
	assert(evaluate("y(n|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("t(&n)", trues, falses, pf, answer) == 1);
	assert(evaluate("(n&(t|y)", trues, falses, pf, answer) == 1);
	assert(evaluate("n+y", trues, falses, pf, answer) == 1);
	assert(evaluate("", trues, falses, pf, answer) == 1);
	assert(evaluate("f  |  !f & (t&n) ", trues, falses, pf, answer) == 0
		&& pf == "ff!tn&&|" && !answer);
	assert(evaluate(" x  ", trues, falses, pf, answer) == 0 && pf == "x" && !answer);
	trues.insert('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 3);
	falses.erase('x');
	assert(evaluate("((x))", trues, falses, pf, answer) == 0 && pf == "x" && answer);
	trues.erase('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 2);
	falses.insert('w');
	assert(evaluate("w| f", trues, falses, pf, answer) == 0 && pf == "wf|" && !answer);
	cout << "Passed all tests" << endl;
}
