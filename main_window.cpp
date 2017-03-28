#include "main_window.hpp"
#include <QLayout>
#include <QObject>
#include <QGraphicsItem>

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
	
}