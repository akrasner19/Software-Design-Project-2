#include "qt_interpreter.hpp"
#include "environment.hpp"
#include "interpreter.hpp"
#include "tokenize.hpp"
#include "expression.hpp"
#include "interpreter_semantic_error.hpp"

#include <iostream>
#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QBrush>
#include <tuple>

using std::string;
using std::cerr;
using std::cout;
using std::cin;

QtInterpreter::QtInterpreter(QObject * parent) : QObject(parent)
{
	interpreter = Interpreter();
}

void QtInterpreter::parseAndEvaluate(QString entry)
{
	try
	{
		string str = entry.toStdString();
		std::istringstream iss(str);
		if (!interpreter.parse(iss))
		{
			throw InterpreterSemanticError("Error: parsing issue");
		}
		Expression hv = interpreter.eval();
		std::stringstream ss;
		//don't forget to account for when begin calls draw
		while (hv.children.size() > 0)
		{
			if (hv.children.front().atom.type == PointType)
			{
				qreal x = std::get<0>(hv.children.front().atom.point_value);
				qreal y = std::get<1>(hv.children.front().atom.point_value);
				auto pointcirc = new QGraphicsEllipseItem(x, y, 4, 4);
				QBrush brush(Qt::SolidPattern);
				pointcirc->setBrush(brush);
				emit drawGraphic(pointcirc);
				//cout << "the emit happened" << endl;
			}
			else if (hv.children.front().atom.type == LineType)
			{
				qreal x1 = std::get<0>(hv.children.front().atom.point_value);
				qreal y1 = std::get<1>(hv.children.front().atom.point_value);
				qreal x2 = std::get<0>(hv.children.front().atom.point2_value);
				qreal y2 = std::get<1>(hv.children.front().atom.point2_value);
				auto line = new QGraphicsLineItem(x1, y1, x2, y2);
				emit drawGraphic(line);
			}
			else if (hv.children.front().atom.type == ArcType)
			{
				qreal x = std::get<0>(hv.children.front().atom.point_value);
				qreal y = std::get<1>(hv.children.front().atom.point_value);
				qreal w = std::get<0>(hv.children.front().atom.point2_value);
				qreal h = std::get<1>(hv.children.front().atom.point2_value);
				auto arc = new QGraphicsEllipseItem(x, y, w, h);
				int i = hv.children.front().atom.double_value;
				arc->setSpanAngle(i);
				emit drawGraphic(arc);
			}
			else
			{
				throw InterpreterSemanticError("Error: issue in evaluation");
			}
			hv.children.pop_front();
		}
		if (hv.atom.type == DoubleType)
		{
			ss << "(" << hv.atom.double_value << ")";
		}
		else if (hv.atom.type == BoolType)
		{
			if (hv.atom.bool_value)
			{
				ss << "(True)";
			}
			else
			{
				ss << "(False)";
			}
		}
		else if (hv.atom.type == StringType || hv.atom.type == OpType)
		{
			ss << "(" << hv.atom.string_value << ")";
		}
		else if (hv.atom.type == PointType)
		{
			ss << "(" << std::get<0>(hv.atom.point_value) << ",";
			ss << std::get<1>(hv.atom.point_value) << ")";
		}
		else if (hv.atom.type == LineType)
		{
			ss << "((" << std::get<0>(hv.atom.point_value) << ",";
			ss << std::get<1>(hv.atom.point_value) << ")" << "(";
			ss << std::get<0>(hv.atom.point2_value) << ",";
			ss << std::get<1>(hv.atom.point2_value) << "))";
		}
		else if (hv.atom.type == ArcType)
		{
			ss << "((" << std::get<0>(hv.atom.point_value) << ",";
			ss << std::get<1>(hv.atom.point_value) << ")" << "(";
			ss << std::get<0>(hv.atom.point2_value) << ",";
			ss << std::get<1>(hv.atom.point2_value) << ") ";
			ss << hv.atom.double_value << ")";
		}
		else
		{
			ss << "(None)";
		}
		QString qstr = QString::fromStdString(ss.str());
		emit info(qstr);
		cout << ss.str() << endl;
	}
	catch (InterpreterSemanticError& erro)
	{
		std::stringstream ss;
		ss << erro.what();
		QString qstr = QString::fromStdString(ss.str());
		emit error(qstr);
	}
	interpreter.reset();
}