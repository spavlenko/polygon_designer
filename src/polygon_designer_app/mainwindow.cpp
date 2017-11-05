#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
	ConnectSignals();
}

MainWindow::~MainWindow()
{
}

void MainWindow::ConnectSignals() const
{
	QObject::connect(m_ui->m_actionExit, &QAction::triggered, this, &QMainWindow::close);
}
