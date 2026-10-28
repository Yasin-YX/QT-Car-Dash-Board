#include "themescreen.h"
#include "ui_themescreen.h"

ThemeScreen::ThemeScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThemeScreen)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground); // 让 QWidget 子类能绘制样式表背景
    for(int i=1;i<=9;i++)
    {
        QString path = QString(":/background/bg/bg%1.png").arg(i);
        imgPaths.push_back(path);
    }
    for(int i=0;i<imgPaths.size();i++)
    {
        QLabel* item = new QLabel(this);
        item->setPixmap(QPixmap(imgPaths.at(i)));
        item->setFixedSize(180,130);
        item->setScaledContents(true);
        ui->gridLayout->addWidget(item,i/3,i%3);
        list_labels.push_back(item);
        item->installEventFilter(this);
        item->setObjectName(QString::number(i));
    }

}

ThemeScreen::~ThemeScreen()
{
    delete ui;
}

void ThemeScreen::randomSelectTheme()
{
    int randomIndex = QRandomGenerator::global()->bounded(0, imgPaths.size());

       // 清除所有卡片的高亮边框
       for(auto item : list_labels)
       {
           item->setStyleSheet("border:2px solid transparent; border-radius:6px;");
       }

       // 给随机选中的卡片加高亮
       list_labels.at(randomIndex)->setStyleSheet("border:3px solid #1E90FF; border-radius:6px;");

       // 更新当前索引
       imgIndex = randomIndex;

       // 发出信号，让 HomeScreen 同步切换背景
       emit changeThemePage(imgPaths.at(randomIndex));
}

bool ThemeScreen::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QLabel* label=dynamic_cast<QLabel*>(watched);
        if(label == nullptr)
        {
            return false;
        }

        for(auto item : list_labels)
        {
            item->setStyleSheet("border:2px solid transparent; border-radius:6px;");
        }

        label->setStyleSheet("border:3px solid #1E90FF; border-radius:6px;");

        imgIndex=label->objectName().toInt();

        return true;
    }

    return QWidget::eventFilter(watched,event);
}

void ThemeScreen::on_pushButton_clicked()
{
    QString path = imgPaths.at(imgIndex);
    emit changeThemePage(path);

}
