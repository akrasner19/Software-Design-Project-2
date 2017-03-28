#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <string>
#include <list>
#include <tuple>

using std::string;
using std::list;
using std::tuple;


enum AtomType {NoneType, BoolType, DoubleType, PointType, 
				LineType, ArcType, StringType, OpType};

struct Atom{
	AtomType type;
	bool bool_value;
	double double_value;
	string string_value;
	tuple<double,double> point_value;
	tuple<double,double> point2_value;
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

	// Construct an Expression with a single Point atom with value
	Expression(tuple<double,double> value);

	// Construct an Expression with a single Line atom with starting
	// point start and ending point end
	Expression(tuple<double,double> start, 
	           tuple<double,double> end);

	// Construct an Expression with a single Arc atom with center
	// point center, starting point start, and spanning angle angle in radians 
	Expression(tuple<double,double> center, 
	           tuple<double,double> start, 
	           double angle);

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