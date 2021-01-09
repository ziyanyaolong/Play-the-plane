#include "bullet.h"
#include "bass_object.h"
#include "object_manager.h"

#include <QTimer>

bullet::bullet() : bass_object()
{
}
bullet::bullet(int damage,int volume,int Speed,int Direction) :
    bass_object(QPoint(0,0),volume,damage,damage)
{
    speed = Speed;
    direction = Direction;
}
