#include "airscreen.h"
#include "ui_airscreen.h"

#include "carcongig.h"

AirScreen::AirScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AirScreen)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); // 让 QWidget 子类能绘制样式表背景

    int temp = CarCongig::getCar().getTemperature();
    ui->label_2->setText(QString("%1℃").arg(temp));
    ui->label->setText(QString("%1℃").arg(temp+1));
    ui->label_3->setText(QString("%1℃").arg(temp-1));
    connect(&CarCongig::getCar(),&CarCongig::sendTemperature,this,
            [this](int temp)
    {
        ui->label_2->setText(QString("%1℃").arg(temp));

        if(temp==16)
            ui->label_3->setText("L0");
        else
            ui->label_3->setText(QString("%1℃").arg(temp-1));
        if(temp==30)
            ui->label->setText("Hi");
        else
            ui->label->setText(QString("%1℃").arg(temp+1));

    });
    if(CarCongig::getCar().getIcon())
    {
        ui->pushButton->setIcon(QIcon(":/background/air/auto_icon.png"));
    }
    if(CarCongig::getCar().getBtn())
    {
        ui->pushButton_2->setIcon(QIcon(":/background/air/wind_btn_lock.png"));
    }
    if(CarCongig::getCar().getSnow())
    {
        ui->pushButton_3->setIcon(QIcon(":/background/air/snow_icon.png"));
    }
    if(CarCongig::getCar().getLoop())
    {
        ui->pushButton_4->setIcon(QIcon(":/background/air/loop_lock.png"));
    }
    if(CarCongig::getCar().getWind())
    {
        ui->pushButton_5->setIcon(QIcon(":/background/air/windding.png"));
    }
    if(CarCongig::getCar().getWram())
    {
        ui->pushButton_6->setIcon(QIcon(":/background/air/wram.png"));
    }
    if(CarCongig::getCar().getWram())
    {
        QPixmap pix(":/background/air/up_no.png");
        ui->label_9->setPixmap(pix);
    }
    if(CarCongig::getCar().getWram())
    {
        QPixmap pix(":/background/air/mid_no.png");
        ui->label_10->setPixmap(pix);
    }
    if(CarCongig::getCar().getWram())
    {
        QPixmap pix(":/background/air/down_no.png");
        ui->label_11->setPixmap(pix);
    }
    int level = CarCongig::getCar().getLevel();
    ui->widget->setLevel(level);


}

AirScreen::~AirScreen()
{
    delete ui;
}

void AirScreen::on_pushButton_7_clicked()
{
    int t = CarCongig::getCar().getTemperature();

    t = t+1;

    CarCongig::getCar().setTemperature(t);
}

void AirScreen::on_pushButton_8_clicked()
{
    int t = CarCongig::getCar().getTemperature();

    t = t-1;

    CarCongig::getCar().setTemperature(t);

}

void AirScreen::on_pushButton_clicked()
{
    bool currentLock = CarCongig::getCar().getIcon();

    bool newLock = !currentLock ;

     CarCongig::getCar().setIcon(newLock);
     if(newLock)
     {
         ui->pushButton->setIcon(QIcon(":/background/air/auto_icon.png"));
     }
     else
     {
         ui->pushButton->setIcon(QIcon(":/background/air/auto_icon_select.png"));
     }
     UdpSend::getUdp().sendUdpJsonData();
}

void AirScreen::on_pushButton_2_clicked()
{
    bool currentLock = CarCongig::getCar().getBtn();

    bool newLock = !currentLock ;

     CarCongig::getCar().setBtn(newLock);
     if(newLock)
     {
         ui->pushButton_2->setIcon(QIcon(":/background/air/wind_btn_lock.png"));
     }
     else
     {
         ui->pushButton_2->setIcon(QIcon(":/background/air/wind_btn_open.png"));
     }
     UdpSend::getUdp().sendUdpJsonData();
}

void AirScreen::on_pushButton_3_clicked()
{
    bool currentLock = CarCongig::getCar().getSnow();

    bool newLock = !currentLock ;

     CarCongig::getCar().setSnow(newLock);
     if(newLock)
     {
         ui->pushButton_3->setIcon(QIcon(":/background/air/snow_icon.png"));
     }
     else
     {
         ui->pushButton_3->setIcon(QIcon(":/background/air/snow_icon_select.png"));
     }
     UdpSend::getUdp().sendUdpJsonData();
}

void AirScreen::on_pushButton_4_clicked()
{
    bool currentLock = CarCongig::getCar().getLoop();

    bool newLock = !currentLock ;

     CarCongig::getCar().setLoop(newLock);
     if(newLock)
     {
         ui->pushButton_4->setIcon(QIcon(":/background/air/loop_lock.png"));
     }
     else
     {
         ui->pushButton_4->setIcon(QIcon(":/background/air/loop_open.png"));
     }
     UdpSend::getUdp().sendUdpJsonData();
}

void AirScreen::on_pushButton_5_clicked()
{
    bool currentLock = CarCongig::getCar().getWind();

    bool newLock = !currentLock ;

     CarCongig::getCar().setWind(newLock);
     if(newLock)
     {
         ui->pushButton_5->setIcon(QIcon(":/background/air/windding.png"));
     }
     else
     {
         ui->pushButton_5->setIcon(QIcon(":/background/air/windding_select.png"));
     }
     UdpSend::getUdp().sendUdpJsonData();
}

void AirScreen::on_pushButton_6_clicked()
{
    bool currentLock = CarCongig::getCar().getWram();

    bool newLock = !currentLock ;

     CarCongig::getCar().setWram(newLock);
     if(newLock)
     {
         ui->pushButton_6->setIcon(QIcon(":/background/air/wram.png"));
     }
     else
     {
         ui->pushButton_6->setIcon(QIcon(":/background/air/wram_seelct.png"));
     }
     UdpSend::getUdp().sendUdpJsonData();
}

void AirScreen::on_pushButton_shang_clicked()
{
    bool currentLock = CarCongig::getCar().getWram();

    bool newLock = !currentLock ;

     CarCongig::getCar().setWram(newLock);
     QPixmap pix(":/background/air/up_no.png");
     QPixmap pix2(":/background/air/up_open.png");
     if(newLock)
     {
         ui->label_9->setPixmap(pix2);
         ui->label_9->setScaledContents(true);
     }
     else
     {
         ui->label_9->setPixmap(pix);
         ui->label_9->setScaledContents(true);
     }
     UdpSend::getUdp().sendUdpJsonData();
}

void AirScreen::on_pushButton_zhong_clicked()
{
    bool currentLock = CarCongig::getCar().getWram();

    bool newLock = !currentLock ;

     CarCongig::getCar().setWram(newLock);
     QPixmap pix(":/background/air/mid_no.png");
     QPixmap pix2(":/background/air/mid_open.png");
     if(newLock)
     {
         ui->label_10->setPixmap(pix2);
//         ui->label_10->setScaledContents(true);
     }
     else
     {
         ui->label_10->setPixmap(pix);
//         ui->label_10->setScaledContents(true);
     }
     UdpSend::getUdp().sendUdpJsonData();
}

void AirScreen::on_pushButton_xia_clicked()
{
    bool currentLock = CarCongig::getCar().getWram();

    bool newLock = !currentLock ;

     CarCongig::getCar().setWram(newLock);
     QPixmap pix(":/background/air/down_no.png");
     QPixmap pix2(":/background/air/down_open.png");
     if(newLock)
     {
         ui->label_11->setPixmap(pix2);
//         ui->label_11->setScaledContents(true);
     }
     else
     {
         ui->label_11->setPixmap(pix);
//         ui->label_11->setScaledContents(true);
     }
     UdpSend::getUdp().sendUdpJsonData();
}
