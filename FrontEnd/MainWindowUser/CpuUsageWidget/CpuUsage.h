#ifndef CPU_USAGE_WIDGET_H
#define CPU_USAGE_WIDGET_H


#include <QtCharts/QtCharts>
#include <QtCharts/QChartView>


class CpuUsage : public QWidget {
    Q_OBJECT

public:
    explicit CpuUsage(QWidget* parent = nullptr);
    ~CpuUsage();

private slots:
    void updateGraph();

private:
    QChartView* chartView;
    QLineSeries* series;
    QValueAxis* axisX;
    QValueAxis* axisY;
    QTimer* timer;
    int x;
};

#endif // CPU_USAGE_WIDGET_H