#ifndef BASS_OBJECT_H
#define BASS_OBJECT_H

#include <QWidget>
#include <QRect>
#include <QPoint>

#include "infrastructure.h"


class bass_object : public QWidget , public infrastructure
{
public:
    bass_object();
    bass_object(QPoint point);
    bass_object(QPoint point, double Volume, double HP_max, double HP_min);

    virtual int HP_set(double a) { return HP = a; }
    virtual int HP_max();
    virtual int HP_min();
    virtual int HP_add();
    virtual int HP_add(double a);
    virtual int HP_reduce();
    virtual int HP_reduce(double a);
    virtual int HP_Test();
    virtual int volume_() { return volume; }
    virtual int set_volume(double Volume) { return volume = Volume; }
    virtual int add_volume(double Volume) { return volume += Volume; }
    virtual int reduce_volume(double Volume) { return volume -= Volume; }

    virtual QPoint return_x_y() { return x_y; }
    virtual QPoint point_x_add();
    virtual QPoint point_y_add();
    virtual QPoint point_x_reduce();
    virtual QPoint point_y_reduce();

    virtual QPoint point_x_add(double a);
    virtual QPoint point_y_add(double a);
    virtual QPoint point_x_reduce(double a);
    virtual QPoint point_y_reduce(double a);

    virtual QPoint setPoint(QPoint xy) { return x_y=xy; }

    virtual QPoint point_x_add_unlimited();
    virtual QPoint point_y_add_unlimited();
    virtual QPoint point_x_reduce_unlimited();
    virtual QPoint point_y_reduce_unlimited();

    virtual QPoint point_x_add_unlimited(double a);
    virtual QPoint point_y_add_unlimited(double a);
    virtual QPoint point_x_reduce_unlimited(double a);
    virtual QPoint point_y_reduce_unlimited(double a);
protected:
    double HP_MAX;
    double HP_MIN;
    double HP;
    double volume;
    QPoint x_y;

signals:
    void HP_IS_MAX() {}
    void die() {}

    void Crossing_line_RIGHT() {}
    void Crossing_line_LEFT() {}
    void Crossing_line_BEFORE() {}
    void Crossing_line_AFTER() {}
};

#endif // BASS_OBJECT_H
