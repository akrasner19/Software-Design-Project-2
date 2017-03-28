#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <cmath>
#include <tuple>
#include <cctype>
#include "expression.hpp"
#include "interpreter_semantic_error.hpp"


using std::string;
using std::map;
using std::cerr;
using std::endl;
using std::tuple;
using std::list;

typedef void (*fcp) (Expression&, map<string,Expression>&);

void defineExp(Expression& exp, map<string,Expression>& envars);
void beginExp(Expression& exp, map<string,Expression>& envars);
void ifExp(Expression& exp, map<string,Expression>& envars);

void addExp(Expression& exp, map<string,Expression>& envars);
void subExp(Expression& exp, map<string,Expression>& envars);
void multExp(Expression& exp, map<string,Expression>& envars);
void divExp(Expression& exp, map<string,Expression>& envars);
void eqExp(Expression& exp, map<string,Expression>& envars);
void geqExp(Expression& exp, map<string,Expression>& envars);
void leqExp(Expression& exp, map<string,Expression>& envars);
void ltExp(Expression& exp, map<string,Expression>& envars);
void gtExp(Expression& exp, map<string,Expression>& envars);
void andExp(Expression& exp, map<string,Expression>& envars);
void orExp(Expression& exp, map<string,Expression>& envars);
void notExp(Expression& exp, map<string,Expression>& envars);

void pointExp(Expression& exp, map<string,Expression>& envars);
void lineExp(Expression& exp, map<string,Expression>& envars);
void arcExp(Expression& exp, map<string,Expression>& envars);

void sinExp(Expression& exp, map<string,Expression>& envars);
void cosExp(Expression& exp, map<string,Expression>& envars);
void arctanExp(Expression& exp, map<string,Expression>& envars);

void drawExp(Expression& exp, map<string,Expression>& envars);

void fillMap(map<string,fcp>& funcMap);

#endif