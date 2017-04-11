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

// Construct an Expression with a single Point atom with value
Expression::Expression(tuple<double,double> value)
{
	atom.type = PointType;
	atom.point_value = value;
	prevHead = nullptr;
}

// Construct an Expression with a single Line atom with starting
// point start and ending point end
Expression::Expression(tuple<double,double> start, tuple<double,double> end)
{
	atom.type = LineType;
	atom.point_value = start;
	atom.point2_value = end;
	prevHead = nullptr;
}

// Construct an Expression with a single Arc atom with center
// point center, starting point start, and spanning angle angle in radians 
Expression::Expression(tuple<double,double> center, tuple<double,double> start, double angle)
{
	atom.type = ArcType;
	atom.point_value = center;
	atom.point2_value = start;
	atom.double_value = angle;
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
		else if (exp.atom.type == PointType)
		{
			if (exp.atom.point_value == this->atom.point_value)
			{
				if (exp.children.size() == this->children.size())
				{
					return true;
				}
			}
		}
		else if (exp.atom.type == LineType)
		{
			if (exp.atom.point_value == this->atom.point_value &&
				exp.atom.point2_value == this->atom.point2_value)
			{
				if (exp.children.size() == this->children.size())
				{
					return true;
				}
			}
		}
		else if (exp.atom.type == ArcType)
		{
			if (exp.atom.point_value == this->atom.point_value &&
				exp.atom.point2_value == this->atom.point2_value &&
				exp.atom.double_value == this->atom.double_value)
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