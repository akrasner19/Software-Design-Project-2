#include "environment.hpp"

#include <set>
//put operation functions here
void addExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() < 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		double sum = 0;
		while (!exp.children.empty())
		{
			if (exp.children.front().atom.type != DoubleType)//line that changes
			{
				if (exp.children.front().atom.type == StringType)
				{
					if (envars.count(exp.children.front().atom.string_value) > 0)
					{
						if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
						{
							sum = sum + envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
						}
						else
						{
							throw InterpreterSemanticError("Error: issue in evaluation");
						}
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}//end of check
			else
			{
				sum = sum + exp.children.front().atom.double_value;
			}
			exp.children.pop_front();
		}
		exp.atom.type = DoubleType;
		exp.atom.double_value = sum;
	}
}

void subExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() < 1 || exp.children.size() > 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		double diff = 0;
		if (exp.children.size() == 1)
		{
			if (exp.children.front().atom.type != DoubleType)//line that changes
			{
				if (exp.children.front().atom.type == StringType)
				{
					if (envars.count(exp.children.front().atom.string_value) > 0)
					{
						if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
						{
							diff = -envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
						}
						else
						{
							throw InterpreterSemanticError("Error: issue in evaluation");
						}
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}//end of check
			else
			{
				diff = -exp.children.front().atom.double_value;
			}
			exp.children.pop_front();
		}
		else
		{
			if (exp.children.front().atom.type != DoubleType)//line that changes
			{
				if (exp.children.front().atom.type == StringType)
				{
					if (envars.count(exp.children.front().atom.string_value) > 0)
					{
						if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
						{
							diff = envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
						}
						else
						{
							throw InterpreterSemanticError("Error: issue in evaluation");
						}
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}//end of check
			else
			{
				diff = exp.children.front().atom.double_value;
			}
			exp.children.pop_front();
			if (exp.children.front().atom.type != DoubleType)//line that changes
			{
				if (exp.children.front().atom.type == StringType)
				{
					if (envars.count(exp.children.front().atom.string_value) > 0)
					{
						if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
						{
							diff = diff - envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
						}
						else
						{
							throw InterpreterSemanticError("Error: issue in evaluation");
						}
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}//end of check
			else
			{
				diff = diff - exp.children.front().atom.double_value;
			}
			exp.children.pop_front();
		}
		exp.atom.type = DoubleType;
		exp.atom.double_value = diff;
	}
}

void multExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() < 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		double prod = 0;
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						prod = envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			prod = exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		while (!exp.children.empty())
		{
			if (exp.children.front().atom.type != DoubleType)//line that changes
			{
				if (exp.children.front().atom.type == StringType)
				{
					if (envars.count(exp.children.front().atom.string_value) > 0)
					{
						if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
						{
							prod = prod * envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
						}
						else
						{
							throw InterpreterSemanticError("Error: issue in evaluation");
						}
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}//end of check
			else
			{
				prod = prod * exp.children.front().atom.double_value;
			}
			exp.children.pop_front();
		}
		exp.atom.type = DoubleType;
		exp.atom.double_value = prod;
	}
}

void divExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		double quo = 0;
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						quo = envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			quo = exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						quo = quo / envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			quo = quo / exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		exp.atom.type = DoubleType;
		exp.atom.double_value = quo;
	}
}

void eqExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		bool ans = true;
		double test = 0;
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						test = envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			test = exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						ans = test == envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			ans = test == exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		exp.atom.type = BoolType;
		exp.atom.bool_value = ans;
	}
}

void geqExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		bool ans = true;
		double test = 0;
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						test = envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			test = exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						ans = test >= envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			ans = test >= exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		exp.atom.type = BoolType;
		exp.atom.bool_value = ans;
	}
}

void leqExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		bool ans = true;
		double test = 0;
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						test = envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			test = exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						ans = test <= envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			ans = test <= exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		exp.atom.type = BoolType;
		exp.atom.bool_value = ans;
	}
}

void ltExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		bool ans = true;
		double test = 0;
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						test = envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			test = exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						ans = test < envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			ans = test < exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		exp.atom.type = BoolType;
		exp.atom.bool_value = ans;
	}
}

void gtExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		bool ans = true;
		double test = 0;
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						test = envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			test = exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		if (exp.children.front().atom.type != DoubleType)//line that changes
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)//line that changes
					{
						ans = test > envars[exp.children.front().atom.string_value].atom.double_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}//end of check
		else
		{
			ans = test > exp.children.front().atom.double_value;
		}
		exp.children.pop_front();
		exp.atom.type = BoolType;
		exp.atom.bool_value = ans;
	}
}

void andExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() < 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		bool ans = true;
		while (!exp.children.empty())
		{
			if (exp.children.front().atom.type != BoolType)
			{
				if (exp.children.front().atom.type == StringType)
				{
					if (envars.count(exp.children.front().atom.string_value) > 0)
					{
						if (envars[exp.children.front().atom.string_value].atom.type == BoolType)//line that changes
						{
							ans = ans && envars[exp.children.front().atom.string_value].atom.bool_value;//line that changes
						}
						else
						{
							throw InterpreterSemanticError("Error: issue in evaluation");
						}
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				ans = ans && exp.children.front().atom.bool_value;
			}
			exp.children.pop_front();
		}
		exp.atom.type = BoolType;
		exp.atom.bool_value = ans;
	}
}

void orExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() < 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		bool ans = false;
		while (!exp.children.empty())
		{
			if (exp.children.front().atom.type != BoolType)
			{
				if (exp.children.front().atom.type == StringType)
				{
					if (envars.count(exp.children.front().atom.string_value) > 0)
					{
						if (envars[exp.children.front().atom.string_value].atom.type == BoolType)//line that changes
						{
							ans = ans || envars[exp.children.front().atom.string_value].atom.bool_value;//line that changes
						}
						else
						{
							throw InterpreterSemanticError("Error: issue in evaluation");
						}
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				ans = ans || exp.children.front().atom.bool_value;
			}
			exp.children.pop_front();
		}
		exp.atom.type = BoolType;
		exp.atom.bool_value = ans;
	}
}

void notExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 1)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		bool ans = true;
		if (exp.children.front().atom.type != BoolType)
		{
			if (exp.children.front().atom.type == StringType)
			{
				if (envars.count(exp.children.front().atom.string_value) > 0)
				{
					if (envars[exp.children.front().atom.string_value].atom.type == BoolType)//line that changes
					{
						ans = !envars[exp.children.front().atom.string_value].atom.bool_value;//line that changes
					}
					else
					{
						throw InterpreterSemanticError("Error: issue in evaluation");
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
		}
		else
		{
			ans = !exp.children.front().atom.bool_value;
		}
		exp.children.pop_front();
		exp.atom.type = BoolType;
		exp.atom.bool_value = ans;
	}
}

//special cases----------------------------------------------------------------
void defineExp(Expression& exp, map<string,Expression>& envars)
{
	std::set<string> keywords {"+", "-", "*", "/", "=", ">=", "<=", ">", "<",
								"and", "or", "not", "define", "begin", "if",
								"point", "line", "arc", "sin", "cos", "arctan", "draw"};
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	else
	{
		string keyToExp;
		if (exp.children.front().atom.type != StringType)
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
		if (envars.count(exp.children.front().atom.string_value) > 0)
		{
			throw InterpreterSemanticError("Error: cannot redefine variable");
		}
		if (keywords.count(exp.children.front().atom.string_value) > 0)
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
		if (isdigit(exp.children.front().atom.string_value[0]))
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
		keyToExp = exp.children.front().atom.string_value;
		exp.children.pop_front();
		if (exp.children.front().atom.type == BoolType)
		{
			Expression mappedVal(exp.children.front().atom.bool_value);
			exp.atom.type = BoolType;
			exp.atom.bool_value = exp.children.front().atom.bool_value;
			envars[keyToExp] = mappedVal;
		}
		else if (exp.children.front().atom.type == DoubleType)
		{
			Expression mappedVal(exp.children.front().atom.double_value);
			exp.atom.type = DoubleType;
			exp.atom.double_value = exp.children.front().atom.double_value;
			envars[keyToExp] = mappedVal;
		}
		else if (exp.children.front().atom.type == StringType)
		{
			if (envars.count(exp.children.front().atom.string_value) > 0)
			{
				if (envars[exp.children.front().atom.string_value].atom.type == BoolType)//line that changes
				{
					Expression mappedVal(envars[exp.children.front().atom.string_value].atom.bool_value);
					exp.atom.type = BoolType;
					exp.atom.bool_value = envars[exp.children.front().atom.string_value].atom.bool_value;
					envars[keyToExp] = mappedVal;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)
				{
					Expression mappedVal(envars[exp.children.front().atom.string_value].atom.double_value);
					exp.atom.type = DoubleType;
					exp.atom.double_value = envars[exp.children.front().atom.string_value].atom.double_value;
					envars[keyToExp] = mappedVal;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == StringType)
				{
					Expression mappedVal(envars[exp.children.front().atom.string_value].atom.string_value);
					exp.atom.type = StringType;
					exp.atom.string_value = envars[exp.children.front().atom.string_value].atom.string_value;
					envars[keyToExp] = mappedVal;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == PointType)
				{
					Expression mappedVal(envars[exp.children.front().atom.string_value].atom.point_value);
					exp.atom.type = PointType;
					exp.atom.point_value = envars[exp.children.front().atom.string_value].atom.point_value;
					envars[keyToExp] = mappedVal;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == LineType)
				{
					Expression mappedVal(envars[exp.children.front().atom.string_value].atom.point_value,
										envars[exp.children.front().atom.string_value].atom.point2_value);
					exp.atom.type = LineType;
					exp.atom.point_value = envars[exp.children.front().atom.string_value].atom.point_value;
					exp.atom.point2_value = envars[exp.children.front().atom.string_value].atom.point2_value;
					envars[keyToExp] = mappedVal;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == ArcType)
				{
					Expression mappedVal(envars[exp.children.front().atom.string_value].atom.point_value,
										envars[exp.children.front().atom.string_value].atom.point2_value,
										envars[exp.children.front().atom.string_value].atom.double_value);
					exp.atom.type = ArcType;
					exp.atom.point_value = envars[exp.children.front().atom.string_value].atom.point_value;
					exp.atom.point2_value = envars[exp.children.front().atom.string_value].atom.point2_value;
					exp.atom.double_value = envars[exp.children.front().atom.string_value].atom.double_value;
					envars[keyToExp] = mappedVal;
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation");
				}
			}
			else
			{
				Expression mappedVal(exp.children.front().atom.string_value);
				exp.atom.type = StringType;
				exp.atom.string_value = exp.children.front().atom.string_value;
				envars[keyToExp] = mappedVal;
			}
		}
		else if (exp.children.front().atom.type == PointType)
		{
			Expression mappedVal(exp.children.front().atom.point_value);
			exp.atom.type = PointType;
			exp.atom.point_value = exp.children.front().atom.point_value;
			envars[keyToExp] = mappedVal;
		}
		else if (exp.children.front().atom.type == LineType)
		{
			Expression mappedVal(exp.children.front().atom.point_value,
								exp.children.front().atom.point2_value);
			exp.atom.type = LineType;
			exp.atom.point_value = exp.children.front().atom.point_value;
			exp.atom.point2_value = exp.children.front().atom.point2_value;
			envars[keyToExp] = mappedVal;
		}
		else if (exp.children.front().atom.type == ArcType)
		{
			Expression mappedVal(exp.children.front().atom.point_value,
								exp.children.front().atom.point2_value,
								exp.children.front().atom.double_value);
			exp.atom.type = ArcType;
			exp.atom.point_value = exp.children.front().atom.point_value;
			exp.atom.point2_value = exp.children.front().atom.point2_value;
			exp.atom.double_value = exp.children.front().atom.double_value;
			envars[keyToExp] = mappedVal;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
		exp.children.pop_front();
	}
}

void beginExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.empty())
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	list<Expression> spList;
	exp.atom.type = exp.children.back().atom.type;
	if (exp.children.back().atom.type == BoolType)
	{
		exp.atom.bool_value = exp.children.back().atom.bool_value;
	}
	else if (exp.children.back().atom.type == DoubleType)
	{
		exp.atom.double_value = exp.children.back().atom.double_value;
	}
	else if (exp.children.back().atom.type == StringType || exp.children.back().atom.type == OpType)
	{
		exp.atom.string_value = exp.children.back().atom.string_value;
	}
	else if (exp.children.back().atom.type == PointType)
	{
		exp.atom.point_value = exp.children.back().atom.point_value;
	}
	else if (exp.children.back().atom.type == LineType)
	{
		exp.atom.point_value = exp.children.back().atom.point_value;
		exp.atom.point2_value = exp.children.back().atom.point2_value;
	}
	else if (exp.children.back().atom.type == ArcType)
	{
		exp.atom.point_value = exp.children.back().atom.point_value;
		exp.atom.point2_value = exp.children.back().atom.point2_value;
		exp.atom.double_value = exp.children.back().atom.double_value;
	}
	if (exp.children.back().atom.type == NoneType)
	{
		exp.atom.type = NoneType;
		while (exp.children.back().children.size() > 0)
		{
			spList.push_back(exp.children.back().children.front());
			exp.children.back().children.pop_front();
		}
	}
	exp.children.pop_back();
	while (exp.children.size() != 0)
	{
		if (exp.children.back().atom.type == NoneType)
		{
			while (exp.children.back().children.size() > 0)
			{
				spList.push_back(exp.children.back().children.front());
				exp.children.back().children.pop_front();
			}
		}
		exp.children.pop_back();
	}
	if (!spList.empty())
	{
		exp.children = spList;
	}
}

void ifExp(Expression& exp, map<string,Expression>& envars)
{
	//temporary version that kinda works but technically evaluates everything
	if (exp.children.size() != 3)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	list<Expression> spList;
	bool x;
	if (exp.children.front().atom.type != BoolType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == BoolType)
		{
			x = envars[exp.children.front().atom.string_value].atom.bool_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
	}
	else
	{
		x = exp.children.front().atom.bool_value;
	}
	if (x)
	{
		exp.children.pop_front();
		if (exp.children.front().atom.type == BoolType)
		{
			exp.atom.type = BoolType;
			exp.atom.bool_value = exp.children.front().atom.bool_value;
		}
		else if (exp.children.front().atom.type == DoubleType)
		{
			exp.atom.type = DoubleType;
			exp.atom.double_value = exp.children.front().atom.double_value;
		}
		else if (exp.children.front().atom.type == StringType ||
				exp.children.front().atom.type == OpType)
		{
			
			if (envars.count(exp.children.front().atom.string_value) > 0)
			{
				exp.atom.type = envars[exp.children.front().atom.string_value].atom.type;
				if (envars[exp.children.front().atom.string_value].atom.type == BoolType)//line that changes
				{
					exp.atom.bool_value = envars[exp.children.front().atom.string_value].atom.bool_value;//line that changes
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)
				{
					exp.atom.double_value = envars[exp.children.front().atom.string_value].atom.double_value;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == StringType ||
						envars[exp.children.front().atom.string_value].atom.type == OpType)
				{
					exp.atom.string_value = envars[exp.children.front().atom.string_value].atom.string_value;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == PointType)
				{
					exp.atom.point_value = envars[exp.children.front().atom.string_value].atom.point_value;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == LineType)
				{
					exp.atom.point_value = envars[exp.children.front().atom.string_value].atom.point_value;
					exp.atom.point2_value = envars[exp.children.front().atom.string_value].atom.point2_value;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == ArcType)
				{
					exp.atom.point_value = envars[exp.children.front().atom.string_value].atom.point_value;
					exp.atom.point2_value = envars[exp.children.front().atom.string_value].atom.point2_value;
					exp.atom.double_value = envars[exp.children.front().atom.string_value].atom.double_value;
				}
			}
			else
			{
				exp.atom.type = exp.children.front().atom.type;
				exp.atom.string_value = exp.children.front().atom.string_value;
			}
		}
		else if (exp.children.front().atom.type == PointType)
		{
			exp.atom.type = PointType;
			exp.atom.point_value = exp.children.front().atom.point_value;
		}
		else if (exp.children.front().atom.type == LineType)
		{
			exp.atom.type = LineType;
			exp.atom.point_value = exp.children.front().atom.point_value;
			exp.atom.point2_value = exp.children.front().atom.point2_value;
		} 
		else if (exp.children.front().atom.type == ArcType)
		{
			exp.atom.type = ArcType;
			exp.atom.point_value = exp.children.front().atom.point_value;
			exp.atom.point2_value = exp.children.front().atom.point2_value;
			exp.atom.double_value = exp.children.front().atom.double_value;
		} 
		else
		{
			exp.atom.type = NoneType;
			while (exp.children.front().children.size() > 0)
			{
				spList.push_back(exp.children.front().children.front());
				exp.children.front().children.pop_front();
			}
		}
		exp.children.pop_front();
		exp.children.pop_front();
	}
	else
	{
		exp.children.pop_front();
		exp.children.pop_front();
		if (exp.children.front().atom.type == BoolType)
		{
			exp.atom.type = BoolType;
			exp.atom.bool_value = exp.children.front().atom.bool_value;
		}
		else if (exp.children.front().atom.type == DoubleType)
		{
			exp.atom.type = DoubleType;
			exp.atom.double_value = exp.children.front().atom.double_value;
		}
		else if (exp.children.front().atom.type == StringType ||
				exp.children.front().atom.type == OpType)
		{
			
			if (envars.count(exp.children.front().atom.string_value) > 0)
			{
				exp.atom.type = envars[exp.children.front().atom.string_value].atom.type;
				if (envars[exp.children.front().atom.string_value].atom.type == BoolType)//line that changes
				{
					exp.atom.bool_value = envars[exp.children.front().atom.string_value].atom.bool_value;//line that changes
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == DoubleType)
				{
					exp.atom.double_value = envars[exp.children.front().atom.string_value].atom.double_value;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == StringType ||
						envars[exp.children.front().atom.string_value].atom.type == OpType)
				{
					exp.atom.string_value = envars[exp.children.front().atom.string_value].atom.string_value;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == PointType)
				{
					exp.atom.point_value = envars[exp.children.front().atom.string_value].atom.point_value;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == LineType)
				{
					exp.atom.point_value = envars[exp.children.front().atom.string_value].atom.point_value;
					exp.atom.point2_value = envars[exp.children.front().atom.string_value].atom.point2_value;
				}
				else if (envars[exp.children.front().atom.string_value].atom.type == ArcType)
				{
					exp.atom.point_value = envars[exp.children.front().atom.string_value].atom.point_value;
					exp.atom.point2_value = envars[exp.children.front().atom.string_value].atom.point2_value;
					exp.atom.double_value = envars[exp.children.front().atom.string_value].atom.double_value;
				}
			}
			else
			{
				exp.atom.type = exp.children.front().atom.type;
				exp.atom.string_value = exp.children.front().atom.string_value;
			}
		}
		else if (exp.children.front().atom.type == PointType)
		{
			exp.atom.type = PointType;
			exp.atom.point_value = exp.children.front().atom.point_value;
		}
		else if (exp.children.front().atom.type == LineType)
		{
			exp.atom.type = LineType;
			exp.atom.point_value = exp.children.front().atom.point_value;
			exp.atom.point2_value = exp.children.front().atom.point2_value;
		} 
		else if (exp.children.front().atom.type == ArcType)
		{
			exp.atom.type = ArcType;
			exp.atom.point_value = exp.children.front().atom.point_value;
			exp.atom.point2_value = exp.children.front().atom.point2_value;
			exp.atom.double_value = exp.children.front().atom.double_value;
		} 
		else
		{
			exp.atom.type = NoneType;
			while (exp.children.front().children.size() > 0)
			{
				spList.push_back(exp.children.front().children.front());
				exp.children.front().children.pop_front();
			}
		}
		exp.children.pop_front();
	}
	if (!spList.empty())
	{
		exp.children = spList;
	}
}

void pointExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	double x;
	if (exp.children.front().atom.type != DoubleType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == DoubleType)
		{
			x = envars[exp.children.front().atom.string_value].atom.double_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
	}
	else
	{
		x = exp.children.front().atom.double_value;
	}
	exp.children.pop_front();
	double y;
	if (exp.children.front().atom.type != DoubleType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == DoubleType)
		{
			y = envars[exp.children.front().atom.string_value].atom.double_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
	}
	else
	{
		y = exp.children.front().atom.double_value;
	}
	exp.children.pop_front();
	tuple<double,double> coord (x, y);
	exp.atom.type = PointType;
	exp.atom.point_value = coord;
}

void lineExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	tuple<double,double> coord;
	if (exp.children.front().atom.type != PointType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == PointType)
		{
			coord = envars[exp.children.front().atom.string_value].atom.point_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
	}
	else
	{
		coord = exp.children.front().atom.point_value;
	}
	exp.children.pop_front();
	tuple<double,double> coord2;
	if (exp.children.front().atom.type != PointType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == PointType)
		{
			coord2 = envars[exp.children.front().atom.string_value].atom.point_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
	}
	else
	{
		coord2 = exp.children.front().atom.point_value;
	}
	exp.children.pop_front();
	exp.atom.type = LineType;
	exp.atom.point_value = coord;
	exp.atom.point2_value = coord2;
}

void arcExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 3)
	{
		throw InterpreterSemanticError("Error: issue 1 in arc evaluation");
	}
	tuple<double,double> coord;
	if (exp.children.front().atom.type != PointType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == PointType)
		{
			coord = envars[exp.children.front().atom.string_value].atom.point_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue 2 in arc evaluation");
		}
	}
	else
	{
		coord = exp.children.front().atom.point_value;
	}
	exp.children.pop_front();
	tuple<double,double> coord2;
	if (exp.children.front().atom.type != PointType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == PointType)
		{
			coord2 = envars[exp.children.front().atom.string_value].atom.point_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue 3 in arc evaluation");
		}
	}
	else
	{
		coord2 = exp.children.front().atom.point_value;
	}
	exp.children.pop_front();
	double angle;
	if (exp.children.front().atom.type != DoubleType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == DoubleType)
		{
			angle = envars[exp.children.front().atom.string_value].atom.double_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue 4 in arc evaluation");
		}
	}
	else
	{
		angle = exp.children.front().atom.double_value;
	}
	exp.children.pop_front();
	exp.atom.type = ArcType;
	exp.atom.point_value = coord;
	exp.atom.point2_value = coord2;
	exp.atom.double_value = angle;
}

void sinExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 1)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	double angle;
	if (exp.children.front().atom.type != DoubleType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == DoubleType)
		{
			angle = envars[exp.children.front().atom.string_value].atom.double_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
	}
	else
	{
		angle = exp.children.front().atom.double_value;
	}
	exp.children.pop_front();
	exp.atom.type = DoubleType;
	double rounder = sin(angle);
	if (rounder < 0.000000001 && rounder > -0.000000001)
	{
		rounder = 0;
	}
	exp.atom.double_value = rounder;
}

void cosExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 1)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	double angle;
	if (exp.children.front().atom.type != DoubleType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == DoubleType)
		{
			angle = envars[exp.children.front().atom.string_value].atom.double_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
	}
	else
	{
		angle = exp.children.front().atom.double_value;
	}
	exp.children.pop_front();
	exp.atom.type = DoubleType;
	double rounder = cos(angle);
	if (rounder < 0.000000001 && rounder > -0.000000001)
	{
		rounder = 0;
	}
	exp.atom.double_value = rounder;
}

void arctanExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.size() != 2)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	double y;
	if (exp.children.front().atom.type != DoubleType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == DoubleType)
		{
			y = envars[exp.children.front().atom.string_value].atom.double_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
	}
	else
	{
		y = exp.children.front().atom.double_value;
	}
	exp.children.pop_front();
	double x;
	if (exp.children.front().atom.type != DoubleType)
	{
		if (exp.children.front().atom.type == StringType
			&& envars.count(exp.children.front().atom.string_value) > 0
			&& envars[exp.children.front().atom.string_value].atom.type == DoubleType)
		{
			x = envars[exp.children.front().atom.string_value].atom.double_value;
		}
		else
		{
			throw InterpreterSemanticError("Error: issue in evaluation");
		}
	}
	else
	{
		x = exp.children.front().atom.double_value;
	}
	exp.children.pop_front();
	exp.atom.type = DoubleType;
	exp.atom.double_value = atan2(y,x);
}

void drawExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.empty())
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	for (list<Expression>::iterator it = exp.children.begin(); it != exp.children.end(); ++it)
	{
		if (it->atom.type != PointType &&
			it->atom.type != LineType &&
			it->atom.type != ArcType)
		{
			if (it->atom.type == StringType ||
				it->atom.type == OpType)
			{
				if (envars.count(it->atom.string_value) > 0)
				{
					it->atom.type = envars[it->atom.string_value].atom.type;
					if (envars[it->atom.string_value].atom.type == PointType)
					{
						it->atom.point_value = envars[it->atom.string_value].atom.point_value;
					}
					else if (envars[it->atom.string_value].atom.type == LineType)
					{
						it->atom.point_value = envars[it->atom.string_value].atom.point_value;
						it->atom.point2_value = envars[it->atom.string_value].atom.point2_value;
					}
					else if (envars[it->atom.string_value].atom.type == ArcType)
					{
						it->atom.point_value = envars[it->atom.string_value].atom.point_value;
						it->atom.point2_value = envars[it->atom.string_value].atom.point2_value;
						it->atom.double_value = envars[it->atom.string_value].atom.double_value;
					}
				}
				else
				{
					throw InterpreterSemanticError("Error: issue in evaluation draw parameters");
				}
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation draw parameters");
			}
		}
	}
	exp.atom.type = NoneType;
}

void fillMap(map<string,fcp>& funcMap)
{
	funcMap["+"] = &addExp;
	funcMap["-"] = &subExp;
	funcMap["*"] = &multExp;
	funcMap["/"] = &divExp;
	funcMap["="] = &eqExp;
	funcMap[">="] = &geqExp;
	funcMap["<="] = &leqExp;
	funcMap["<"] = &ltExp;
	funcMap[">"] = &gtExp;
	funcMap["and"] = &andExp;
	funcMap["or"] = &orExp;
	funcMap["not"] = &notExp;
	funcMap["define"] = &defineExp;
	funcMap["begin"] = &beginExp;
	funcMap["if"] = &ifExp;
	funcMap["point"] = &pointExp;
	funcMap["line"] = &lineExp;
	funcMap["arc"] = &arcExp;
	funcMap["sin"] = &sinExp;
	funcMap["cos"] = &cosExp;
	funcMap["arctan"] = &arctanExp;
	funcMap["draw"] = &drawExp;
}

