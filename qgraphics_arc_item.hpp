#ifndef QGRAPHICS_ARC_ITEM_H
#define QGRAPHICS_ARC_ITEM_H

#include <QGraphicsEllipseItem>
#include <cmath>
#include <QPainter>

class QGraphicsArcItem : public QGraphicsEllipseItem
{
	public:
		QGraphicsArcItem(qreal cX, qreal cY, 
					qreal spX, qreal spY, 
					qreal spanAngle, int diameter,
					QGraphicsItem * parent = 0);

	protected:
		void paint(QPainter * painter, 
				const QStyleOptionGraphicsItem * option, 
				QWidget * widget=0);
};


#endif