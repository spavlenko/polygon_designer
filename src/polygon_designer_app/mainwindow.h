#ifndef mainwindow_h
#define mainwindow_h

#include <QMainWindow>
#include <memory>

class Designer;

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

    void startDrawing();

private:
    std::unique_ptr<Ui::MainWindow> m_ui;
    std::unique_ptr<Designer>       m_designer;
};

#endif
