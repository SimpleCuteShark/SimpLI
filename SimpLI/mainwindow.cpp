#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qcustomplot.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString str_x = ui->lineEdit_x->text();
    QString str_y = ui->lineEdit_y->text();
    bool ok;
    double a = str_x.toDouble(&ok);     //Начало интервала, где рисуем график по оси Ox
    double b = str_y.toDouble(&ok);     //Конец интервала, где рисуем график по оси Ox
    QCPItemTracer *tracer = new QCPItemTracer(ui->widget);

    if (ui->radioButton->isChecked()) {
    //Рисуем график y=x*x

    //Начало интервала, где рисуем график по оси Ox
    //Конец интервала, где рисуем график по оси Ox
    double h = 0.01; //Шаг, с которым будем пробегать по оси Ox

    int N=(b-a)/h + 2; //Вычисляем количество точек, которые будем отрисовывать
    QVector<double> x(N), y(N); //Массивы координат точек

    //Вычисляем наши данные
    int i=0;
    for (double X=a; X<=b; X+=h)//Пробегаем по всем точкам
    {
        x[i] = X;
        y[i] = X*X;//Формула нашей функции
        i++;
    }

    ui->widget->clearGraphs();//Если нужно, но очищаем все графики
    //Добавляем один график в widget
    ui->widget->addGraph();
    //Говорим, что отрисовать нужно график по нашим двум массивам x и y
    ui->widget->graph(0)->setData(x, y);

    //Подписываем оси Ox и Oy
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    //Установим область, которая будет показываться на графике
    ui->widget->xAxis->setRange(a, b);//Для оси Ox

    //Для показа границ по оси Oy сложнее, так как надо по правильному
    //вычислить минимальное и максимальное значение в векторах
    double minY = y[0], maxY = y[0];
    for (int i=1; i<N; i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y[i]>maxY) maxY = y[i];
    }
    ui->widget->yAxis->setRange(minY, maxY);//Для оси Oy
    } else if (ui->radioButton_2->isChecked()) {
            //Рисуем точки

            int N=5; //Допустим, что у нас пять точек
            QVector<double> x(N), y(N); //Массивы координат точек

            //Зададим наши точки
            x[0] = 1.0; y[0] = 2.0;
            x[1] = 4.0; y[1] = 1.0;
            x[2] = 3.0; y[2] = 0.0;
            x[3] = 0.5; y[3] = 2.2;
            x[4] = 1.5; y[4] = 0.7;

            ui->widget->clearGraphs();//Если нужно, но очищаем все графики
            //Добавляем один график в widget
            ui->widget->addGraph();
            //Говорим, что отрисовать нужно график по нашим двум массивам x и y
            ui->widget->graph(0)->setData(x, y);

            ui->widget->graph(0)->setPen(QColor(50, 50, 50, 255));//задаем цвет точки
            ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);//убираем линии
            //формируем вид точек
            ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

            //Подписываем оси Ox и Oy
            ui->widget->xAxis->setLabel("x");
            ui->widget->yAxis->setLabel("y");

            //Установим область, которая будет показываться на графике
            ui->widget->xAxis->setRange(-1, 5);//Для оси Ox
            ui->widget->yAxis->setRange(-1, 3);//Для оси Oy
    } else if (ui->radioButton_3->isChecked()) {
        // Инициализируем вертикальную линию
        //verticalLine = new QCPCurve(ui->widget->xAxis, ui->widget->yAxis);

        // Подключаем сигналы событий мыши от полотна графика к слотам для их обработки
        connect(ui->widget, &QCustomPlot::mousePress, this, &MainWindow::slotMousePress);
        connect(ui->widget, &QCustomPlot::mouseMove, this, &MainWindow::slotMouseMove);

        // создаём вектора для вертикальной линии
        //QVector<double> x(2) , y(2);
       //     x[0] = 0;
         //   y[0] = -50;
        //    x[1] = 0;
         //   y[1] = 50;

        //ui->widget->plottable(verticalLine);    // Добавляем линию на полотно
        //ui->widget->addLayer(verticalLine)
        //verticalLine->setName("Vertical");      // Устанавливаем ей наименование
        //verticalLine->setData(x, y);            // И устанавливаем координаты

        // создаём вектора для графика
        QVector<double> x1(5) , y1(5);
            x1[0] = -45;
            y1[0] = -43;
            x1[1] = 46;
            y1[1] = 42;
            x1[2] = -25;
            y1[2] = -24;
            x1[3] = -12;
            y1[3] = 10;
            x1[4] = 25;
            y1[4] = 26;

        // Добавляем график на полотно
        ui->widget->addGraph(ui->widget->xAxis, ui->widget->yAxis);
        ui->widget->graph(0)->setData(x1,y1);     // Устанавливаем координаты точек графика

        // Инициализируем трассировщик
        //QCPItemTracer *tracer = new QCPItemTracer(ui->widget);
        tracer->setGraph(ui->widget->graph(0));   // Трассировщик будет работать с графиком

        // Подписываем оси координат
        ui->widget->xAxis->setLabel("x");
        ui->widget->yAxis->setLabel("y");

        // Устанавливаем максимальные и минимальные значения координат
        ui->widget->xAxis->setRange(-50,50);
        ui->widget->yAxis->setRange(-50,50);
    }
    //И перерисуем график на нашем widget
    ui->widget->replot();
}
void MainWindow::slotMousePress(QMouseEvent *event)
{
    if (ui->radioButton_3->isChecked()) {
    QCPItemTracer *tracer = new QCPItemTracer(ui->widget);
    // Определяем координату X на графике, где был произведён клик мышью
    double coordX = ui->widget->xAxis->pixelToCoord(event->pos().x());

        // Подготавливаем координаты по оси X для переноса вертикальной линии
        //QVector<double> x(2), y(2);
        //x[0] = coordX;
        //y[0] = -50;
        //x[1] = coordX;
        //y[1] = 50;

        // Устанавливаем новые координаты
        //verticalLine->setData(x, y);

        // По координате X клика мыши определим ближайшие координаты для трассировщика
        tracer->setGraphKey(coordX);

        // Выводим координаты точки графика, где установился трассировщик, в lineEdit
        ui->widget->replot(); // Перерисовываем содержимое полотна графика
    }
}

void MainWindow::slotMouseMove(QMouseEvent *event)
{
    /* Если при передвижении мыши, ей кнопки нажаты,
     * то вызываем отработку координат мыши
     * через слот клика
     * */
    if(QApplication::mouseButtons()) slotMousePress(event);
}
