#include "repl_widget.hpp"
#include <QLayout>
#include <QLabel>
#include <QObject>
#include <QEvent>
#include <QDebug>

//event stuff start ------------------
EventLineEdit::EventLineEdit(QWidget * parent) : QLineEdit(parent)
{
}

void EventLineEdit::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Up ||
    	event->key() == Qt::Key_Down)
    {
        emit sendKeyEvent(event);
        //qDebug() << "Event emitted";
    }
    else
    {
    	QLineEdit::keyPressEvent(event);
    }
}
//event stuff end ---------------------

// Default construct a REPLWidget
REPLWidget::REPLWidget(QWidget * parent) : QWidget(parent)
{
	QString str = "vtscript>";
	auto lbl = new QLabel(str);
	qle = new EventLineEdit(this);
	auto layout = new QHBoxLayout();
	layout->addWidget(lbl);
	layout->addWidget(qle);

	QObject::connect(qle, SIGNAL(returnPressed()), 
					this, SLOT(pullFromQLE()));

	QObject::connect(qle, SIGNAL(sendKeyEvent(QKeyEvent*)),
					this, SLOT(historyAccess(QKeyEvent*)));

	setLayout(layout);

	idx = history.begin();
	histActive = false;
}

void REPLWidget::pullFromQLE()
{
	if (qle->text().size() > 0)
	{
		QString command = qle->text();
		emit lineEntered(command);
		history.push_front(command);
		qle->setText("");
	}
	histActive = false;
	idx = history.begin();
}

void REPLWidget::historyAccess(QKeyEvent * kp)
{
	//qDebug() << "It was called";
	if (history.size() > 0)
	{
		if (kp->key() == Qt::Key_Up)
		{
			if (histActive)
			{
				idx++;
				if (idx == history.end())
				{
					idx--;
				}
				qle->setText(*idx);
			}
			else
			{
				histActive = true;
				qle->setText(*idx);
			}
		}
		else if (kp->key() == Qt::Key_Down)
		{
			if (histActive)
			{
				if (idx == history.begin())
				{
					qle->setText("");
					histActive = false;
				}
				else
				{
					idx--;
					qle->setText(*idx);
				}
			}
		}
	}
}