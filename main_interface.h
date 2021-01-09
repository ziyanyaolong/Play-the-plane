#ifndef MAIN_INTERFACE_H
#define MAIN_INTERFACE_H

#include <QMainWindow>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include <QSoundEffect>

#include "object_manager.h"
#include "infrastructure.h"

namespace Ui {
class main_interface;
}

class main_interface : public QWidget ,public infrastructure
{
    Q_OBJECT

public:
    explicit main_interface(bool fs = 0,QWidget *parent = nullptr,object_manager * Object_Manager_ = nullptr);
    virtual ~main_interface();

    double return_Movable_area_highly_1() { return Movable_area_highly_1; }
    double return_Movable_area_width_1() { return Movable_area_width_1; }
    double return_Movable_area_highly_2() { return Movable_area_highly_2; }
    double return_Movable_area_width_2() { return Movable_area_width_2; }

    void bullet_calculation();
    void bullet_management();

    bool Kill_entity(int a,int b);
    bool HP_judgment(int a, int b);

protected:

    void paintEvent(QPaintEvent * e);
    void keyPressEvent(QKeyEvent * e);
    void keyReleaseEvent(QKeyEvent * e);
    void Game_keyboard_control();
    bool fullscreen;

private:
    QPixmap * pixmap;
    QPainter * painter;
    QPen * pen;
    QBrush * brush;

    QPushButton * start_all_over_again;
    QPushButton * close_game;
    Ui::main_interface *ui;
    QByteArray * COM_Buffer_Read;

    object_manager * object_manager_;

    QTimer * fps;

    QImage * background1;
    QImage * background2;
    QImage * background3;

    QSoundEffect * music;
    QSoundEffect * sound0;
    QSoundEffect * sound1;

    QThread * music_sounds_thread;


    bool start = false;

    bool Key_R = false;
    bool Key_Up = false;
    bool Key_Left = false;
    bool Key_Down = false;
    bool Key_Right = false;
};

#endif // MAIN_INTERFACE_H
