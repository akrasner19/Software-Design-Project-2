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
								"and", "or", "not", "define", "begin", "if"};
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
		else
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
				else
				{
					Expression mappedVal(envars[exp.children.front().atom.string_value].atom.string_value);
					exp.atom.type = StringType;
					exp.atom.string_value = envars[exp.children.front().atom.string_value].atom.string_value;
					envars[keyToExp] = mappedVal;
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
		exp.children.pop_front();
	}
}

void beginExp(Expression& exp, map<string,Expression>& envars)
{
	if (exp.children.empty())
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
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
	else
	{
		exp.atom.type = StringType;
		exp.atom.string_value = exp.children.front().atom.string_value;
	}
	exp.children.pop_front();
	while (exp.children.size() != 0)
	{
		exp.children.pop_front();
	}
}

void ifExp(Expression& exp, map<string,Expression>& envars)
{
	//temporary version that kinda works but technically evaluates everything
	if (exp.children.size() != 3 || exp.children.back().atom.type != BoolType)
	{
		throw InterpreterSemanticError("Error: issue in evaluation");
	}
	if (exp.children.back().atom.bool_value)
	{
		exp.children.pop_back();
		exp.children.pop_back();
		if (exp.children.back().atom.type == BoolType)
		{
			exp.atom.type = BoolType;
			exp.atom.bool_value = exp.children.back().atom.bool_value;
		}
		else if (exp.children.back().atom.type == DoubleType)
		{
			exp.atom.type = DoubleType;
			exp.atom.double_value = exp.children.back().atom.double_value;
		}
		else
		{
			
			if (envars.count(exp.children.back().atom.string_value) > 0)
			{
				if (envars[exp.children.back().atom.string_value].atom.type == BoolType)//line that changes
				{
					exp.atom.type = BoolType;
					exp.atom.bool_value = envars[exp.children.back().atom.string_value].atom.bool_value;//line that changes
				}
				else if (envars[exp.children.back().atom.string_value].atom.type == DoubleType)
				{
					exp.atom.type = DoubleType;
					exp.atom.double_value = envars[exp.children.back().atom.string_value].atom.double_value;
				}
				else
				{
					exp.atom.type = StringType;
					exp.atom.string_value = envars[exp.children.back().atom.string_value].atom.string_value;
				}
			}
			else
			{
				exp.atom.type = StringType;
				exp.atom.string_value = exp.children.back().atom.string_value;
			}
		}
		exp.children.pop_back();
	}
	else
	{
		exp.children.pop_back();
		if (exp.children.back().atom.type == BoolType)
		{
			exp.atom.type = BoolType;
			exp.atom.bool_value = exp.children.back().atom.bool_value;
		}
		else if (exp.children.back().atom.type == DoubleType)
		{
			exp.atom.type = DoubleType;
			exp.atom.double_value = exp.children.back().atom.double_value;
		}
		else
		{
			
			if (envars.count(exp.children.back().atom.string_value) > 0)
			{
				if (envars[exp.children.back().atom.string_value].atom.type == BoolType)//line that changes
				{
					exp.atom.type = BoolType;
					exp.atom.bool_value = envars[exp.children.back().atom.string_value].atom.bool_value;//line that changes
				}
				else if (envars[exp.children.back().atom.string_value].atom.type == DoubleType)
				{
					exp.atom.type = DoubleType;
					exp.atom.double_value = envars[exp.children.back().atom.string_value].atom.double_value;
				}
				else
				{
					exp.atom.type = StringType;
					exp.atom.string_value = envars[exp.children.back().atom.string_value].atom.string_value;
				}
			}
			else
			{
				exp.atom.type = StringType;
				exp.atom.string_value = exp.children.back().atom.string_value;
			}
		}
		exp.children.pop_back();
		exp.children.pop_back();
	}
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
}

