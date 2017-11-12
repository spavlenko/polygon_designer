#pragma once

#include <QMainWindow>
#include <memory>

class Designer;
class Polygon;

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
    void stopDrawing();

private:
    std::unique_ptr<Ui::MainWindow> m_ui;
    std::unique_ptr<Designer>       m_designer;
    std::unique_ptr<Polygon>       m_polygon;
};

