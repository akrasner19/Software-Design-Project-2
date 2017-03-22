#include "environment.hpp"
#include "interpreter.hpp"
#include "tokenize.hpp"
#include "expression.hpp"
#include "interpreter_semantic_error.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string>

using std::string;
using std::cerr;
using std::cout;
using std::cin;

int main(int argc, char*argv[])
{
	if (argc <= 3)
	{
		if (argc == 3)
		{
			string arg1(argv[1]);
			string arg2(argv[2]);
			if (arg1 == "-e")
			{
				try
				{
					string argument = arg2;//.substr(1,arg2.size()-2);
					std::istringstream iss(argument);
					Interpreter interpreter;

					if (!interpreter.parse(iss))
					{
						throw InterpreterSemanticError("Error: parsing issue");
					}
					Expression exp;
					interpreter.eval();
					interpreter.dupExpVals(exp);
					if (exp.atom.type == DoubleType)
					{
						cout << "(" << exp.atom.double_value << ")" << endl;;
					}
					else if (exp.atom.type == BoolType)
					{
						if (exp.atom.bool_value)
						{
							cout << "(True)" << endl;;
						}
						else
						{
							cout << "(False)" << endl;
						}
					}
					else
					{
						cout << "(" << exp.atom.string_value << ")" << endl;
					}
				}
				catch (InterpreterSemanticError& error)
				{
					cerr << error.what() << endl;
					return EXIT_FAILURE;
				}
			}
			else
			{
				cerr << "Error: Tag not recognized" << endl;
				return EXIT_FAILURE;
			}
		}
		else if (argc == 2)
		{
			string arg1(argv[1]);
			std::ifstream infile(arg1);
			if (infile.is_open())
			{
				try
				{
					Interpreter interpreter;

					if (!interpreter.parse(infile))
					{
						throw InterpreterSemanticError("Error: parsing issue");
					}
					Expression exp;
					interpreter.eval();
					interpreter.dupExpVals(exp);
					if (exp.atom.type == DoubleType)
					{
						cout << "(" << exp.atom.double_value << ")" << endl;
					}
					else if (exp.atom.type == BoolType)
					{
						if (exp.atom.bool_value)
						{
							cout << "(True)" << endl;
						}
						else
						{
							cout << "(False)" << endl;
						}
					}
					else
					{
						cout << "(" << exp.atom.string_value << ")" << endl;
					}
				}
				catch (InterpreterSemanticError& error)
				{
					cerr << error.what() << endl;
					return EXIT_FAILURE;
				}
				
			}
			else
			{
				cerr << "Error: File could not be opened" << endl;
				return EXIT_FAILURE;
			}
		}
		else
		{
			string str;
			cout << endl << "vtscript> ";
			Interpreter interpreter;
			while (getline(cin,str))
			{
				std::istringstream iss(str);
				try
				{
					if (!interpreter.parse(iss))
					{
						throw InterpreterSemanticError("Error: parsing issue");
					}
					Expression exp;
					interpreter.eval();
					interpreter.dupExpVals(exp);
					if (exp.atom.type == DoubleType)
					{
						cout << "(" << exp.atom.double_value << ")" << endl;
					}
					else if (exp.atom.type == BoolType)
					{
						if (exp.atom.bool_value)
						{
							cout << "(True)" << endl;
						}
						else
						{
							cout << "(False)" << endl;
						}
					}
					else
					{
						cout << "(" << exp.atom.string_value << ")" << endl;
					}
				}
				catch (InterpreterSemanticError& error)
				{
					cerr << error.what() << endl;
				}
				interpreter.reset();
				cout << endl << "vtscript> ";
			}
			//Interpreter interpreter;
			//interpreter.parse(iss);
			//interpreter.dump();
		}
	}
	else
	{
		cerr << "Error: Incorrect number of arguments" << endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
