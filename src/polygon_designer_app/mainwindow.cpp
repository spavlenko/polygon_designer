#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMouseEvent> 


MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
	connectSignals();
}

MainWindow::~MainWindow()
{

}

void MainWindow::connectSignals() const
{
	QObject::connect(m_ui->m_actionExit, &QAction::triggered, this, &QMainWindow::close);
	
	QObject::connect(m_ui->m_drawinArea, &DrawingArea::mouseMoved, [this](const QPoint& p)
	{
		setStatusbarText(QString(tr("x=%0, y=%1").arg(p.x()).arg(p.y())));
	});

	QObject::connect(m_ui->m_drawinArea, &DrawingArea::mouseLeftArea, [this]()
	{
		setStatusbarText("");
	});
	
	const Polygon p1({ { 0, 0 }, { 0, 50 }, { 90, 150 }, {100, 90 }, { 100, 50 }, { 20, 20 } });
	m_ui->m_drawinArea->setRenderer(std::make_unique<PolygonRenderer>(p1));
}

void MainWindow::setStatusbarText(const QString& text) const
{
	m_ui->m_statusBar->showMessage(text);
}
