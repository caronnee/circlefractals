#include "circles.h"
#include <qpainter>
#include <QGraphicsEllipseItem>
#include "drawing.h"

const int bigRange = 100;
const int smallRange = 70;

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
	_mainCircle = createCircle();
	_mainCircle->setRange(bigRange);
	GDrawing = new Drawing(_mainCircle);
	GDrawing->setZValue(100);
	Circle * c = createCircle();
	c->setRange(smallRange);
	c->setCross(QPointF(DEBUG_RANGE,0),QColor(0,0,0));
	_mainCircle->attach(c);
	ui._view->setRenderHints( QPainter::Antialiasing );
	_timer.setInterval(100/3);

	QObject::connect(&_timer, SIGNAL(timeout()), GScene, SLOT(advance()));
	QObject::connect(ui.startButton, SIGNAL(clicked()), this, SLOT(changeTimer()));
	QObject::connect(ui.restartButton, SIGNAL(clicked()), this, SLOT(restart()));
}

Circle * Circles::createCircle()
{
	Circle * ret = new Circle(0, GScene);
	QObject::connect(ui.restartButton, SIGNAL(clicked()), ret, SLOT(restart()));
	return ret;
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

void Circles::restart()
{
	GDrawing->clear();
}