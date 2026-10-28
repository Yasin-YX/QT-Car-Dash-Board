#include "chartpage.h"
#include "ui_chartpage.h"

ChartPage::ChartPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChartPage)
{
    ui->setupUi(this);
    chart = new QChart;
    m_line = new QLineSeries;
    m_avg = new QLineSeries;
    area = new QAreaSeries(m_line);

    axisX = new QDateTimeAxis;
    axisY = new QValueAxis;


    m_line = new QLineSeries;
    m_line->setName("我的");
    // 设置折线画笔：绿色，线宽2px
    QPen greenPen(QColor(76,175,80));
    greenPen.setWidth(2);

    m_line->setPen(greenPen);
    m_line->setPointsVisible(true);// 开启：显示折线上的数据圆点
    m_line->setPointLabelsVisible(true); //开启：显示每个数据点的数值标签
    m_line->setPointLabelsFormat("@yPoint");//标签格式：只展示Y轴数值
    m_line->setPointLabelsColor(QColor(60, 64, 70));// 数值文字颜色
    // 设置数据点标签字体大小
    QFont labelFont = font();
    labelFont.setPointSize(9);
    m_line->setPointLabelsFont(labelFont);

    // ------ 第二条折线：同车型均值线 ----
    m_avg = new QLineSeries;
    m_avg->setName("同车型均值");
    // 蓝色画笔，线宽2px
    QPen bluePen(QColor(58, 110, 235));
    bluePen.setWidth(2);
    m_avg->setPen(bluePen);

//    area = new QAreaSeries(m_line);

    chart->addSeries(m_line);
    chart->addSeries(m_avg);

    axisY->setRange(0, 10);// Y轴数值范围 0 ~ 10
    axisY->setTickCount(6);  // 刻度数量：0,2,4,6,8,10 共6个刻度
    axisY->setLabelFormat("%d");// 刻度标签格式：整数
    axisY->setGridLineColor(QColor(235, 238, 242));// 横向网格线颜色
    axisY->setLineVisible(false);// 隐藏Y轴轴线
    axisY->setLabelsColor(QColor(120, 126, 134)); // Y刻度文字颜色
    labelFont.setPointSize(10);
    axisY->setLabelsFont(labelFont);

    chart->addAxis(axisY,Qt::AlignLeft);
    m_line->attachAxis(axisY);
    m_avg->attachAxis(axisY);


    axisX->setFormat("MM-dd"); // 日期显示格式：月-日
    axisX->setTickCount(7); // X轴刻度数量
    axisX->setGridLineVisible(false);// 隐藏纵向网格线
    axisX->setLineVisible(false);// 隐藏X轴轴线
    axisX->setLabelsColor(QColor(120, 126, 134));// X刻度文字颜色
    axisX->setLabelsFont(labelFont);

    chart->addAxis(axisX,Qt::AlignBottom);
    m_line->attachAxis(axisX);
    m_avg->attachAxis(axisX);

    // 纵向渐变：从上到下（ObjectBoundingMode坐标 0=顶部，1=底部）
    QLinearGradient grad(0, 0, 0, 1); //纵向渐变
    grad.setCoordinateMode(QGradient::ObjectBoundingMode);
    grad.setColorAt(0.0, QColor(76, 175, 80, 80));// 顶部：半透明绿色
    grad.setColorAt(1.0, QColor(76, 175, 80, 0));// 底部：完全透明
    area->setBrush(grad);
    area->setPen(Qt::NoPen);// 关闭区域边框，避免和原折线重复描边

    chart->addSeries(area);

    area->attachAxis(axisY);
    area->attachAxis(axisX);

    chart->legend()->setVisible(true);

    ui->graphicsView->setChart(chart);

    // =======填充测试数据 =========
        QStringList dates;
        // X轴日期文本数组
        dates << "10-07" << "10-08" << "10-09" << "10-10"
                                  << "10-11" << "10-12" << "10-13";

        // 对应每个日期的Y值
        QVector<double> values;
        values << 5.5 << 4.0 << 3.8 << 4.0 << 4.1 << 4.0 << 4.1;

        m_line->clear();
        m_avg->clear();

        //日期字符串"MM-dd"转为时间戳
        qint64 minTime = 0, maxTime = 0;// 记录时间的最小、最大值，用来画均值横线和X轴范围
        // 循环：把 "MM-dd" 字符串转为毫秒时间戳，添加到折线
        for (int i = 0; i < dates.size(); ++i)
        {
             // 解析月-日，年份默认是系统当前年份！【坑：跨年时会出错】
            QDate d = QDate::fromString(dates.at(i), "MM-dd");
            qint64 t = QDateTime(d, QTime(0, 0)).toMSecsSinceEpoch();
             // 更新最小、最大时间戳
            if (i == 0) { minTime = t; maxTime = t; }
            minTime = qMin(minTime, t);
            maxTime = qMax(maxTime, t);

             // 给“我的”折线添加点
            m_line->append(t, values.at(i));
        }

        //均值横线：首尾两个点
        // 绘制均值水平线：取横轴最左、最右时间，Y固定5.9
        m_avg->append(minTime, 5.9);
        m_avg->append(maxTime, 5.9);

        //设置横轴范围
        // 重新获取横轴，设置X轴时间范围（限定在数据首尾时间）
        QDateTimeAxis *axisX = qobject_cast<QDateTimeAxis *>(chart->axes(Qt::Horizontal).first());
        if (axisX)
        {
            axisX->setMin(QDateTime::fromMSecsSinceEpoch(minTime));
            axisX->setMax(QDateTime::fromMSecsSinceEpoch(maxTime));
        }

}

ChartPage::~ChartPage()
{
    delete ui;
}
