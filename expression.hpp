#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <list>

using std::string;
using std::list;

enum AtomType {NoneType, BoolType, DoubleType, StringType, OpType};

struct Atom{
	AtomType type;
	bool bool_value;
	double double_value;
	string string_value;
};

class Expression
{
public:
	// Default construct an Expression of type None
	Expression();

	//Default destructor
	~Expression();

	// Construct an Expression with a single Boolean atom with value
	Expression(bool value);

	// Construct an Expression with a single Number atom with value
	Expression(double value);

	// Construct an Expression with a single Symbol atom with value
	Expression(const string & value);

	// Equality operator for two Expressions, two expressions are equal if the have the same 
	// type, atom value, and number of arguments
	bool operator==(const Expression & exp) const;

	Atom atom;
	
	list<Expression> children;

	//used only in parsing
	Expression * prevHead;
private:

};


#endif