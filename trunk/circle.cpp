#include "circle.h"
#include <math.h>
#include "drawing.h"

extern Drawing * GDrawing;

#define PI 3.14f
#define STEP 1

Circle::Circle(QGraphicsEllipseItem *parent, QGraphicsScene * scene)
	: QGraphicsEllipseItem(parent,scene),_alpha(0),_parent(NULL),_alphaStep(5 * PI/360),_rDiff(0),_attached(NULL),_pixmap(NULL),_scale(0),_cross(true)
{
	setPos(  0 , 0 );
}

QPointF Circle::getCentre()
{
	return pos();
}

Circle::~Circle()
{
	if (_attached)
		delete (_attached);
}

#define ToDegree(x) x*180/PI

void Circle::advance( int phase )
{
	if ( (!_parent) || (!phase) )
		return;
	// calculate position of tracked symbol
	// move yourself as a according to parent
	setPos( _rDiff * cos(_alpha*_scale), _rDiff * sin(_alpha*_scale) );
	setRotation(ToDegree(_alpha));
	_alpha += _alphaStep;
	GDrawing->addPoint(mapToItem(GDrawing,_point));
}

void Circle::attach( Circle * at )
{
	_attached = at;
	at->setParent(this);
	advance(1);	
}

void Circle::setAlphaStep( float step )
{
	_alphaStep = step;
}

int Circle::getRange()
{
	return rect().width() / 2;
}

void Circle::setCross(QPointF point, QColor color)
{
	_cross = true;
	_point = point;
	_color = color;
}

void Circle::setParent( Circle* parent )
{
	if (_pixmap)
		delete _pixmap;
	// center pixmap
	_parent = parent;
	_rDiff = parent->getRange() - getRange();
	_scale = getRange()/(float)parent->getRange();
	advance(1);	
}

void Circle::setRange( int range )
{
	setRect(-range,-range,range * 2, range *2);
	if (_parent)
		_rDiff = _parent->getRange() - getRange();
}
