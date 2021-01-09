
#include "oneself.h"
#include "Input_mm_zh.h"
#include "main_interface.h"
#include "windows_manager.h"
#include "com_management.h"
#include "bullet.h"
#include "object_manager.h"

#include <QPoint>
#include <QDebug>
#include <QPainter>
#include <QTimer>
#include <QSoundEffect>

extern COM_management COM_m;
extern windows_manager * manager;
extern QPixmap * pixmap;

oneself::oneself() : bass_object()
{
    _bullet = new bullet;
}

oneself::oneself(QPoint point, int Volume,int HP_max, int HP_min,
                 int damage,int damage_volume, int damage_Speed,int damage_Direction,double my_Speed) :
    bass_object(point,Volume,HP_max,HP_min)
{
    _bullet = new bullet(damage,damage_volume,damage_Speed,damage_Direction);
    Speed = my_Speed;
}
bool oneself::bullet_fired()
{
    if(!bullet_cooling)
    {
        bullet_fired_ = true;
        bullet_cooling = true;
        for(int i = 0; i < _bullet_.size(); i++)
        {
            if(_bullet_[i] == nullptr)
            {
                _bullet_[i] = new bullet(_bullet->HP_Test(),_bullet->volume_(),_bullet->return_speed(),_bullet->return_direction());
                _bullet_[i]->setPoint(QPoint((x_y.x() + volume),x_y.y()));
                return true;
            }
        }
        _bullet_.prepend(new bullet(_bullet->HP_Test(),_bullet->volume_(),_bullet->return_speed(),_bullet->return_direction()));
        _bullet_[0]->setPoint(return_x_y());
    }else if(bullet_fired_)
    {
        bullet_fired_ = false;
        QTimer::singleShot(bullet_velocity, this, [=](){
            bullet_cooling = false;
        });
    }
    return false;
}
oneself::~oneself()
{
    delete _bullet;
    _bullet = nullptr;
    for(int i = 0;i < _bullet_.size();i++)
    {
        bullet_fired_ = false;
        if(_bullet_[i] != nullptr)
        {
            delete _bullet_[i];
            _bullet_[i] = nullptr;
        }
    }
}
