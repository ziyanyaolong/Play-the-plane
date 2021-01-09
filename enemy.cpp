#include "enemy.h"
#include "object_manager.h"
#include <QSoundEffect>

enemy::enemy() : bass_object() , _bullet()
{
}
enemy::enemy(QPoint point, int Volume, int HP_max, int HP_min, int damage,int damage_volume,int damage_Speed, int damage_Direction,double my_Speed) :
    bass_object(point,Volume,HP_max,HP_min) ,
    _bullet(damage,damage_volume,damage_Speed,damage_Direction)
{
    Speed = my_Speed;
}
enemy::~enemy()
{
}
