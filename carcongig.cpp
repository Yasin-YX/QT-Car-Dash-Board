#include "carcongig.h"

CarCongig::CarCongig()
{
    setting = new QSettings("config.ini",QSettings::IniFormat);

    if(!setting->contains("/car_status/door_lock"))
    {
        setting->setValue("/car_status/door_lock",0);
    }

    if(!setting->contains("/car_status/car_lock"))
    {
        setting->setValue("/car_status/car_lock",0);
    }
    if(!setting->contains("/car_air/temperature"))
    {
        setting->setValue("/car_air/temperature",23);
    }
    if(!setting->contains("/car_icon/car_icon_lock"))
    {
        setting->setValue("/car_icon/car_icon_lock",0);
    }
    if(!setting->contains("/car_btn/car_btn_lock"))
    {
        setting->setValue("/car_btn/car_btn_lock",0);
    }
    if(!setting->contains("/car_snow/car_snow_lock"))
    {
        setting->setValue("/car_snow/car_snow_lock",0);
    }
    if(!setting->contains("/car_loop/car_loop_lock"))
    {
        setting->setValue("/car_loop/car_loop_lock",0);
    }
    if(!setting->contains("/car_wind/car_wind_lock"))
    {
        setting->setValue("/car_wind/car_wind_lock",0);
    }
    if(!setting->contains("/car_wram/car_wram_lock"))
    {
        setting->setValue("/car_wram/car_wram_lock",0);
    }
    if(!setting->contains("/car_up/car_up_lock"))
    {
        setting->setValue("/car_up/car_up_lock",0);
    }
    if(!setting->contains("/car_oo/car_oo_lock"))
    {
        setting->setValue("/car_oo/car_oo_lock",0);
    }
    if(!setting->contains("/car_down/car_down_lock"))
    {
        setting->setValue("/car_down/car_down_lock",0);
    }
}
CarCongig CarCongig::temp;
CarCongig::CarCongig(const CarCongig &other)
{

}

CarCongig &CarCongig::getCar()
{        
        return temp;

}

void CarCongig::setDoorlock(bool lock)
{
    setting->setValue("/car_status/door_lock",lock?1:0);
}

bool CarCongig::getDoorLock()const
{
    return setting->value("/car_status/door_lock").toBool();
}

void CarCongig::setCarBox(bool lock)
{
     setting->setValue("/car_status/car_lock",lock?1:0);
}

bool CarCongig::getCarBox() const
{
    return setting->value("/car_status/car_lock").toBool();
}

void CarCongig::setTemperature(int temp)
{
    if(temp<16) temp=16;
    if(temp>30) temp=30;
    setting->setValue("/car_air/temperature",temp);

    emit sendTemperature(temp);
}

QJsonObject CarCongig::buildJsonObject()
{
    QJsonObject obj;
    obj["car_doorlock"]=getDoorLock();
    obj["car_boxlock"]=getCarBox();
    obj["temp"]=getTemperature();
    obj["icon"]=getIcon();
    obj["btn"]=getBtn();
    obj["loop"]=getLoop();
    obj["snow"]=getSnow();
    obj["wind"]=getWind();
    obj["wram"]=getWram();
    obj["level"]=getLevel();
    obj["up"]=getUp();
    obj["oo"]=getOo();
    obj["down"]=getDown();
    return obj;
}

int CarCongig::getTemperature() const
{
    return setting->value("/car_air/temperature").toInt();
}

void CarCongig::setIcon(bool lock)
{
    setting->setValue("/car_icon/car_icon_lock",lock?1:0);
}

bool CarCongig::getIcon() const
{
    return setting->value("/car_icon/car_icon_lock").toBool();
}

void CarCongig::setBtn(bool lock)
{
    setting->setValue("/car_btn/car_btn_lock",lock?1:0);
}

bool CarCongig::getBtn() const
{
    return setting->value("/car_btn/car_btn_lock").toBool();
}

void CarCongig::setSnow(bool lock)
{
    setting->setValue("/car_snow/car_snow_lock",lock?1:0);
}

bool CarCongig::getSnow() const
{
    return setting->value("/car_snow/car_snow_lock").toBool();
}

void CarCongig::setLoop(bool lock)
{
    setting->setValue("/car_loop/car_loop_lock",lock?1:0);
}

bool CarCongig::getLoop() const
{
    return setting->value("/car_loop/car_loop_lock").toBool();
}

void CarCongig::setWind(bool lock)
{
    setting->setValue("/car_wind/car_wind_lock",lock?1:0);
}

bool CarCongig::getWind() const
{
    return setting->value("/car_wind/car_wind_lock").toBool();
}

void CarCongig::setWram(bool lock)
{
    setting->setValue("/car_wram/car_wram_lock",lock?1:0);
}

bool CarCongig::getWram() const
{
    return setting->value("/car_wram/car_wram_lock").toBool();
}

void CarCongig::setLevel(int l)
{
    setting->setValue("/car_air/level",l);
}

int CarCongig::getLevel() const
{
    return setting->value("car_air/level").toInt();
}

void CarCongig::setUp(bool lock)
{
    setting->setValue("/car_up/car_up_lock",lock?1:0);
}

bool CarCongig::getUp() const
{
    return setting->value("/car_up/car_up_lock").toBool();
}

void CarCongig::setOo(bool lock)
{
    setting->setValue("/car_oo/car_oo_lock",lock?1:0);
}

bool CarCongig::getOo() const
{
    return setting->value("/car_oo/car_oo_lock").toBool();
}

void CarCongig::setDown(bool lock)
{
    setting->setValue("/car_down/car_down_lock",lock?1:0);
}

bool CarCongig::getDown() const
{
    return setting->value("/car_down/car_down_lock").toBool();
}




