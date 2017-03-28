#ifndef QT_INTERPRETER_H
#define QT_INTERPRETER_H

#include <QObject>
#include <QString>
#include <string>
#include <sstream>
#include <iostream>
#include "interpreter_semantic_error.hpp"
#include "interpreter.hpp"
#include "expression.hpp"
#include <QGraphicsItem>

using std::string;

class QtInterpreter : public QObject
{
	Q_OBJECT
public:
	// Default construct an QtInterpreter with the default environment and an empty AST
	QtInterpreter(QObject * parent = nullptr);

	Expression headVal;

signals:
	// a signal emitting a graphic to be drawn as a pointer
	void drawGraphic(QGraphicsItem * item);

	// a signal emitting an informational message
	void info(QString message);

	// a signal emitting an error message
	void error(QString message);

public slots:
	// a public slot that accepts and expression string and parses/evaluates it
	void parseAndEvaluate(QString entry);

private:
	Interpreter interpreter;
};



#endif