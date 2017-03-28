#include "message_widget.hpp"
#include <QLayout>
#include <QLabel>

// Default construct a MessageWidget displaying no text
MessageWidget::MessageWidget(QWidget * parent) : QWidget(parent)
{
	QString str = "Message:";
	auto lbl = new QLabel(str);
	qled = new QLineEdit();
	qled->setReadOnly(true);
	auto layout = new QHBoxLayout();
	layout->addWidget(lbl);
	layout->addWidget(qled);

	setLayout(layout);
}

// a public slot accepting an informational message to display, clearing any error formatting
void MessageWidget::info(QString message)
{
	qled->setText(message);
	qled->setStyleSheet("");
}

// a public slot accepting an error message to display as selected text highlighted with a red background.
void MessageWidget::error(QString message)
{
	qled->setText(message);
	qled->setSelection(0,message.size());
	qled->setStyleSheet("QLineEdit {selection-background-color: red; }");
	qled->setFocus();
}