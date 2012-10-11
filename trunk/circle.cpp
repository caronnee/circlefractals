#include "circle.h"
#include <math.h>
#include "drawing.h"

extern Drawing * GDrawing;
extern int GFrameStep;

#define PI 3.14f

Circle::Circle(QGraphicsEllipseItem *parent, QGraphicsScene * scene)
	: QGraphicsEllipseItem(parent,scene),_alpha(0),_parent(NULL),_alphaStep(5 * PI/360),_rDiff(0),_attached(NULL),_pixmap(NULL),_scale(0)
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

float ToDegree(float x) { return x*180/PI; }

void Circle::advance( int phase )
{
	if ( (!_parent) || (!phase) )
		return;
	for ( int i = 0; i < GFrameStep; i++)
	{
		// calculate position of tracked symbol
		// move yourself as a according to parent
		setPos( _rDiff * cos(_alpha*_scale), _rDiff * sin(_alpha*_scale) );
		setRotation(ToDegree(_alpha));
		_alpha += _alphaStep;
		GDrawing->addPoint(mapToItem(GDrawing,_point));
	}
}

void Circle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */)
{
	base::paint(painter,option,widget);
#if 0
	if (!_parent)
		return;
	painter->drawLine(0,0,getRange(),0);
#endif
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
#if 0 //_DEBUG
	Circle *c = new Circle(this,scene());
	c->setRange(DEBUG_RANGE);
#endif
	advance(1);	
}

void Circle::setRange( int range )
{
	setRect(-range,-range,range * 2, range *2);
	if (_parent)
		_rDiff = _parent->getRange() - getRange();
}

void Circle::restart()
{
	_alpha = 0;
	advance(1);
}