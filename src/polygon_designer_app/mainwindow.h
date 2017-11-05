#ifndef mainwindow_h
#define mainwindow_h

#include <QMainWindow>
#include <QScopedPointer>
#include <QMouseEvent> 

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow 
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow() override;

private:
	void connectSignals() const;
	void setStatusbarText(const QString& text) const;

private:
    QScopedPointer<Ui::MainWindow> m_ui;
};

#endif
