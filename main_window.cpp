#include "main_window.hpp"
#include <QLayout>
#include <QObject>
#include <QGraphicsItem>
#include <sstream>
#include <fstream>
#include <streambuf>
#include <QString>

// Default construct a MainWindow
MainWindow::MainWindow(QWidget * parent) : QWidget(parent)
{
	msg = new MessageWidget;
	cnvs = new CanvasWidget;
	repl = new REPLWidget;
	qterp = new QtInterpreter;

	auto layout = new QVBoxLayout();
	layout->addWidget(msg);
	layout->addWidget(cnvs);
	layout->addWidget(repl);

	QObject::connect(repl, SIGNAL(lineEntered(QString)), 
					qterp, SLOT(parseAndEvaluate(QString)));

	QObject::connect(qterp, SIGNAL(info(QString)),
					msg, SLOT(info(QString)));

	QObject::connect(qterp, SIGNAL(error(QString)),
					msg, SLOT(error(QString)));

	QObject::connect(qterp, SIGNAL(drawGraphic(QGraphicsItem*)),
					cnvs, SLOT(addGraphic(QGraphicsItem*)));

	setLayout(layout);
}

// Default construct a MainWidow, using filename as the script file to attempt to preload
MainWindow::MainWindow(std::string filename, QWidget * parent) : QWidget(parent)
{
	msg = new MessageWidget;
	cnvs = new CanvasWidget;
	repl = new REPLWidget;
	qterp = new QtInterpreter;

	auto layout = new QVBoxLayout();
	layout->addWidget(msg);
	layout->addWidget(cnvs);
	layout->addWidget(repl);

	QObject::connect(repl, SIGNAL(lineEntered(QString)), 
					qterp, SLOT(parseAndEvaluate(QString)));

	QObject::connect(qterp, SIGNAL(info(QString)),
					msg, SLOT(info(QString)));

	QObject::connect(qterp, SIGNAL(error(QString)),
					msg, SLOT(error(QString)));

	QObject::connect(qterp, SIGNAL(drawGraphic(QGraphicsItem*)),
					cnvs, SLOT(addGraphic(QGraphicsItem*)));

	setLayout(layout);

	std::ifstream infile(filename);
	if (infile.is_open())
	{
		std::string str((std::istreambuf_iterator<char>(infile)),
                 	std::istreambuf_iterator<char>());

		QString qstr = QString::fromStdString(str);

		qterp->parseAndEvaluate(qstr);
	}
	else
	{
		msg->error("Error: File could not be opened");
	}
}