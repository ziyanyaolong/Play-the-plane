#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <QWidget>

#include "enemy.h"
#include "oneself.h"
#include "Input_mm_zh.h"
#include "com_management.h"
#include "bullet.h"
#include "infrastructure.h"

#include <QPoint>
#include <QVector>
#include <QDebug>

class object_manager : public QWidget , public infrastructure
{
    Q_OBJECT
public:
    explicit object_manager(QWidget *parent = nullptr,
                            QPoint point = QPoint(0,0),
                            int Volume = 0,
                            int HP_max = 0,
                            int HP_min = 0,
                            int damage = 0,
                            int damage_volume = 0,
                            int damage_Speed = 0,
                            int damage_Direction = 0,
                            double oneself_my_speed = 0);
    virtual ~object_manager();
    oneself * return_oneself_me() { return oneself_me; }
    enemy * return_enemy(int a) { return enemy_1[a]; }
    enemy * set_enemy_nullptr(int a) { return enemy_1[a] = nullptr; }
    oneself * set_oneself_nullptr() { return oneself_me = nullptr; }
    enemy * new_enemy(int a);
    unsigned int return_enemy_number() { return enemy_number; }
    double read_score() { return score; }
    double set_score(double a) { return score = a; }
    double add_score(double a) { return score += a; }
    oneself * new_oneself();
    unsigned int add_enemy_number(int a);
    unsigned int set_enemy_number(int a);
private:
    unsigned int enemy_number;
    oneself * oneself_me;
    oneself * oneself_template;
    QVector<enemy*> enemy_1;
    enemy * enemy_1_template;
    double score = 0;
signals:
    void score_increase();

};

#endif // OBJECT_MANAGER_H
