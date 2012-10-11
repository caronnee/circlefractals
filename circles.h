#ifndef CIRCLES_H
#define CIRCLES_H

#include <QtGui/QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "circle.h"
#include "ui_circles.h"

class Circles : public QMainWindow
{
	Q_OBJECT

	QTimer _timer;
	Circle *_mainCircle;
	// pixmap on scene
public:
	Circles(QWidget *parent = 0, Qt::WFlags flags = 0);
	~Circles();

private:
	Ui::CirclesClass ui;
public slots:
	void changeTimer();
	void restart();
	Circle * createCircle();
	void setFrameStep(int frameStep);
};

#endif // CIRCLES_H
