#include "canvas_widget.hpp"
#include <QLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
//#include <iostream>
// Default construct a CanvasWidget
CanvasWidget::CanvasWidget(QWidget * parent) : QWidget(parent)
{
	scene = new QGraphicsScene(this);
	auto view = new QGraphicsView(scene);
	//auto layout = new QGraphicsLayout();
	auto layout = new QVBoxLayout();
	layout->addWidget(view);

	setLayout(layout);
}

// A public slot that accepts a signal in the form of a QGraphicsItem pointer containing an 
// object derived from QGraphicsItem to draw
void CanvasWidget::addGraphic(QGraphicsItem * item)
{
	scene->addItem(item);
	//std::cout << "The slot was called" << std::endl;
}