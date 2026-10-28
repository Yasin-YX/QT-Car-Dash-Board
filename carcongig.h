#ifndef CARCONGIG_H
#define CARCONGIG_H

#include <QSettings>
#include <QObject>
#include <QJsonObject>
class CarCongig:public QObject
{
    Q_OBJECT
    CarCongig();
    CarCongig(const CarCongig & other);

    QSettings* setting;

   static CarCongig temp;
signals:
    void sendTemperature(int temp);

public:
    static CarCongig & getCar();

    void setDoorlock(bool lock);
    bool getDoorLock()const;

    void setCarBox(bool lock);
    bool getCarBox()const;

    void setTemperature(int temp);
    int getTemperature()const;

    void setIcon(bool lock);
    bool getIcon()const;

    void setBtn(bool lock);
    bool getBtn()const;

    void setSnow(bool lock);
    bool getSnow()const;

    void setLoop(bool lock);
    bool getLoop()const;

    void setWind(bool lock);
    bool getWind()const;

    void setWram(bool lock);
    bool getWram()const;

    void setLevel(int l);
    int getLevel()const;

    void setUp(bool lock);
    bool getUp()const;

    void setOo(bool lock);
    bool getOo()const;

    void setDown(bool lock);
    bool getDown()const;
    QJsonObject buildJsonObject();
};

#endif // CARCONGIG_H
