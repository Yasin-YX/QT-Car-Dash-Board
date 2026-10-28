#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QPoint>

namespace Ui {
class Map;
}

// 地图显示标签：支持鼠标滚轮缩放、双击复位（通过信号通知外部处理）
class MapLabel : public QLabel
{
    Q_OBJECT

public:
    explicit MapLabel(QWidget *parent = nullptr);

signals:
    void zoomInRequested();   // 滚轮向上 / 请求放大
    void zoomOutRequested();  // 滚轮向下 / 请求缩小
    void resetRequested();    // 双击 / 请求复位

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
};

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

private slots:
    void zoomIn();
    void zoomOut();
    void resetView();

private:
    void updateMap(); // 按当前缩放比例重新生成显示的地图

    Ui::Map *ui;
    QPixmap m_baseMap;    // 原始地图图片
    QPointF m_markerPos;  // 定位标记在地图上的坐标（原图像素）
    qreal m_fitScale;     // 适配窗口时的缩放比例
    qreal m_zoom;         // 当前缩放倍数（1.0 = 适配窗口）
};

#endif // MAP_H
