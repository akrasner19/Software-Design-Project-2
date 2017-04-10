#include "qgraphics_arc_item.hpp"
#include <QLineF>

void QGraphicsArcItem::paint(QPainter * painter, 
							const QStyleOptionGraphicsItem * option, 
							QWidget * widget)
{
	painter->setPen(pen());
	painter->setBrush(brush());
	painter->drawArc(rect(), startAngle(), spanAngle());
}

QGraphicsArcItem::QGraphicsArcItem(qreal cX, qreal cY, 
								qreal spX, qreal spY, 
								qreal spanAngle, int diameter, 
								QGraphicsItem * parent) 
								: QGraphicsEllipseItem(cX, cY, diameter, diameter, parent)
{
	//qreal radius = sqrt(pow(cX-spX,2)+pow(cY-spY,2));
	int rAngle = (180*16*spanAngle)/atan2(0,-1);
	this->setSpanAngle(rAngle);
	QLineF tempLine(cX, cY, spX, spY);
	this->setStartAngle(16*tempLine.angle());
}
