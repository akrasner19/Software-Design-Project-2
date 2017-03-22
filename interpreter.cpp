#include "interpreter.hpp"
#include "environment.hpp"

#include <iostream>
#include <cmath>

using std::cout;

// Default construct an Interpreter with the default environment and an empty AST
Interpreter::Interpreter()
{
	ASTHead.atom.type = NoneType;
	double dVal = atan2(0, -1);
	Expression piVal(dVal);
	envariables["pi"] = piVal;
}

bool isNumber(const string& s)
{
    try
    {
        std::stod(s);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

// Given a vtscript program as a std::istream, attempt to parse into an internal AST
// return true on success, false on failure
bool Interpreter::parse(std::istream & expression)
{
	try
	{
		list<string> tokens = tokenize(expression);
		parseHelper(tokens, ASTHead);//change to deal with parse failures
	}
	catch (InterpreterSemanticError& error)
	{
		return false;
	}
	return true;
}

// Evaluate the current AST and return the resulting Expression
// throws InterpreterSemanticError if a semantic error is encountered
// the exception message string should document the nature of the semantic error 
Expression Interpreter::eval()
{
	map<string,fcp> functions;
	fillMap(functions);
	return evalRecursive(ASTHead, envariables, functions);
}

Expression Interpreter::evalRecursive(Expression& head, map<string,Expression>& envars, map<string,fcp>& funcMap)
{
	if (head.children.size() == 0)
	{
		return head;
	}
	else
	{
		for (list<Expression>::reverse_iterator it = head.children.rbegin(); it != head.children.rend(); ++it)
		{
			evalRecursive(*it, envars, funcMap);
		}
		if (funcMap.count(head.atom.string_value) > 0)
		{
			fcp fp = funcMap[head.atom.string_value];
			fp(head, envars);
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
		return head;
	}
}

AtomType whatType(string token)
{
	AtomType theType;
	if (isNumber(token))
	{
		theType = DoubleType;
	}
	else if (token == "True" || token == "False")
	{
		theType = BoolType;
	}
	else
	{
		theType = StringType;
	}
	return theType;
}

//Expression is the head of the relative thing
Expression Interpreter::parseHelper(list<string>& tokens, Expression& head)
{
	if (!tokens.empty())
	{
		if (tokens.front() == "(")
		{
			tokens.pop_front();
			if (tokens.empty())
			{
				throw InterpreterSemanticError("Error: issue in parsing");
			}
			if (head.atom.type != OpType)
			{
				head.atom.type = OpType;
				head.atom.string_value = tokens.front();
				tokens.pop_front();
				return parseHelper(tokens, head);
			} //make it so it splits the set up every time it hits a parenthesis into a subset that is processed by the method until it is called
			else
			{
				Expression element(tokens.front());
				element.atom.type = OpType;
				element.prevHead = &head;
				tokens.pop_front();
				parseHelper(tokens, element);
				head.children.push_back(element);
				return head;
			}
		}
		else
		{
			if (tokens.front() == ")")
			{
				tokens.pop_front();
				if (tokens.empty())
				{
					if (head.prevHead)
					{
						throw InterpreterSemanticError("Error: issue in parsing");
					}
					else
					{
						return head;
					}
				}
				else
				{
					//call the method again with the parent as the node :/
					if (!head.prevHead)
					{
						throw InterpreterSemanticError("Error: issue in parsing");
					}
					return parseHelper(tokens, *(head.prevHead));
				}
			}
			else if (whatType(tokens.front()) == BoolType)
			{
				if (tokens.front() == "True")
				{
					Expression element(true);
					tokens.pop_front();
					head.children.push_back(element);
				}
				else if (tokens.front() == "False")
				{
					Expression element(false);
					tokens.pop_front();
					head.children.push_back(element);
				}
				return parseHelper(tokens, head);
			}
			else if (whatType(tokens.front()) == DoubleType)
			{
				Expression element(std::stod(tokens.front()));
				tokens.pop_front();
				head.children.push_back(element);
				return parseHelper(tokens, head);
			}
			else if (whatType(tokens.front()) == StringType)
			{
				Expression element(tokens.front());
				tokens.pop_front();
				head.children.push_back(element);
				return parseHelper(tokens, head);
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in parsing");
			}
		}
	}
	else
	{
		throw InterpreterSemanticError("Error: issue in parsing");
	}
		
}

void Interpreter::dupExpVals(Expression& temp)
{
	temp.atom.type = ASTHead.atom.type;
	if (ASTHead.atom.type == DoubleType)
	{
		temp.atom.double_value = ASTHead.atom.double_value;
	}
	else if (ASTHead.atom.type == BoolType)
	{
		temp.atom.bool_value = ASTHead.atom.bool_value;
	}
	else
	{
		temp.atom.string_value = ASTHead.atom.string_value;
	}
}

void Interpreter::dump()
{
	rtp(ASTHead);
}

void rtp(Expression& exp)
{
	if (exp.atom.type == DoubleType)
	{
		cout << exp.atom.double_value << " ";
	}
	else if (exp.atom.type == BoolType)
	{
		cout << exp.atom.bool_value << " ";
	}
	else
	{
		cout << exp.atom.string_value << " ";
	}
	if (exp.children.empty())
	{
		//do nothing
	}
	else
	{
		cout << "\n";
		for (list<Expression>::iterator it = exp.children.begin(); it != exp.children.end(); ++it)
		{
			rtp(*it); //fix this and get this printing
		}
		cout << "\n" << endl;
	}
}

void Interpreter::reset()
{
	ASTHead.atom.type = NoneType;
	soleSurvivor(ASTHead);
}

void soleSurvivor(Expression& exp)
{
	if (!exp.children.empty())
	{
		for (list<Expression>::iterator it = exp.children.begin(); it != exp.children.end(); ++it)
		{
			soleSurvivor(*it);
		}
		while (!exp.children.empty())
		{
			exp.children.pop_front();
		}
	}
}
// Expression getHead(){
// 	return ASTHead;
// }
/*
//requires that the list being passed in starts with (
list<string> nextSubListGen(list<string> tokens)
{
	int i = 1;
	index = 1;
	list<string> subList;
	while (i > 0 && index < tokens.size())
	{
		subList.push_back(tokens[index])
		if (tokens[index] == ")")
		{
			i = i - 1;
		}
		else if (tokens[index] == '(')
		{
			i = i + 1;
		}
		index++;
	}
	return subList;
}
*/