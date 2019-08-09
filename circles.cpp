#include "circles.h"
#include <qpainter>
#include <QGraphicsEllipseItem>

QGraphicsScene * GScene = NULL;
int GFrameStep = 1;// number of points per frame

Circles::Circles(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	GScene = new QGraphicsScene(this);
	ui.q_view->setScene(GScene);
  ui.q_or->setValue(100);
  ui.q_ir->setValue(70);

	QSize s = ui.q_view->size();
	GScene->setSceneRect( -100.0, -100.0, 200.0, 200.0 );
  GScene->addEllipse(0, 0, 30, 30);
	ui.q_view->setRenderHints( QPainter::Antialiasing );
	_timer.setInterval(100/3);
  
	QObject::connect(&_timer, SIGNAL(timeout()), GScene, SLOT(advance()));
	QObject::connect(ui.startButton, SIGNAL(clicked()), this, SLOT(changeTimer()));
	QObject::connect(ui.restartButton, SIGNAL(clicked()), this, SLOT(restart()));
	QObject::connect(ui.frameStep, SIGNAL(valueChanged(int)), this, SLOT(setFrameStep(int)));
  //GScene->render();
}

Circles::~Circles()
{
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
}

void Circles::setFrameStep( int frameStep )
{
	GFrameStep = frameStep;
}
