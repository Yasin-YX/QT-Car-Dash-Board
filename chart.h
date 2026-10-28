#ifndef CHART_H
#define CHART_H

#include <QWidget>
#include <QChar>
#include <QLineSeries>
#include <QValueAxis>
#include <QDateTimeAxis>
#include <QDateTime>
#include <QAreaSeries>
QT_BEGIN_NAMESPACE
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class chart;
}

class chart : public QWidget
{
    Q_OBJECT

public:
    explicit chart(QWidget *parent = nullptr);
    ~chart();


private:
    Ui::chart *ui;

    QLineSeries* m_line;
    QLineSeries* m_avg;
    QAreaSeries* area;

    QChart* Achart;
    QDateTimeAxis* axisX;
    QValueAxis* axisY;
};

#endif // CHART_H
