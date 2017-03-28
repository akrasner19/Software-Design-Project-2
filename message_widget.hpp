#ifndef MESSAGE_WIDGET_H
#define MESSAGE_WIDGET_H

#include <QWidget>
#include <QLineEdit>

class MessageWidget : public QWidget
{
	Q_OBJECT
public:
	// Default construct a MessageWidget displaying no text
	MessageWidget(QWidget * parent = nullptr);

private:
	QLineEdit * qled;

public slots:
	// a public slot accepting an informational message to display, clearing any error formatting
	void info(QString message);

	// a public slot accepting an error message to display as selected text highlighted with a red background.
	void error(QString message);
};


#endif