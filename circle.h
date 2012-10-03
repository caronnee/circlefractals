#ifndef CIRCLE_H
#define CIRCLE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>

class Circle : public QGraphicsEllipseItem
{
public:
	Circle(QGraphicsEllipseItem *parent, QGraphicsScene * scene);
	~Circle();

private:
	QPixmap * _pixmap;
	Circle * _parent;
	float _alphaStep;
	float _alpha;
	Circle * _attached;
	float _rDiff;
public slots:
	void attach( Circle * at );
	virtual void advance(int phase);
public:
	QPointF getCentre();
	void setAlphaStep(float step);
	void setParent( Circle* param1 );
	int getRange();
	void setRange( int range );
};

#endif // CIRCLE_H
