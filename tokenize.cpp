#include "tokenize.hpp"

list<string> tokenize(istream& in)
{
	list<string> parseFeed;
	char temp;
	string junk;
	string tokenStor = "";
	while (in.get(temp))
	{
		if (temp == ';')
		{
			std::getline(in, junk);
			if (!tokenStor.empty())
			{
				string token;
				token = tokenStor;
				parseFeed.push_back(token);
				tokenStor.clear();
			}
		}
		else if (temp == ')' || temp == '(')
		{
			if (!tokenStor.empty())
			{
				string token;
				token = tokenStor;
				parseFeed.push_back(token);
				tokenStor.clear();
			}
			string pushable;
			pushable = temp;
			parseFeed.push_back(pushable);
		}
		else if (!isspace(temp))
		{
			char storable;
			storable = temp;
			tokenStor += storable;
		}
		else //if space
		{
			if (!tokenStor.empty())
			{
				string token;
				token = tokenStor;
				parseFeed.push_back(token);
				tokenStor.clear();
			}
		}
	}
	if (!tokenStor.empty())
	{
		string token;
		token = tokenStor;
		parseFeed.push_back(token);
		tokenStor.clear();
	}
	return parseFeed;
}