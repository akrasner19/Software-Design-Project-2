#include "interpreter.hpp"
#include "environment.hpp"

#include <iostream>
#include <cmath>
#include <cctype>

using std::cout;

// Default construct an Interpreter with the default environment and an empty AST
Interpreter::Interpreter()
{
	ASTHead = Expression();
	ASTHead.atom.type = NoneType;
	double dVal = atan2(0, -1);
	Expression piVal(dVal);
	envariables["pi"] = piVal;
	/*Expression truVal(true);
	envariables["True"] = truVal;
	Expression falVal(false);
	envariables["False"] = falVal;*/
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
	Expression rxp = evalRecursive(ASTHead, envariables, functions);
	if (rxp.atom.type == OpType)
	{
		if (whatType(rxp.atom.string_value) == StringType
			&& functions.count(rxp.atom.string_value) == 0)
		{
			if (envariables.count(rxp.atom.string_value) > 0)
			{
				rxp = envariables[rxp.atom.string_value];
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}
	}
	return rxp;
}

Expression Interpreter::evalRecursive(Expression& head, map<string,Expression>& envars, map<string,fcp>& funcMap)
{
	if (head.children.size() == 0)
	{
		return head;
	}
	else
	{
		for (list<Expression>::iterator it = head.children.begin(); it != head.children.end(); ++it)
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

Expression giveRelExp(string token)
{
	if (whatType(token) == BoolType)
	{
		if (token == "True")
		{
			Expression element(true);
			return element;
		}
		else if (token == "False")
		{
			Expression element(false);
			return element;
		}
	}
	else if (whatType(token) == DoubleType)
	{
		Expression element(std::stod(token));
		return element;
	}
	else if (whatType(token) == StringType)
	{
		Expression element(token);
		return element;
	}
	else
	{
		throw InterpreterSemanticError("Error: issue in parsing");
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
			if (isdigit(tokens.front()[0]))
			{
				for (int i = 1; i < tokens.front().size(); ++i)
				{
					if(!isdigit(tokens.front()[i]) &&
						tokens.front()[i] != 'e' &&
						tokens.front()[i] != '-' &&
						tokens.front()[i] != '+' &&
						tokens.front()[i] != '.')
					{
						throw InterpreterSemanticError("Error: issue in parsing");
					}
				}
			}
			if (head.atom.type != OpType)
			{
				if (tokens.size() > 1)
				{
					list<string>::iterator checker = tokens.begin();
					checker++;
					if (*checker == ")")
					{
						head = giveRelExp(tokens.front());
						if (head.atom.type == StringType)
						{
							head.atom.type = OpType;
						}
						tokens.pop_front();
						parseHelper(tokens, head);
						if (tokens.empty())
						{
							return head;
						}
						else
						{
							throw InterpreterSemanticError("Error: issue in parsing");
						}
					}
				}
				head.atom.type = OpType;
				head.atom.string_value = tokens.front();
				tokens.pop_front();
				parseHelper(tokens, head);
				if (tokens.empty())
				{
					return head;
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in parsing");
				}
			} //make it so it splits the set up every time it hits a parenthesis into a subset that is processed by the method until it is called
			else
			{
				if (tokens.size() > 1)
				{
					list<string>::iterator checker = tokens.begin();
					checker++;
					if (*checker == ")")
					{
						Expression literal = giveRelExp(tokens.front());
						/*if (head.atom.type == StringType)
						{
							head.atom.type = OpType;
						}*/
						if (literal.atom.type == StringType)
						{
							literal.atom.type = OpType;
						}
						tokens.pop_front();
						parseHelper(tokens, head);
						head.children.push_back(literal);
						if (tokens.empty())
						{
							throw InterpreterSemanticError("Error: issue in parsing");
						}
						else
						{
							//call the method again with the parent as the node :/
							return parseHelper(tokens, head);
						}
					}
				}
				Expression element(tokens.front());
				element.atom.type = OpType;
				//element.prevHead = &head;
				tokens.pop_front();
				parseHelper(tokens, element);
				head.children.push_back(element);
				if (tokens.empty())
				{
					throw InterpreterSemanticError("Error: issue in parsing");
				}
				else
				{
					//call the method again with the parent as the node :/
					return parseHelper(tokens, head);
				}
			}
		}
		else
		{
			if (tokens.front() == ")")
			{
				tokens.pop_front();
				return head;
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
	else if (ASTHead.atom.type == StringType)
	{
		temp.atom.string_value = ASTHead.atom.string_value;
	}
	else if (ASTHead.atom.type == PointType)
	{
		temp.atom.point_value = ASTHead.atom.point_value;
	}
	else if (ASTHead.atom.type == LineType)
	{
		temp.atom.point_value = ASTHead.atom.point_value;
		temp.atom.point2_value = ASTHead.atom.point2_value;
	}
	else if (ASTHead.atom.type == ArcType)
	{
		temp.atom.point_value = ASTHead.atom.point_value;
		temp.atom.point2_value = ASTHead.atom.point2_value;
		temp.atom.double_value = ASTHead.atom.double_value;
	}
	else
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
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