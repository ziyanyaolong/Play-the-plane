#include "bass_object.h"
#include "oneself.h"
#include "Input_mm_zh.h"
#include "main_interface.h"
#include "windows_manager.h"
#include "com_management.h"
#include "object_manager.h"

#include <QPoint>

#define PI 3.141516


int bass_object::HP_max()
{
    return HP_MAX;
}
int bass_object::HP_min()
{
    return HP_MIN;
}

bass_object::bass_object()
{
    x_y = QPoint(0,0);
    volume = 1;
    HP_MAX = 100;
    HP_MIN = 0;
}
bass_object::bass_object(QPoint point)
{
    x_y = point;
    volume = 1;
    HP_MAX = 100;
    HP_MIN = 0;
}
bass_object::bass_object(QPoint point, double Volume, double HP_max, double HP_min)
{
    x_y = point;
    volume = Volume;
    HP_MAX = HP_max;
    HP_MIN = HP_min;
    HP = HP_max;
}
int bass_object::HP_add()
{
    if(HP + 1 > HP_MAX)
    {
        HP_IS_MAX();
        return  HP = HP_MAX;
    }else
    {
        return HP += 1;
    }
}
int bass_object::HP_add(double a)
{
    if(HP + a > HP_MAX)
    {
        HP_IS_MAX();
        return HP = HP_MAX;
    }else
    {
        return HP += a;
    }
}
int bass_object::HP_reduce()
{
    if(HP - 1 <= HP_MIN)
    {
        die();
        return HP = HP_MIN;
    }else
    {
        return HP -= 1;
    }
}
int bass_object::HP_reduce(double a)
{
    if(HP - a <= HP_MIN)
    {
        die();
        return HP = HP_MIN;
    }else
    {
        return HP -= a;
    }
}

int bass_object::HP_Test()
{
    return HP;
}

QPoint bass_object::point_x_add()
{
    if(x_y.x() + volume + 1 >= Movable_area_width_2)
    {
        x_y.setX(Movable_area_width_2 - volume);
        return x_y;
    }else
    {
        x_y.setX(x_y.x() + 1);
        return x_y;
    }
}
QPoint bass_object::point_x_add(double a)
{
    if(x_y.x() + volume + a >= Movable_area_width_2)
    {
        x_y.setX(Movable_area_width_2 - volume);
        return x_y;
    }else
    {
        x_y.setX(x_y.x() + a);
        return x_y;
    }
}
QPoint bass_object::point_x_reduce()
{
    if(x_y.x() - volume - 1 <= Movable_area_width_1)
    {
        x_y.setX(Movable_area_width_1 + volume);
        return x_y;
    }else
    {
        x_y.setX(x_y.x() - 1);
        return x_y;
    }
}
QPoint bass_object::point_x_reduce(double a)
{
    if(x_y.x() - volume - a <= Movable_area_width_1)
    {
        x_y.setX(Movable_area_width_1 + volume);
        return x_y;
    }else
    {
        x_y.setX(x_y.x() - a);
        return x_y;
    }
}

QPoint bass_object::point_y_add()
{
    if(x_y.y() + volume + 1 >= Movable_area_highly_2)
    {
        x_y.setY(Movable_area_highly_2 - volume);
        return x_y;
    }else
    {
        x_y.setY(x_y.y() + 1);
        return x_y;
    }
}
QPoint bass_object::point_y_add(double a)
{
    if(x_y.y() + volume + a >= Movable_area_highly_2)
    {
        x_y.setY(Movable_area_highly_2 - volume);
        return x_y;
    }else
    {
        x_y.setY(x_y.y() + a);
        return x_y;
    }
}
QPoint bass_object::point_y_reduce()
{
    if(x_y.y() - volume - 1 <= Movable_area_highly_1)
    {
        x_y.setY(Movable_area_highly_1 + volume);
        return x_y;
    }else
    {
        x_y.setY(x_y.y() - 1);
        return x_y;
    }
}
QPoint bass_object::point_y_reduce(double a)
{
    if(x_y.y() - volume - a <= Movable_area_highly_1)
    {
        x_y.setY(Movable_area_highly_1 + volume);
        return x_y;
    }else
    {
        x_y.setY(x_y.y() - a);
        return x_y;
    }
}
QPoint bass_object::point_x_add_unlimited()
{
    if(x_y.x() + volume + 1 >= Movable_area_width_2)
    {
        x_y.setX(x_y.x() + 1);
        Crossing_line_RIGHT();
        return x_y;
    }else
    {
        x_y.setX(x_y.x() + 1);
        return x_y;
    }
}
QPoint bass_object::point_x_add_unlimited(double a)
{
    if(x_y.x() + volume + a >= Movable_area_width_2)
    {
        x_y.setX(x_y.x() + a);
        Crossing_line_RIGHT();
        return x_y;
    }else
    {
        x_y.setX(x_y.x() + a);
        return x_y;
    }
}
QPoint bass_object::point_x_reduce_unlimited()
{
    if(x_y.x() - volume - 1 <= Movable_area_width_1)
    {
        x_y.setX(x_y.x() - 1);
        Crossing_line_LEFT();
        return x_y;
    }else
    {
        x_y.setX(x_y.x() - 1);
        return x_y;
    }
}
QPoint bass_object::point_x_reduce_unlimited(double a)
{
    if(x_y.x() - volume - a <= Movable_area_width_1)
    {
        x_y.setX(x_y.x() - a);
        Crossing_line_LEFT();
        return x_y;
    }else
    {
        x_y.setX(x_y.x() - a);
        return x_y;
    }
}

QPoint bass_object::point_y_add_unlimited()
{
    if(x_y.y() + volume + 1 >= Movable_area_highly_2)
    {
        x_y.setY(x_y.y() + 1);
        Crossing_line_AFTER();
        return x_y;
    }else
    {
        x_y.setY(x_y.y() + 1);
        return x_y;
    }
}
QPoint bass_object::point_y_add_unlimited(double a)
{
    if(x_y.y() + volume + a >= Movable_area_highly_2)
    {
        x_y.setY(x_y.y() + a);
        Crossing_line_AFTER();
        return x_y;
    }else
    {
        x_y.setY(x_y.y() + a);
        return x_y;
    }
}
QPoint bass_object::point_y_reduce_unlimited()
{
    if(x_y.y() - volume - 1 <= Movable_area_highly_1)
    {
        x_y.setY(x_y.y() - 1);
        Crossing_line_BEFORE();
        return x_y;
    }else
    {
        x_y.setY(x_y.y() - 1);
        return x_y;
    }
}
QPoint bass_object::point_y_reduce_unlimited(double a)
{
    if(x_y.y() - volume - a <= Movable_area_highly_1)
    {
        x_y.setY(x_y.y() - a);
        Crossing_line_BEFORE();
        return x_y;
    }else
    {
        x_y.setY(x_y.y() - a);
        return x_y;
    }
}
