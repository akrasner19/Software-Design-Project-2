#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "expression.hpp"
#include "tokenize.hpp"
#include "environment.hpp"
#include "interpreter_semantic_error.hpp"
#include <iostream>
#include <list>
#include <map>

using std::istream;
using std::list;
using std::string;
using std::map;

class Interpreter
{
public:
	// Default construct an Interpreter with the default environment and an empty AST
	Interpreter();

	// Given a vtscript program as a std::istream, attempt to parse into an internal AST
	// return true on success, false on failure
	bool parse(istream & expression);

	// Evaluate the current AST and return the resulting Expression
	// throws InterpreterSemanticError if a semantic error is encountered
	// the exception message string should document the nature of the semantic error 
	Expression eval();

	Expression evalRecursive(Expression& head, map<string,Expression>& envars, map<string,fcp>& funcMap);

	Expression parseHelper(list<string>& tokens, Expression& head);

	void dupExpVals(Expression& temp);

	void dump();

	void reset();

private:
	Expression ASTHead;

	map<string,Expression> envariables;
};

bool isNumber(const string& s);

AtomType whatType(string token);

void rtp(Expression& exp);

void soleSurvivor(Expression& exp);

#endif