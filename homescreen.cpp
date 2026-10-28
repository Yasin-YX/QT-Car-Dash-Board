#include "homescreen.h"
#include "ui_homescreen.h"
//#include <QRandomGenerator>
#include <QDateTime>
#include <QTimer>

HomeScreen::HomeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeScreen)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); // 让 QWidget 子类能绘制样式表背景
    time = new QTimer(this);
    connect(time,&QTimer::timeout,this,&HomeScreen::changeTime);

    time->start(1);
    player = new QMediaPlayer(this);
    label = new myLabel(this);
    paths.push_back("D:/文件/OneDrive/Desktop/music/A1 TRIP _ 大籽 _ Lil E - 放空.mp3");
    paths.push_back("D:/文件/OneDrive/Desktop/music/Flo Rida - Whistle.mp3");
    paths.push_back("D:/文件/OneDrive/Desktop/music/金志文 - 自娱自乐.mp3");

    player->setMedia(QUrl::fromLocalFile(paths.at(0)));

    connect(player,&QMediaPlayer::mediaStatusChanged,this,&HomeScreen::on_mediaStatusChanged);

 ui->pushButton_stop->setIcon(QIcon("D:/文件/OneDrive/Desktop/background/main/play.png"));
 ui->pushButton_up->setIcon(QIcon("D:/文件/OneDrive/Desktop/background/main/previous.png"));
 ui->pushButton_down->setIcon(QIcon("D:/文件/OneDrive/Desktop/background/main/next.png"));

    if(CarCongig::getCar().getDoorLock())
    {
        ui->pushButton_suo->setIcon(QIcon(":/background/main/suo.png"));
    }
    if(CarCongig::getCar().getCarBox())
    {
        ui->pushButton_hou->setIcon(QIcon(":/background/main/box_lock.png"));
    }

//    int randomIndex = QRandomGenerator::global()->bounded(1, 10); // 生成 1~9

//    // 2. 拼出对应的图片路径
//    QString randomPath = QString(":/background/bg/bg%1.png").arg(randomIndex);

//    // 3. 调用你已有的 setBackgroundImg 设置随机背景
//    setBackgroundImg(randomPath);
}

HomeScreen::~HomeScreen()
{
    delete ui;
}

void HomeScreen::setBackgroundImg(QString path)
{
    QString style = QString("#home{ border-image: url(%1);}").arg(path);

    this->setStyleSheet(style);
}

void HomeScreen::on_pushButton_chart_clicked()
{
    emit changeChart();
}

void HomeScreen::on_pushButton_daohang_clicked()
{
    emit changeMap();
}

void HomeScreen::changeTime()
{
    QDateTime data = QDateTime::currentDateTime();
    QString t = data.toString("HH:mm:ss");
    QString y = data.toString("yyyy/MM/dd ddd");
    ui->label_3->setText(t+'\n'+y);
}

void HomeScreen::on_pushButton_up_clicked()
{
    count = (count-1+3)%3;
     player->setMedia(QUrl::fromLocalFile(paths.at(count)));
     ui->pushButton_stop->setIcon(QIcon("D:/文件/OneDrive/Desktop/background/main/pause.png"));
     player->play();
}

void HomeScreen::on_pushButton_stop_clicked()
{
    if(player->state() == QMediaPlayer::PlayingState)
    {
        player->pause();
        ui->pushButton_stop->setIcon(QIcon("D:/文件/OneDrive/Desktop/background/main/play.png"));
    }else if(player->state() == QMediaPlayer::PausedState||player->state() == QMediaPlayer::StoppedState)
    {
        player->play();
        ui->pushButton_stop->setIcon(QIcon("D:/文件/OneDrive/Desktop/background/main/pause.png"));
    }
}

void HomeScreen::on_pushButton_down_clicked()
{
    count = (count+1+3)%3;
     player->setMedia(QUrl::fromLocalFile(paths.at(count)));
    ui->pushButton_stop->setIcon(QIcon("D:/文件/OneDrive/Desktop/background/main/pause.png"));
    player->play();
}

void HomeScreen::on_mediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::LoadedMedia || status == QMediaPlayer::BufferedMedia)
    {
        getMusic();
    }
}

void HomeScreen::getMusic()
{
    QVariant title = player->metaData(QMediaMetaData::Title);//标题
    ui->label_2->setText(title.toString());

    // 先试封面，再试缩略图
    QVariant v = player->metaData(QMediaMetaData::CoverArtImage);//封面
    if (!v.isValid())
    {
        v = player->metaData(QMediaMetaData::ThumbnailImage);//缩略图
    }
    if (v.canConvert<QImage>())
    {
        QImage img = v.value<QImage>();
        if (!img.isNull())
        {
            ui->label_4->setPixmap(QPixmap::fromImage(img).scaled(
            ui->label_4->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
}

void HomeScreen::on_pushButton_suo_clicked()
{
   bool currentLock = CarCongig::getCar().getDoorLock();

   bool newLock = !currentLock ;

    CarCongig::getCar().setDoorlock(newLock);
    if(newLock)
    {
        ui->pushButton_suo->setIcon(QIcon(":/background/main/suo.png"));
        label->toastLabel("门已锁");
    }
    else
    {
        ui->pushButton_suo->setIcon(QIcon(":/background/main/unlock.png"));
        label->toastLabel("门已解锁");
    }
    UdpSend::getUdp().sendUdpJsonData();

}

void HomeScreen::on_pushButton_hou_clicked()
{
    bool currentLock = CarCongig::getCar().getCarBox();

    bool newLock = !currentLock ;

     CarCongig::getCar().setCarBox(newLock);
     if(newLock)
     {
         ui->pushButton_hou->setIcon(QIcon(":/background/main/box_lock.png"));
         label->toastLabel("后备箱已锁");
     }
     else
     {
         ui->pushButton_hou->setIcon(QIcon(":/background/main/box_open.png"));
         label->toastLabel("后备箱已解锁");
     }
    UdpSend::getUdp().sendUdpJsonData();
}
