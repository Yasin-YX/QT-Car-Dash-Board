#include "map.h"
#include "ui_map.h"

#include <QPainter>
#include <QPainterPath>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <QDebug>

// 绘制定位图钉（尖角对准 pos，固定屏幕大小）
static void drawPin(QPainter &painter, const QPointF &pos)
{
    painter.setRenderHint(QPainter::Antialiasing);

    // 红色圆头 + 底部尖角
    QPainterPath path;
    path.addEllipse(QPointF(pos.x(), pos.y() - 20), 10, 10);
    path.moveTo(pos.x() - 5, pos.y() - 14);
    path.lineTo(pos.x() + 5, pos.y() - 14);
    path.lineTo(pos.x(), pos.y());
    path.closeSubpath();

    painter.setPen(QPen(Qt::white, 1.5));
    painter.setBrush(QColor(230, 30, 30));
    painter.drawPath(path);

    // 中间白色圆点
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawEllipse(QPointF(pos.x(), pos.y() - 20), 4, 4);
}

// ==================== 地图标签 ====================

MapLabel::MapLabel(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
}

void MapLabel::wheelEvent(QWheelEvent *event)
{
    // 滚轮向上放大，向下缩小
    if (event->angleDelta().y() > 0)
        emit zoomInRequested();
    else
        emit zoomOutRequested();
    event->accept();
}

void MapLabel::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit resetRequested(); // 双击复位
}

// ==================== 地图页面 ====================

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map),
    m_markerPos(853, 640), // 地图中心（原图 1707x1280 的中心）
    m_zoom(1.0)
{
    ui->setupUi(this);

    m_baseMap.load(":/background/main/map.png");
    if (m_baseMap.isNull())
    {
        qDebug() << "地图图片加载失败";
        return;
    }

    // 适配窗口时的缩放比例：整张地图塞进标签，保持比例
    qreal w = qreal(ui->label_map->width())  / m_baseMap.width();
    qreal h = qreal(ui->label_map->height()) / m_baseMap.height();
    m_fitScale = qMin(w, h);

    // 信号槽：按钮 + 标签（滚轮/双击）
    connect(ui->pushButton_zoomin,  &QPushButton::clicked, this, &Map::zoomIn);
    connect(ui->pushButton_zoomout, &QPushButton::clicked, this, &Map::zoomOut);
    connect(ui->label_map, &MapLabel::zoomInRequested,  this, &Map::zoomIn);
    connect(ui->label_map, &MapLabel::zoomOutRequested, this, &Map::zoomOut);
    connect(ui->label_map, &MapLabel::resetRequested,   this, &Map::resetView);

    updateMap();
}

Map::~Map()
{
    delete ui;
}

void Map::zoomIn()
{
    m_zoom *= 1.25;
    if (m_zoom > 8.0) m_zoom = 8.0;
    updateMap();
}

void Map::zoomOut()
{
    m_zoom *= 0.8;
    if (m_zoom < 0.1) m_zoom = 0.1;
    updateMap();
}

void Map::resetView()
{
    m_zoom = 1.0; // 回到适配窗口
    updateMap();
}

void Map::updateMap()
{
    if (m_baseMap.isNull()) return;

    qreal s = m_fitScale * m_zoom;
    QSize size(int(m_baseMap.width() * s), int(m_baseMap.height() * s));

    // 按比例缩放地图
    QPixmap scaled = m_baseMap.scaled(size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // 把定位标记画到地图上（固定屏幕大小，位置随地图缩放）
    QPainter painter(&scaled);
    drawPin(painter, QPointF(m_markerPos.x() * s, m_markerPos.y() * s));
    painter.end();

    ui->label_map->setPixmap(scaled);
}
