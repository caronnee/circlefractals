#include "drawing.h"
#include <assert.h>

extern QGraphicsScene * GScene;
extern Drawing * GDrawing;

Drawing::Drawing(QGraphicsItem *parent)
	: QGraphicsItem(parent),_lastPoint(1)
{
	_points.clear();
}

Drawing::~Drawing()
{

}
//this is the same as repaint. TODO repaint only small rectangles
void Drawing::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */ )
{
	if (_points.size() < 2)
		return;
	QRectF rect(boundingRect());
	assert(!rect.isEmpty());
	_lastPoint = 1;
	while ( _lastPoint < _points.size() )
	{
		painter->drawLine(_points[_lastPoint-1],_points[_lastPoint]);
		_lastPoint++;
	}
	update(rect);
}

QRectF Drawing::boundingRect( void ) const
{
	return parentItem()->boundingRect();
}

#define MAXPOINTS 10000

void Drawing::addPoint(const QPointF & newPos )
{
	if (_lastPoint > MAXPOINTS)
		return;
	_points.append(newPos);
}

void Drawing::clear()
{
	_points.clear();
}

//void Cross::paint( QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */ )
//{
//	painter->drawLine(-2,-2,2,2);
//	painter->drawLine(-2,2,2,-2);
//}
//Cross::Cross(QGraphicsItem * parent) : base(parent,GScene) {}
//
//void Cross::advance( int phase )
//{
//	if(!phase)
//		return;
//	GDrawing->addPoint( mapToItem(GDrawing,pos()));
//}
