#ifndef ENEMY_H
#define ENEMY_H

#include "bass_object.h"
#include "bullet.h"
#include "infrastructure.h"

#include <QWidget>
#include <QRect>
#include <QPoint>

class enemy : public bass_object
{
public:
    enemy();
    ~enemy();
    enemy(QPoint point, int Volume, int HP_max, int HP_min, int damage,int damage_volume,int Speed,int damage_Direction,double my_Speed);
    bullet * return_bullet() { return &_bullet; }
    QColor set_my_color(QColor color) { return my_color = color; }
    QColor return_my_color() { return my_color; }
    double return_speed() { return Speed; }
    double set_speed(double speed) { return Speed = speed; }
    double add_speed(double speed) { return Speed += speed; }
    double reduce_speed(double speed) { return Speed -= speed; }
private:
    bullet _bullet;   
    QColor my_color;
    double Speed;
};

#endif // ENEMY_H
