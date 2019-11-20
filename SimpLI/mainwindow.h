#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qcustomplot.h>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    //QCPCurve *verticalLine;     // Объявляем объект для вертикальной линии
    //QCPItemTracer *tracer;      // Трасировщик по точкам графика

private:
    Ui::MainWindow *ui;
    void slotMousePress(QMouseEvent * event);
    void slotMouseMove(QMouseEvent * event);
};
#endif // MAINWINDOW_H
