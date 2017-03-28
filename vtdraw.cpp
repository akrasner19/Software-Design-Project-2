#include "main_window.hpp"
#include "qt_interpreter.hpp"
#include "repl_widget.hpp"
#include "canvas_widget.hpp"
#include "message_widget.hpp"
#include "qgraphics_arc_item.hpp"

#include <iostream>
#include <string>
#include <QApplication>
#include <QWidget>

using std::string;

int main(int argc, char*argv[])
{
	QApplication app(argc, argv);

	if (argc <= 2)
	{
		MainWindow * mw;
		if (argc == 2)
		{
			string arg1(argv[1]);
			mw = new MainWindow(arg1);
		}
		else if (argc == 1)
		{
			mw = new MainWindow();
		}
		mw->setMinimumWidth(800);
		mw->setMinimumHeight(600);
		mw->show();
	}
	else
	{
		cerr << "Error: Incorrect number of arguments" << endl;
	}
	return app.exec();
}