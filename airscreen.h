#ifndef AIRSCREEN_H
#define AIRSCREEN_H

#include <QWidget>
#include "udpsend.h"
namespace Ui {
class AirScreen;
}

class AirScreen : public QWidget
{
    Q_OBJECT

public:
    explicit AirScreen(QWidget *parent = nullptr);
    ~AirScreen();

private slots:
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_shang_clicked();

    void on_pushButton_zhong_clicked();

    void on_pushButton_xia_clicked();

private:
    Ui::AirScreen *ui;
};

#endif // AIRSCREEN_H
