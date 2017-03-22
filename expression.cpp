#include "expression.hpp"
// Default construct an Expression of type None
Expression::Expression()
{
	atom.type = NoneType;
	prevHead = nullptr;
}

//Default destructor
Expression::~Expression()
{
	//nothing but maybe later
	prevHead = nullptr;
}

// Construct an Expression with a single Boolean atom with value
Expression::Expression(bool value)
{
	atom.type = BoolType;
	atom.bool_value = value;
	prevHead = nullptr;
}

// Construct an Expression with a single Number atom with value
Expression::Expression(double value)
{
	atom.type = DoubleType;
	atom.double_value = value;
	prevHead = nullptr;
}

// Construct an Expression with a single Symbol atom with value
Expression::Expression(const string & value)
{
	atom.type = StringType;
	atom.string_value = value;
	prevHead = nullptr;
}

// Equality operator for two Expressions, two expressions are equal if the have the same 
// type, atom value, and number of arguments
bool Expression::operator==(const Expression & exp) const
{
	if (exp.atom.type == this->atom.type)
	{
		if (exp.atom.type == BoolType)
		{
			if (exp.atom.bool_value == this->atom.bool_value)
			{
				if (exp.children.size() == this->children.size())
				{
					return true;
				}
			}
		}
		else if (exp.atom.type == DoubleType)
		{
			if (exp.atom.double_value == this->atom.double_value)
			{
				if (exp.children.size() == this->children.size())
				{
					return true;
				}
			}
		}
		else if (exp.atom.type == StringType || exp.atom.type == OpType)
		{
			if (exp.atom.string_value == this->atom.string_value)
			{
				if (exp.children.size() == this->children.size())
				{
					return true;
				}
			}
		}
		else if (exp.atom.type == NoneType)
		{
			if (exp.children.size() == this->children.size())
			{
				return true;
			}
		}
	}
	return false;
}