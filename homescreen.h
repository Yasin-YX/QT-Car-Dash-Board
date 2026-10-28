#ifndef HOMESCREEN_H
#define HOMESCREEN_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QList>
#include "carcongig.h"
#include "udpsend.h"
#include "mylabel.h"
#include "WindSpeedControl.h"
namespace Ui {
class HomeScreen;
}

class HomeScreen : public QWidget
{
    Q_OBJECT

public:
    explicit HomeScreen(QWidget *parent = nullptr);
    ~HomeScreen();

    void setBackgroundImg(QString path);

signals:
    void changTheme();
    void changeChart();
    void changeMap();
private slots:
    void on_pushButton_chart_clicked();
    void on_pushButton_daohang_clicked();
    void changeTime();


    void on_pushButton_up_clicked();

    void on_pushButton_stop_clicked();

    void on_pushButton_down_clicked();

    void on_mediaStatusChanged(QMediaPlayer::MediaStatus status);
    void on_pushButton_suo_clicked();

    void on_pushButton_hou_clicked();

private:
    void getMusic();
private:
    Ui::HomeScreen *ui;
    QTimer* time;

    QMediaPlayer* player;

    QList<QString> paths;

    int count=0;

    myLabel* label;
};

#endif // HOMESCREEN_H
