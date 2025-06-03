#include "CpuUsage.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QDebug>
#include <QPainter>
#include "../../../BackEnd/GetSystemResources/GetCpuUsage/GetCpuUsage.h"

CpuUsage::CpuUsage(QWidget* parent) : QWidget(parent), x(0) {

    series = new QLineSeries();
    series->setName("CPU Usage");
    QPen pen(QColor("#00FFC6"));
    pen.setWidth(2);
    series->setPen(pen);


    QChart* chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->setBackgroundBrush(QBrush(QColor("#1e1e2f")));
    chart->setBackgroundPen(Qt::NoPen);


    axisX = new QValueAxis;
    axisX->setRange(0, 100);
    axisX->setLabelFormat("%d");
    axisX->setGridLineVisible(false);


    axisY = new QValueAxis;
    axisY->setRange(0, 100);
    axisY->setLabelFormat("%d%");
    axisY->setTitleText("CPU %");
    axisY->setLabelsBrush(QBrush(QColor("#CCCCCC")));
    axisY->setTitleBrush(QBrush(QColor("#CCCCCC")));
    axisY->setGridLineVisible(false);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);


    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(chartView);
    setLayout(layout);

    //1 sec refresh
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CpuUsage::updateGraph);
    timer->start(1000);


    for (int i = 0; i < 10; ++i) {
        series->append(i, 0);
    }
    x = 10;

    qDebug() << "[CPU Graph] Timer started.";
}

void CpuUsage::updateGraph() {
    static GetCpuUsage cpuUsage;
    float usage = cpuUsage.getCurrentUsage();

    qDebug() << "[CPU Usage] Current:" << usage;

    if (usage < 0.0f || usage > 100.0f) return;

    if (x > 100) {
        series->removePoints(0, series->count() - 100);
        axisX->setRange(x - 100, x);
    }

    series->append(x++, usage);
}

CpuUsage::~CpuUsage() {}