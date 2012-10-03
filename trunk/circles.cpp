#include "circles.h"
#include <qpainter>
#include <QGraphicsEllipseItem>
#include "drawing.h"

const int bigRange = 100;
const int smallRange = 30;

QGraphicsScene * GScene = NULL;
Drawing * GDrawing = NULL;

Circles::Circles(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	GScene = new QGraphicsScene(this);
	ui._view->setScene(GScene);
	QSize s = ui._view->size();
	GScene->setSceneRect( -100.0, -100.0, 200.0, 200.0 );
	_mainCircle = new Circle( 0, GScene );
	_mainCircle->setRange(bigRange);
	GDrawing = new Drawing(_mainCircle);
	GDrawing->setZValue(100);
	Circle * c = new Circle(0, GScene);
	c->setRange(smallRange);
	c->setCross(QPointF(5,5),QColor(0,0,0));
	_mainCircle->attach(c);
	QPoint point(10,10);
	ui._view->setRenderHints( QPainter::Antialiasing );
	_timer.setInterval(100/3);

	QObject::connect(&_timer, SIGNAL(timeout()), GScene, SLOT(advance()));
	QObject::connect(ui.startButton, SIGNAL(clicked()), this, SLOT(changeTimer()));
}

Circles::~Circles()
{
	delete _mainCircle;
}

void Circles::changeTimer()
{
	if ( !_timer.isActive() )
	{
		_timer.start();
		ui.startButton->setText("Pause");
		return;
	}
	_timer.stop();
	ui.startButton->setText("Start");
}
