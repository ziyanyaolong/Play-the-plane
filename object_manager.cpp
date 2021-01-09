#include "object_manager.h"
#include "enemy.h"
#include "oneself.h"
#include "Input_mm_zh.h"
#include "main_interface.h"
#include "windows_manager.h"
#include "com_management.h"
#include "bullet.h"
#include "ui_main_interface.h"
#include "windows_manager.h"
#include "general_manager.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include <QWidget>
#include <QPen>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <random>
#include <QKeyEvent>
#include <QPaintEvent>
#include <iostream>
#include <stdlib.h>

int RandomNum(int min_num, int max_num);
double RandomNum_Double(double min_num, double max_num);

object_manager::object_manager(QWidget *parent,
                               QPoint oneself_point,
                               int oneself_Volume,
                               int oneself_HP_max,
                               int oneself_HP_min,
                               int oneself_damage,
                               int oneself_damage_volume,
                               int oneself_damage_Speed,
                               int oneself_damage_Direction,
                               double oneself_my_speed) : QWidget(parent)
{
    enemy_number = 10;
    oneself_template = new oneself(oneself_point,
                             oneself_Volume - 5,
                             oneself_HP_max,
                             oneself_HP_min,
                             oneself_damage,
                             oneself_damage_volume,
                             oneself_damage_Speed,
                             oneself_damage_Direction,
                             oneself_my_speed);
    oneself_me = nullptr;
    enemy_1_template = new enemy(QPoint(0,0),
                                 20,
                                 100,
                                 0,
                                 10,
                                 5,
                                 oneself_damage_Speed,
                                 oneself_damage_Direction,
                                 6);
    for(unsigned int i = 0;i < enemy_number;i++)
    {
        enemy_1.append(nullptr);
    }
}
enemy * object_manager::new_enemy(int a)
{
    if(enemy_1[a] == nullptr)
    {
        enemy_1[a] = new enemy(enemy_1_template->return_x_y(),
                               RandomNum(enemy_1_template->volume_() - 5,enemy_1_template->volume_() + 5),
                               enemy_1_template->HP_max(),
                               enemy_1_template->HP_min(),
                               enemy_1_template->return_bullet()->HP_Test(),
                               enemy_1_template->return_bullet()->volume_(),
                               enemy_1_template->return_bullet()->return_speed(),
                               enemy_1_template->return_bullet()->return_direction(),
                               enemy_1_template->return_speed());
        enemy_1[a]->setPoint(QPoint(RandomNum(int(Movable_area_width_2 / 2),int(Movable_area_width_2)) + Movable_area_width_2,
                                    RandomNum(int(Movable_area_highly_1 + enemy_1[a]->volume_()),
                                              int(Movable_area_highly_2 - enemy_1[a]->volume_()))));
        enemy_1[a]->HP_add(enemy_1[a]->volume_() * 1.5);
        enemy_1[a]->return_bullet()->HP_add(enemy_1[a]->volume_() * 2);
        if(enemy_1[a]->volume_() >= enemy_1_template->volume_())
        {
            enemy_1[a]->reduce_speed(enemy_1[a]->volume_() / enemy_1_template->volume_() * RandomNum_Double(1.3,2.3));
            enemy_1[a]->HP_add(enemy_1[a]->HP_Test() * RandomNum_Double(1.6,2.6));
            enemy_1[a]->return_bullet()->HP_add(enemy_1[a]->return_bullet()->HP_Test() * RandomNum_Double(1.3,2.6));
            enemy_1[a]->return_bullet()->add_volume(enemy_1[a]->volume_() / enemy_1_template->volume_() * RandomNum_Double(1.3,2.6));
        }else
        {
            enemy_1[a]->add_speed(enemy_1[a]->volume_() / enemy_1_template->volume_() * RandomNum_Double(1.6,2.6));
            enemy_1[a]->HP_reduce(enemy_1[a]->HP_Test() * RandomNum_Double(1.3,2.3));
            enemy_1[a]->return_bullet()->HP_reduce(enemy_1[a]->return_bullet()->HP_Test() * RandomNum_Double(1.6,2.3));
            enemy_1[a]->return_bullet()->reduce_volume(enemy_1[a]->volume_() * RandomNum_Double(1.6,2.3));
        }
        enemy_1[a]->set_my_color(QColor(RandomNum(0,255),RandomNum(0,255),RandomNum(0,255)));
    }
    return enemy_1[a];
}

int RandomNum(int min_num, int max_num)
{
    if (min_num > max_num)
    {
        int swap_temp = min_num;
        min_num = max_num;
        max_num = swap_temp;
    }
    return qrand() % (max_num-min_num+1) + min_num;
}
double RandomNum_Double(double min_num, double max_num)
{
    if (min_num > max_num)
    {
        int swap_temp = min_num;
        min_num = max_num;
        max_num = swap_temp;
    }
    std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min_num, max_num);
    return dis(gen);
}
oneself * object_manager::new_oneself()
{
    if(oneself_me == nullptr)
    {
        return oneself_me = new oneself(oneself_template->return_x_y(),
                                        oneself_template->volume_(),
                                        oneself_template->HP_max(),
                                        oneself_template->HP_min(),
                                        oneself_template->return_bullet()->HP_Test(),
                                        oneself_template->return_bullet()->volume_(),
                                        oneself_template->return_bullet()->return_speed(),
                                        oneself_template->return_bullet()->return_direction(),
                                        oneself_template->return_speed());
    }
    return oneself_me;
}
unsigned int object_manager::add_enemy_number(int a)
{
    for(int i = 0;i < a;i++)
    {
        enemy_1.append(nullptr);
    }
    return enemy_number += a;
}
unsigned int object_manager::set_enemy_number(int a)
{
    int temp = enemy_1.size();
    for(int i = 0;i < temp;i++)
    {
        if(enemy_1[i] != nullptr)
        {
            delete enemy_1[i];
            enemy_1[i] = nullptr;
        }
    }
    for(int i = 0;i < temp;i++)
    {
        enemy_1.pop_back();
    }
    for(int i = 0;i < a;i++)
    {
        enemy_1.append(nullptr);
    }
    return enemy_number = a;
}
object_manager::~object_manager()
{
    if(enemy_1_template != nullptr)
    {
        delete enemy_1_template;
    }
    if(oneself_me != nullptr)
    {
        delete oneself_me;
    }
    if(oneself_template != nullptr)
    {
        delete oneself_template;
    }
    for(int i = 0; i < enemy_1.size(); i++)
    {
        if(enemy_1[i] != nullptr)
        {
            delete enemy_1[i];
        }
    }
}
