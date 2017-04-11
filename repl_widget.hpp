#ifndef REPL_WIDGET_H
#define REPL_WIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <list>
#include <QString>
#include <QEvent>
#include <QKeyEvent>

using std::list;

//event stuff start ------------------------
class EventLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	EventLineEdit(QWidget * parent = Q_NULLPTR);

protected:
	void keyPressEvent(QKeyEvent * event);

signals:
	void sendKeyEvent(QKeyEvent * kp);
};
//event stuff end --------------------------

class REPLWidget : public QWidget
{
	Q_OBJECT
public:
	// Default construct a REPLWidget
	REPLWidget(QWidget * parent = nullptr);

private:
	EventLineEdit * qle;

	list<QString> history;

	list<QString>::iterator idx;

	bool histActive;

public slots:
	void pullFromQLE();

	void historyAccess(QKeyEvent * kp);

signals:
	// A signal that sends the current edited text as a QString when the return key is pressed.
	void lineEntered(QString);
};

#endif