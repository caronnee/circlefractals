#ifndef CIRCLES_H
#define CIRCLES_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "ui_circles.h"

class Circles : public QMainWindow
{
	Q_OBJECT

	QTimer _timer;
	// pixmap on scene
public:
	Circles(QWidget *parent = 0);
	~Circles();

private:
	Ui::CirclesClass ui;
public slots:
	void changeTimer();
	void restart();
	void setFrameStep(int frameStep);
};

#endif // CIRCLES_H
