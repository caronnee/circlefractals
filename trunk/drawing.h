#ifndef DRAWED_H
#define DRAWED_H

#include <QGraphicsItem>
#include <QPainter>
#include <QList>

class Drawing : public QGraphicsItem
{
	int _lastPoint;
	QList<QPointF> _points;
public:
	Drawing(QGraphicsItem *parent);
	QRectF boundingRect(void) const;
	void repaint();
	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget /* = 0 */);
	~Drawing();
	void addPoint( const QPointF & newPos );
private:
	
};

#endif // DRAWED_H
