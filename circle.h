#ifndef CIRCLE_H
#define CIRCLE_H

#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>

#define DEBUG_RANGE 30

class Circle : public QObject, public QGraphicsEllipseItem
{
	Q_OBJECT

	typedef QGraphicsEllipseItem base;
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
	float _scale;
	QPointF _point;
	QColor _color;
	bool _end;
	public slots:
	void attach( Circle * at );
	virtual void advance(int phase);
public:
	QPointF getCentre();
	void setAlphaStep(float step);
	void setParent( Circle* param1 );
	int getRange();
	void setRange( int range );
	void setCross(QPointF point, QColor color);
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
public slots:
	void restart();
};

#endif // CIRCLE_H
