#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polygon_designer_lib/designer.h"

#include <QMouseEvent>
#include <QMessageBox>
#include <QDebug>
#include <QString>

namespace
{
    namespace Const
    {
        const auto windowsTitle = "Designer";
    }
}

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    setWindowTitle(tr(Const::windowsTitle));
    connectSignals();
    startDrawing();
}

MainWindow::~MainWindow()
{
}

void MainWindow::connectSignals() const
{
    QObject::connect(m_ui->m_actionExit, &QAction::triggered, this, &QMainWindow::close);
    QObject::connect(m_ui->m_actionAbout, &QAction::triggered, this, &MainWindow::about);

    QObject::connect(m_ui->m_drawinArea, &DrawingArea::mouseMoved, [this](const QPoint& p)
    {
        if (isDesignState())
            setStatusbarText(QString(tr("x=%0, y=%1").arg(p.x()).arg(p.y())));
    });

    QObject::connect(m_ui->m_drawinArea, &DrawingArea::mouseLeftArea, [this]()
    {
        if(isDesignState())
            clearStatusbar();
    });

    QObject::connect(m_ui->m_resetBtn, &QAbstractButton::clicked, this, &MainWindow::startDrawing);
    QObject::connect(m_ui->m_completeBtn, &QAbstractButton::clicked, this, &MainWindow::stopDrawing);

}

void MainWindow::setStatusbarText(const QString& text) const
{
    m_ui->m_statusBar->showMessage(text);
}

void MainWindow::clearStatusbar() const
{
    setStatusbarText("");
}

void MainWindow::startDrawing()
{
    clearStatusbar();
    m_designer = std::make_unique<Designer>();

    QObject::connect(m_ui->m_drawinArea, &DrawingArea::mouseMoved,    m_designer.get(), &Designer::setPendingPointPosition);
    QObject::connect(m_ui->m_drawinArea, &DrawingArea::mouseLeftArea, m_designer.get(), &Designer::discardPendingPoint);
    QObject::connect(m_ui->m_drawinArea, &DrawingArea::mousePressed,  m_designer.get(), &Designer::acceptPendingPoint);

    QObject::connect(&m_designer->getDrawingFigure(), &Figure::changed
        , m_ui->m_drawinArea, static_cast<void (QWidget::*)(void)>(&QWidget::update));

    QObject::connect(m_designer.get(), &Designer::figureChanged, m_ui->m_completeBtn, &QWidget::setEnabled);

    auto strategy = std::make_unique<EditingPolygonRenderingStrategy>();

    QObject::connect(m_designer.get(), &Designer::pendingPointIndexChanged
        , strategy.get(), &EditingPolygonRenderingStrategy::setPendingVertex);

    QObject::connect(m_designer.get(), &Designer::figureChanged
        , strategy.get(), &EditingPolygonRenderingStrategy::polygonCnahged);

    m_ui->m_drawinArea->setRenderer(std::make_unique<PolygonRenderer>(m_designer->getDrawingFigure(), std::move(strategy)));

    m_polygon.reset();
}

void MainWindow::stopDrawing()
{
    Q_ASSERT(m_designer);

    if(!m_designer)
    {
        qDebug() << "Incorrect call of stop drawing. Error: no active designer.";

        return;
    }

    m_ui->m_completeBtn->setDisabled(true);

    m_polygon = std::make_unique<Polygon>(m_designer->getDrawingFigure());
    m_designer.reset();

    Renderer::Ptr renderer = std::make_unique<PolygonRenderer>(*m_polygon
        , std::make_unique<PolygonDefaultRenderingStrategy>());

    m_ui->m_drawinArea->setRenderer(std::move(renderer));

    QString statusText(tr("Built a polygon. It %0, it's area = %1"));

    const bool isConvex = ::isConvex(*m_polygon);
    const QString convexity = isConvex ? tr("is convex") : tr("is not convex");

    statusText = statusText.arg(convexity).arg(::calculateArea(*m_polygon));

    setStatusbarText(statusText);
}

void MainWindow::about()
{
    QMessageBox aboutDlg(this);
    aboutDlg.setWindowTitle(QString(tr("About %0")).arg(tr(Const::windowsTitle)));
    aboutDlg.setText(tr("This is a simple application, which was written"
            "which was written as a task in a scope of a interview."));

    aboutDlg.exec();
}

bool MainWindow::isDesignState() const
{
    return m_designer != nullptr;
}
