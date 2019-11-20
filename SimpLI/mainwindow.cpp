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
    ui->widget->clearGraphs();
    ui->widget->clearItems();
    ui->widget->clearPlottables();
    ui->widget->clearMask();
    ui->widget->clearFocus();
    /*
    QString str_x = ui->lineEdit_x->text();
    QString str_y = ui->lineEdit_y->text();
    bool ok;
    double a = str_x.toDouble(&ok);     //Начало интервала, где рисуем график по оси Ox
    double b = str_y.toDouble(&ok);     //Конец интервала, где рисуем график по оси Ox
    */
    int cout = 10;
    QVector<double> x(cout), y(cout);
    //x << 1 << 2.3 << 3.4 << 0.2 << 5.8 << 4.2 << 7.2 << 8.8 << 9 << 10;
    //y << 0.5 << 3.3 << 2.4 << 0.2 << 4.8 << 4.2 << 5.2 << 6.8 << 7 << 10;
    x[0] = 0; y[0] = 0;
    for (int i=1; i<cout; i++) {
        x[i] = x[i-1] + 1;
        y[i] = y[i-1] + 1;
    }
    double minY = y[0], maxY = y[0];
    double minX = x[0], maxX = x[0];
    for (int i=1; i<cout; i++)
    {
        if (y[i]<minY) minY = y[i]*1.5;
        if (y[i]>maxY) maxY = y[i]*1.5;
        if (x[i]<minX) minX = x[i]*1.5;
        if (x[i]>maxX) maxX = x[i]*1.5;
    }
    ui->widget->xAxis->setRange(minX, maxX);
    ui->widget->yAxis->setRange(minY, maxY);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");

    if (ui->radioButton->isChecked()) {
        ui->widget->addGraph();
        ui->widget->graph(0)->setData(x, y);
    } else if (ui->radioButton_2->isChecked()) {
        ui->widget->addGraph();
        ui->widget->graph(0)->setData(x, y);

        ui->widget->graph(0)->setPen(QColor(255, 0, 0, 255));
        ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

    } else if (ui->radioButton_3->isChecked()) {

        // set dark background gradient:
        QLinearGradient gradient(0, 0, 0, 400);
        gradient.setColorAt(0, QColor(90, 90, 90));
        gradient.setColorAt(0.38, QColor(105, 105, 105));
        gradient.setColorAt(1, QColor(70, 70, 70));
        ui->widget->setBackground(QBrush(gradient));

        // create empty bar chart objects:
        QCPBars *data = new QCPBars(ui->widget->xAxis, ui->widget->yAxis);
        data->setName("Regenerative");
        data->setPen(QPen(QColor(0, 0, 255).lighter(130)));
        data->setBrush(QColor(0, 0, 122));

        // prepare x axis with country labels:
        QVector<double> ticks;
        //QVector<QString> labels;
        ticks << 1 << 2 << 3 << 4 << 5 << 6 << 7 << 8 << 9 << 10;
        //labels << "USA" << "Japan" << "Germany" << "France" << "UK" << "Italy" << "Canada";
        QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
        //textTicker->addTicks(ticks, labels);
        ui->widget->xAxis->setTicker(textTicker);
        ui->widget->xAxis->setTickLabelRotation(60);
        //ui->widget->xAxis->setSubTicks(false);
        //ui->widget->xAxis->setTickLength(0, 4);
        ui->widget->xAxis->setRange(minX, maxX);
        ui->widget->xAxis->setBasePen(QPen(Qt::white));
        ui->widget->xAxis->setTickPen(QPen(Qt::white));
        //ui->widget->xAxis->grid()->setVisible(true);
        //ui->widget->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
        ui->widget->xAxis->setTickLabelColor(Qt::white);
        ui->widget->xAxis->setLabelColor(Qt::white);

        // prepare y axis:
        ui->widget->yAxis->setRange(minY, maxY);
        //ui->widget->yAxis->setPadding(5); // a bit more space to the left border
        //ui->widget->yAxis->setLabel("Power Consumption in\nKilowatts per Capita (2007)");
        ui->widget->yAxis->setBasePen(QPen(Qt::white));
        ui->widget->yAxis->setTickPen(QPen(Qt::white));
        ui->widget->yAxis->setSubTickPen(QPen(Qt::white));
        //ui->widget->yAxis->grid()->setSubGridVisible(true);
        ui->widget->yAxis->setTickLabelColor(Qt::white);
        ui->widget->yAxis->setLabelColor(Qt::white);
        //ui->widget->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
        //ui->widget->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

        data->setData(ticks, x);
    }
    ui->widget->replot();
}
