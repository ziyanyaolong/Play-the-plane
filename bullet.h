#ifndef BULLET_H
#define BULLET_H

#include "bass_object.h"

#include <QWidget>
#include <QPoint>
#include <QTimer>

class bullet : public bass_object
{
public:
    bullet();
    bullet(int damage,int volume,int Speed,int Direction);
    int return_speed() { return speed; }
    int return_direction() { return direction; }
private:
    int speed;
    int direction = 0;

};

#endif // BULLET_H
