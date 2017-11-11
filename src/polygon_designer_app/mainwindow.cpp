#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygon_designer_lib/designer.h"

#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    connectSignals();
    startDrawing();
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
}

void MainWindow::setStatusbarText(const QString& text) const
{
    m_ui->m_statusBar->showMessage(text);
}

void MainWindow::startDrawing()
{
    m_designer = std::make_unique<Designer>();

    QObject::connect(m_ui->m_drawinArea, &DrawingArea::mouseMoved, m_designer.get(), &Designer::setPendingPointPosition);
    QObject::connect(m_ui->m_drawinArea, &DrawingArea::mouseLeftArea, m_designer.get(), &Designer::discardPendingPoint);
    QObject::connect(m_ui->m_drawinArea, &DrawingArea::mousePressed, m_designer.get(), &Designer::acceptPendingPoint);

    ///todo: implement it in a correct way
    QObject::connect(&m_designer->getDrawingFigure(), &Figure::changed, [&]() {m_ui->m_drawinArea->update(); });

    QObject::connect(m_designer.get(), &Designer::figureAcceptable, m_ui->m_compleateBtn, &QWidget::setEnabled);

    m_ui->m_drawinArea->setRenderer(std::make_unique<PolygonRenderer>(m_designer->getDrawingFigure()));
}
