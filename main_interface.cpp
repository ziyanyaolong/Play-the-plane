#include "main_interface.h"
#include "ui_main_interface.h"
#include "com_management.h"
#include "windows_manager.h"
#include "oneself.h"
#include "object_manager.h"
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
#include <math.h>
#include <QSize>
#include <QFont>
#include <QSoundEffect>


#define MOVE_SPEED 10

double Collision_calculation(double x1,double y1,double x2,double y2,double volume1,double volume2);

main_interface::main_interface(
        bool fs,
        QWidget *parent,
        object_manager * Object_Manager_) :
    QWidget (parent),
    ui(new Ui::main_interface)
{
    object_manager_ = Object_Manager_;
    fullscreen = fs;
    fs = false;
    if ( fullscreen )
        showFullScreen();
    resize(width_,highly_);
    fps = new QTimer;
    fps->start(10);
    music_sounds_thread = new QThread;
    sound0 = new QSoundEffect;
    music = new QSoundEffect;
    sound1 = new QSoundEffect;

    sound0->setSource(QUrl::fromLocalFile(":/sounds/sounds/explosion.wav"));
    sound0->setLoopCount(QSoundEffect::Infinite);
    sound0->setVolume(2.0f);
    sound0->moveToThread(music_sounds_thread);

    sound1->setSource(QUrl::fromLocalFile(":/sounds/sounds/bullet_fired.wav"));
    sound1->setLoopCount(QSoundEffect::Infinite);
    sound1->setVolume(1.0f);
    sound1->moveToThread(music_sounds_thread);

    music->setSource(QUrl::fromLocalFile(":/music/music/music1.wav"));
    music->setLoopCount(QSoundEffect::Infinite);
    music->setVolume(0.2f);
    music->moveToThread(music_sounds_thread);
    music_sounds_thread->start();

    pixmap = new QPixmap(width_,highly_);
    painter = new QPainter(pixmap);
    pen = new QPen(QColor(70,120,155));
    brush = new QBrush(QColor(70,120,10));
    painter->setPen(*pen);
    painter->setBrush(*brush);

    start_all_over_again = new QPushButton("开始游戏",this);
    start_all_over_again->setFixedSize(width_ / 10,highly_ / 10);
    start_all_over_again->move(width_ / 10 * 5,highly_ / 10 * 5);
    start_all_over_again->show();

    close_game = nullptr;

    connect(start_all_over_again,&QPushButton::clicked,this,[=](){
        Key_Up = false;
        Key_Down = false;
        Key_Left = false;
        Key_Right = false;
        Key_R = false;
        if(object_manager_->return_oneself_me() == nullptr)
        {
            object_manager_->new_oneself();
        }
        start = true;
        delete start_all_over_again;
        start_all_over_again = nullptr;
    });

    connect(fps,&QTimer::timeout,this,[=](){
        update();
        Game_keyboard_control();
        if(!music->isPlaying())
        {
            music->play();
        }
    });

    for(unsigned int i = 0;i < object_manager_->return_enemy_number();i++)
    {
        if(object_manager_->return_enemy(i) == nullptr)
        {
            object_manager_->new_enemy(i);
            object_manager_->return_enemy(i)->point_x_add(Movable_area_width_2);
        }
    }
    background1 = new QImage(":/background/res/1.jpg");
    *background1 = background1->scaled(Movable_area_width_2, Movable_area_highly_2 - Movable_area_highly_1, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background2 = new QImage(":/background/res/2.jpg");
    *background2 = background2->scaled(Movable_area_width_2, Movable_area_highly_1, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    background3 = new QImage(":/background/res/3.jpg");
    *background3 = background3->scaled(Movable_area_width_2, Movable_area_highly_1, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
}

void main_interface::Game_keyboard_control()
{
    if(object_manager_->return_oneself_me() != nullptr)
    {
        if(Key_Up) object_manager_->return_oneself_me()->point_y_reduce(object_manager_->return_oneself_me()->return_speed());
        if(Key_Left) object_manager_->return_oneself_me()->point_x_reduce(object_manager_->return_oneself_me()->return_speed());
        if(Key_Down) object_manager_->return_oneself_me()->point_y_add(object_manager_->return_oneself_me()->return_speed());
        if(Key_Right) object_manager_->return_oneself_me()->point_x_add(object_manager_->return_oneself_me()->return_speed());
        if(Key_R)
        {
            if(start)
            {
                if(object_manager_->return_oneself_me()->bullet_fired())
                {
                    sound1->play();
                    sound1->setLoopCount(0);
                }
            }
        }
    }
}

main_interface::~main_interface()
{
    if(music_sounds_thread->isRunning())
    {
        music_sounds_thread->terminate();
        music_sounds_thread->exit();
    }
    if(pixmap != nullptr)
    {
        delete pixmap;
    }
    if(painter != nullptr)
    {
        delete painter;
    }
    if(pen != nullptr)
    {
        delete pen;
    }
    if(brush != nullptr)
    {
        delete brush;
    }
    if(start_all_over_again != nullptr)
    {
        delete start_all_over_again;
    }
    if(close_game != nullptr)
    {
        delete close_game;
    }
    if(fps != nullptr )
    {
        delete fps;
    }
    if(background1 != nullptr )
    {
        delete background1;
    }
    if(background2 != nullptr )
    {
        delete background2;
    }
    if(background3 != nullptr )
    {
        delete background3;
    }
    if(music != nullptr)
    {
        delete music;
    }
    if(music_sounds_thread != nullptr)
    {
        delete music_sounds_thread;
    }
    if(sound0 != nullptr)
    {
        delete sound0;
    }
    if(sound1 != nullptr)
    {
        delete sound1;
    }
    delete ui;
}

void main_interface::keyReleaseEvent(QKeyEvent * e)
{
    if(start)
    {
        switch ( e->key() )
        {

        case Qt::Key_Up:
            Key_Up = false;
            break;

        case Qt::Key_Down:
            Key_Down = false;
            break;

        case Qt::Key_Left:
            Key_Left = false;
            break;

        case Qt::Key_Right:
            Key_Right = false;
            break;

        case Qt::Key_R:
            Key_R = false;
            break;
        }
    }
}
void main_interface::keyPressEvent(QKeyEvent * e)
{
    if(start)
    {
        switch ( e->key() )
        {
        case Qt::Key_F2:
          fullscreen = !fullscreen;
          if ( fullscreen )
          {
            showFullScreen();
          }
          else
          {
            showNormal();
          }
          break;

        case Qt::Key_Escape:
          close();
            break;

        case Qt::Key_Up:
            Key_Up = true;
            break;

        case Qt::Key_Down:
            Key_Down = true;
            break;

        case Qt::Key_Left:
            Key_Left = true;
            break;

        case Qt::Key_Right:
            Key_Right = true;
            break;

        case Qt::Key_R:
            Key_R = true;
            break;
        }
    }else if(e->key())
    {
        if(e->isAutoRepeat())
        {
            e->ignore();
            return;
        }
        if(start_all_over_again != nullptr)
        {
            start_all_over_again->clicked();
            return;
        }
        if(close_game != nullptr)
        {
            close_game->clicked();
            return;
        }
    }
}

void main_interface::paintEvent(QPaintEvent *)
{
    pen->setColor(QColor(70,120,155));
    brush->setColor(QColor(70,120,10));
    painter->setPen(*pen);
    painter->setBrush(*brush);
    painter->fillRect(0,0,width(),height(),QColor(255,255,255));
    painter->fillRect(Movable_area_width_1,
                     Movable_area_highly_1,
                     Movable_area_width_2,
                     Movable_area_highly_2,
                     QColor(0,0,0));

    painter->fillRect(Movable_area_width_1,
                     Movable_area_highly_2,
                     width(),
                     height(),
                     QColor(255,255,255));

    painter->drawImage(QPoint(0,0),*background2);
    painter->drawImage(QPoint(0,Movable_area_highly_2),*background3);
    painter->drawImage(QPoint(0,Movable_area_highly_1),*background1);
    QFont font("宋体",20,QFont::Bold,true);//设置字体的类型，大小，加粗，斜体
    font.setUnderline(false);//设置下划线
    font.setOverline(false);//设置上划线
    font.setCapitalization(QFont::SmallCaps);//设置大小写
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);//设置间距
    painter->setFont(font);
    QRect ff(0,0,300,200);
    painter->setPen(QColor(Qt::red));
    painter->drawText(ff,Qt::AlignCenter,"分数" + QString::number(int(object_manager_->read_score())));
    if(start)
    {
        bullet_management();
        bullet_calculation();
        for(unsigned int i = 0; i < object_manager_->return_enemy_number();i++)
        {
            if(object_manager_->return_enemy(i) != nullptr && object_manager_->return_oneself_me() != nullptr)
            {
                if(Collision_calculation(object_manager_->return_oneself_me()->return_x_y().x(),
                                         object_manager_->return_oneself_me()->return_x_y().y(),
                                         object_manager_->return_enemy(i)->return_x_y().x(),
                                         object_manager_->return_enemy(i)->return_x_y().y(),
                                         object_manager_->return_oneself_me()->volume_(),
                                         object_manager_->return_enemy(i)->volume_()) < 0)
                {
                    start = false;
                    Kill_entity(2,0);
                    for(unsigned int i = 0; i < object_manager_->return_enemy_number();i++)
                    {
                        Kill_entity(1,i);
                    }
                    break;
                }
            }else if(object_manager_->return_oneself_me() != nullptr)
            {
                break;
            }
        }
        if(object_manager_->return_oneself_me() != nullptr)
        {
            pen->setColor(QColor(25,70,200));
            brush->setColor(QColor(25,70,200));
            painter->drawEllipse(object_manager_->return_oneself_me()->return_x_y(),
                                object_manager_->return_oneself_me()->volume_(),
                                object_manager_->return_oneself_me()->volume_());
            for(unsigned int i = 0; i < object_manager_->return_enemy_number();i++)
            {
                if(object_manager_->return_enemy(i) != nullptr)
                {
                    if(object_manager_->return_enemy(i)->return_x_y().x() <=
                            (Movable_area_width_1 - object_manager_->return_enemy(i)->volume_()) ||
                            object_manager_->return_enemy(i)->return_x_y().x() >= (Movable_area_width_2 * 4) ||
                            object_manager_->return_enemy(i)->return_x_y().y() < Movable_area_highly_1 ||
                            object_manager_->return_enemy(i)->return_x_y().y() > Movable_area_highly_2)
                    {
                        object_manager_->return_enemy(i)->set_my_color(QColor(0,0,0));
                        pen->setColor(object_manager_->return_enemy(i)->return_my_color());
                        brush->setColor(object_manager_->return_enemy(i)->return_my_color());
                        painter->setPen(*pen);
                        painter->setBrush(*brush);
                        painter->drawEllipse(object_manager_->return_enemy(i)->return_x_y(),
                                            object_manager_->return_enemy(i)->volume_(),
                                            object_manager_->return_enemy(i)->volume_());
                        Kill_entity(1,i);
                        continue;
                    }
                    pen->setColor(object_manager_->return_enemy(i)->return_my_color());
                    brush->setColor(object_manager_->return_enemy(i)->return_my_color());
                    painter->setPen(*pen);
                    painter->setBrush(*brush);
                    painter->drawEllipse(object_manager_->return_enemy(i)->return_x_y(),
                                        object_manager_->return_enemy(i)->volume_(),
                                        object_manager_->return_enemy(i)->volume_());
                }else
                {
                    object_manager_->new_enemy(i);
                }
            }
         }
        for(unsigned int i = 0; i < object_manager_->return_enemy_number();i++)
        {
            if(object_manager_->return_enemy(i) != nullptr)
            {
                object_manager_->return_enemy(i)->point_x_add_unlimited(-(object_manager_->return_enemy(i)->return_speed()));
            }
        }
    }
    painter->end();
    painter->begin(this);
    painter->drawPixmap(0, 0, *pixmap);
    painter->end();
    painter->begin(pixmap);
}

double Collision_calculation(double x1,double y1,double x2,double y2,double volume1,double volume2)
{
    return (sqrt((pow((x2-x1),2))+(pow((y2-y1),2)))-volume1-volume2);
}

bool main_interface::Kill_entity(int a,int b)
{
    if(a == 0)
    {
        if(object_manager_->return_oneself_me()->return__bullet_(b) != nullptr && object_manager_->return_oneself_me() != nullptr)
        {
            delete object_manager_->return_oneself_me()->return__bullet_(b);
            object_manager_->return_oneself_me()->set__bullet__nullptr(b);
            return 1;
        }
        return 0;
    }else if(a == 1)
    {
        if(object_manager_->return_enemy(b) != nullptr)
        {
            delete object_manager_->return_enemy(b);
            object_manager_->set_enemy_nullptr(b);
            return 1;
        }
        return 0;
    }else if(a == 2)
    {
        if(object_manager_->return_oneself_me() != nullptr)
        {
            object_manager_->set_enemy_number(10);
            if(close_game != nullptr)
            {
                delete close_game;
                close_game = nullptr;
            }
            delete object_manager_->return_oneself_me();
            object_manager_->set_oneself_nullptr();
            close_game = new QPushButton("重新开始",this);
            close_game->setFixedSize(width_ / 10,highly_ / 10);
            close_game->move(width_ / 10 * 5,highly_ / 10 * 5);
            close_game->show();

            connect(close_game,&QPushButton::clicked,this,[=](){
                object_manager_->set_score(0);
                Key_Up = false;
                Key_Down = false;
                Key_Left = false;
                Key_Right = false;
                Key_R = false;
                if(object_manager_->return_oneself_me() == nullptr)
                {
                    object_manager_->new_oneself();
                }
                for(unsigned int i = 0;i < object_manager_->return_enemy_number();i++)
                {
                    if(object_manager_->return_enemy(i) == nullptr)
                    {
                        object_manager_->new_enemy(i);
                    }
                }
                start = true;
                delete close_game;
                close_game = nullptr;
            });
            return 1;
        }
        return 0;
    }else
    {
        return 0;
    }
}
void main_interface::bullet_calculation()
{
    for(int j = 0; j < object_manager_->return_oneself_me()->return__bullet_().size();j++)
    {
        if(object_manager_->return_oneself_me()->return__bullet_(j) != nullptr)
        {
            pen->setColor(QColor(90,150,30));
            brush->setColor(QColor(90,150,30));
            painter->setPen(*pen);
            painter->setBrush(*brush);
            painter->drawEllipse(object_manager_->return_oneself_me()->return__bullet_(j)->return_x_y(),
                                object_manager_->return_oneself_me()->return__bullet_(j)->volume_(),
                                object_manager_->return_oneself_me()->return__bullet_(j)->volume_());
            for(unsigned int i = 0; i < object_manager_->return_enemy_number();i++)
            {
                if(object_manager_->return_enemy(i) != nullptr && object_manager_->return_oneself_me()->return__bullet_(j) != nullptr)
                {
                    if(Collision_calculation(object_manager_->return_oneself_me()->return__bullet_(j)->return_x_y().x(),
                                             object_manager_->return_oneself_me()->return__bullet_(j)->return_x_y().y(),
                                             object_manager_->return_enemy(i)->return_x_y().x(),
                                             object_manager_->return_enemy(i)->return_x_y().y(),
                                             object_manager_->return_oneself_me()->return__bullet_(j)->volume_(),
                                             object_manager_->return_enemy(i)->volume_()) <= 0)
                    {
                        if(HP_judgment(object_manager_->return_enemy(i)->HP_Test(),object_manager_->return_oneself_me()->return__bullet_(j)->HP_Test()))
                        {
                            object_manager_->add_score(object_manager_->return_enemy(i)->HP_max());
                            Kill_entity(1,i);
                            Kill_entity(0,j);
                            sound0->play();
                            sound0->setLoopCount(0);
                        }else
                        {
                            object_manager_->return_enemy(i)->HP_reduce(object_manager_->return_oneself_me()->return__bullet_(j)->HP_max());
                            Kill_entity(0,j);
                            sound0->play();
                            sound0->setLoopCount(0);
                        }
                        continue;
                    }
                }
            }
            if(object_manager_->return_oneself_me()->return__bullet_(j) != nullptr)
            {
                object_manager_->return_oneself_me()->return__bullet_(j)->point_x_add_unlimited(object_manager_->return_oneself_me()->return__bullet_(j)->return_speed());
            }
            if(object_manager_->return_oneself_me()->return__bullet_(j) != nullptr)
            {
                if(object_manager_->return_oneself_me()->return__bullet_(j)->return_x_y().x() > Movable_area_width_2 && object_manager_->return_oneself_me()->return__bullet_(j) != nullptr)
                {
                    Kill_entity(0,j);
                }
            }
         }
      }
}
void main_interface::bullet_management()
{
    for(int i = 0; i < object_manager_->return_oneself_me()->return__bullet_().size(); i++)
    {
        if(object_manager_->return_oneself_me()->return__bullet_(i) == nullptr)
        {
            delete object_manager_->return_oneself_me()->return__bullet_(i);
            object_manager_->return_oneself_me()->return__bullet_().remove(i);
         }
    }
}

bool main_interface::HP_judgment(int a, int b)
{
    if(b <= 0)
    {
        return false;
    }
    if(a <= 0)
    {
        return true;
    }
    if(a - b > 0)
    {
        return false;
    }else
    {
        return true;
    }
}
