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

    if (ui->radioButton->isChecked()) {
    ui->widget->clearGraphs();

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
    ui->widget->xAxis->setRange((a-20), (b+20));

    double minY = y[0], maxY = y[0];
    for (int i=1; i<N; i++)
    {
        if (y[i]<minY) minY = y[i];
        if (y[i]>maxY) maxY = y[i];
    }
    ui->widget->yAxis->setRange((minY-20), (maxY+20));//Для оси Oy
    } else if (ui->radioButton_2->isChecked()) {
            int N=5;
            QVector<double> x(N), y(N);

            x[0] = 1.0; y[0] = 2.0;
            x[1] = 4.0; y[1] = 1.0;
            x[2] = 3.0; y[2] = 0.0;
            x[3] = 0.5; y[3] = 2.2;
            x[4] = 1.5; y[4] = 0.7;

            ui->widget->clearGraphs();
            ui->widget->addGraph();
            ui->widget->graph(0)->setData(x, y);

            ui->widget->graph(0)->setPen(QColor(255, 0, 0, 255));
            ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
            ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

            ui->widget->xAxis->setLabel("x");
            ui->widget->yAxis->setLabel("y");

            ui->widget->xAxis->setRange(-1, 5);
            ui->widget->yAxis->setRange(-1, 3);
    } else if (ui->radioButton_3->isChecked()) {
        // set dark background gradient:
        QLinearGradient gradient(0, 0, 0, 400);
        gradient.setColorAt(0, QColor(90, 90, 90));
        gradient.setColorAt(0.38, QColor(105, 105, 105));
        gradient.setColorAt(1, QColor(70, 70, 70));
        ui->widget->setBackground(QBrush(gradient));

        // create empty bar chart objects:
        QCPBars *regen = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
        QCPBars *nuclear = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
        QCPBars *fossil = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
        regen->setAntialiased(false); // gives more crisp, pixel aligned bar borders
        nuclear->setAntialiased(false);
        fossil->setAntialiased(false);
        regen->setStackingGap(1);
        nuclear->setStackingGap(1);
        fossil->setStackingGap(1);
        // set names and colors:
        fossil->setName("Fossil fuels");
        fossil->setPen(QPen(QColor(111, 9, 176).lighter(170)));
        fossil->setBrush(QColor(111, 9, 176));
        nuclear->setName("Nuclear");
        nuclear->setPen(QPen(QColor(250, 170, 20).lighter(150)));
        nuclear->setBrush(QColor(250, 170, 20));
        regen->setName("Regenerative");
        regen->setPen(QPen(QColor(0, 168, 140).lighter(130)));
        regen->setBrush(QColor(0, 168, 140));
        // stack bars on top of each other:
        nuclear->moveAbove(fossil);
        regen->moveAbove(nuclear);

        // prepare x axis with country labels:
        QVector<double> ticks;
        QVector<QString> labels;
        ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7;
        labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        textTicker->addTicks(ticks, labels);
        ui->widget->xAxis->setTicker(textTicker);
        ui->widget->xAxis->setTickLabelRotation(60);
        ui->widget->xAxis->setSubTicks(false);
        ui->widget->xAxis->setTickLength(0, 4);
        ui->widget->xAxis->setRange(0, 8);
        ui->widget->xAxis->setBasePen(QPen(Qt::white));
        ui->widget->xAxis->setTickPen(QPen(Qt::white));
        ui->widget->xAxis->grid()->setVisible(true);
        ui->widget->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        ui->widget->xAxis->setTickLabelColor(Qt::white);
        ui->widget->xAxis->setLabelColor(Qt::white);

        // prepare y axis:
        ui->widget->yAxis->setRange(0, 12.1);
        ui->widget->yAxis->setPadding(5); // a bit more space to the left border
        ui->widget->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
        ui->widget->yAxis->setBasePen(QPen(Qt::white));
        ui->widget->yAxis->setTickPen(QPen(Qt::white));
        ui->widget->yAxis->setSubTickPen(QPen(Qt::white));
        ui->widget->yAxis->grid()->setSubGridVisible(true);
        ui->widget->yAxis->setTickLabelColor(Qt::white);
        ui->widget->yAxis->setLabelColor(Qt::white);
        ui->widget->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        // Add data:
        QVector<double> fossilData, nuclearData, regenData;
        fossilData  << 0.86*10.5 << 0.83*5.5 << 0.84*5.5 << 0.52*5.8 << 0.89*5.2 << 0.90*4.2 << 0.67*11.2;
        nuclearData << 0.08*10.5 << 0.12*5.5 << 0.12*5.5 << 0.40*5.8 << 0.09*5.2 << 0.00*4.2 << 0.07*11.2;
        regenData   << 0.06*10.5 << 0.05*5.5 << 0.04*5.5 << 0.06*5.8 << 0.02*5.2 << 0.07*4.2 << 0.25*11.2;
        fossil->setData(ticks, fossilData);
        nuclear->setData(ticks, nuclearData);
        regen->setData(ticks, regenData);

        // setup legend:
        ui->widget->legend->setVisible(true);
        ui->widget->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
        ui->widget->legend->setBrush(QColor(255, 255, 255, 100));
        ui->widget->legend->setBorderPen(Qt::NoPen);
        QFont legendFont = font();
        legendFont.setPointSize(10);
        ui->widget->legend->setFont(legendFont);
        ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    }
    ui->widget->replot();
}
