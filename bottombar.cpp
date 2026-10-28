#include "bottombar.h"
#include "ui_bottombar.h"

BottomBar::BottomBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BottomBar)
{
    ui->setupUi(this);
     setAttribute(Qt::WA_StyledBackground); // 让 QWidget 子类能绘制样式表背景
    int temp = CarCongig::getCar().getTemperature();
    ui->label->setText(QString("%1℃").arg(temp));

    connect(&CarCongig::getCar(),&CarCongig::sendTemperature,this,
            [this](int temp)
    {
        ui->label->setText(QString("%1℃").arg(temp));
    });

}

BottomBar::~BottomBar()
{
    delete ui;
}

void BottomBar::on_pushButton_clicked()
{
    emit changeHome();
}

void BottomBar::on_pushButton_2_clicked()
{
    emit changeHome();
}

void BottomBar::on_pushButton_5_clicked()
{
    emit changeAir();
}

void BottomBar::on_pushButton_4_clicked()
{
    emit changeTheme();
}



void BottomBar::on_pushButton_6_clicked()
{
    int t = CarCongig::getCar().getTemperature();

    t = t-1;

    CarCongig::getCar().setTemperature(t);



}

void BottomBar::on_pushButton_7_clicked()
{
    int t = CarCongig::getCar().getTemperature();

    t = t+1;

    CarCongig::getCar().setTemperature(t);



}


