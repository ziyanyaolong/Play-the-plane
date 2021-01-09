#ifndef ONESELF_H
#define ONESELF_H

#include "bass_object.h"
#include "bullet.h"

#include <QWidget>
#include <QRect>
#include <QPoint>
#include <QVector>
#include <QSoundEffect>
#include <QThread>

class oneself : public bass_object
{
public:
    virtual ~oneself();

    oneself();
    oneself(QPoint point, int Volume, int HP_max, int HP_min, int damage,int damage_volume,int Speed,int damage_direction,double my_Speed);
    bullet * return_bullet() { return _bullet; }
    QVector<bullet*> return__bullet_() { return _bullet_; }
    bullet * return__bullet_(int a) { return _bullet_[a]; }
    bullet * set__bullet__nullptr(int a) { return _bullet_[a] = nullptr; };
    double return_speed() { return Speed; }
    bool bullet_fired();
private:
    bullet * _bullet;
    QVector<bullet*> _bullet_;
    double Speed;
    bool bullet_fired_ = false;
    bool bullet_cooling = false;
    unsigned bullet_velocity = 30;
};

#endif // ONESELF_H
