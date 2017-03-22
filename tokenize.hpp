#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <list>
#include <string>
#include <cctype>

using std::string;
using std::list;
using std::istream;

list<string> tokenize(istream& in);

#endif