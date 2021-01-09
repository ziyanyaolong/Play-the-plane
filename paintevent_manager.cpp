#include "paintevent_manager.h"
#include "main_interface.h"
#include "ui_main_interface.h"
#include "com_management.h"
#include "windows_manager.h"
#include "oneself.h"
#include "object_manager.h"
#include "ui_paintevent_manager.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>
#include <QTimer>
#include <QPushButton>

#include <QPen>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <random>
#include <QKeyEvent>
#include <GL/glu.h>
#include <QtOpenGL>

#define MOVE_SPEED 10

extern COM_management COM_m;
extern windows_manager * manager;
extern object_manager * Object_Manager;
extern QPixmap * pixmap;

paintevent_manager::~paintevent_manager()
{
}
paintevent_manager::paintevent_manager(QWidget* parent, bool fs) : QGLWidget(parent) ,
    ui(new Ui::paintevent_manager)
{
    fullscreen = fs;
    fs = false;
    setGeometry( 0, 0, manager->return_width(), manager->return_highl());
    if ( fullscreen )
        showFullScreen();
    ui->setupUi(this);
    show();
    resize(manager->return_width(),manager->return_highl());
    fps = new QTimer;
    fps->start(10);
    connect(fps,&QTimer::timeout,this,[=](){
        updateGL();
    });
}

void paintevent_manager::initializeGL()
{
  glShadeModel( GL_SMOOTH );
  glClearColor( 0.0, 0.0, 0.0, 0.0 );
  glClearDepth( 1.0 );
  glEnable( GL_DEPTH_TEST );
  glDepthFunc( GL_LEQUAL );
  glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void paintevent_manager::paintGL()
{
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  glLoadIdentity();
  glRectd(manager->return_main_interface()->return_Movable_area_width_1(),
          manager->return_main_interface()->return_Movable_area_highly_1(),
          manager->return_main_interface()->return_Movable_area_width_2(),
          manager->return_main_interface()->return_Movable_area_highly_2());
}

void paintevent_manager::resizeGL( int width, int height )
{
  if ( height == 0 )
  {
    height = 1;
  }
  glViewport( 0, 0, (GLint)width, (GLint)height );
  glMatrixMode( GL_PROJECTION );
  glLoadIdentity();
  gluPerspective( 45.0, (GLfloat)width/(GLfloat)height, 0.1, 100.0 );
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
}

void paintevent_manager::keyPressEvent( QKeyEvent *e )
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
      setGeometry( 0, 0, 640, 480 );
    }
    updateGL();
    break;

  case Qt::Key_Escape:
    close();
  }

}

void paintevent_manager::paintEvent(QPaintEvent *)
{
}


//    if(manager->return_main_interface() != nullptr)
//    {
//        QPainter painter(pixmap);
//        *pixmap = QPixmap(manager->return_width(),manager->return_highl());
//        QPen pen(QColor(70,120,155));
//        QBrush brush(QColor(70,120,10));
//        painter.setPen(pen);
//        painter.setBrush(brush);
//        painter.fillRect(0,0,width(),height(),QColor(255,255,255));
//        painter.fillRect(manager->return_main_interface()->return_Movable_area_width_1(),
//                         manager->return_main_interface()->return_Movable_area_highly_1(),
//                         manager->return_main_interface()->return_Movable_area_width_2(),
//                         manager->return_main_interface()->return_Movable_area_highly_2(),
//                         QColor(0,0,0));

//        painter.fillRect(manager->return_main_interface()->return_Movable_area_width_1(),
//                         manager->return_main_interface()->return_Movable_area_highly_2(),
//                         width(),
//                         height(),
//                         QColor(255,255,255));

//        painter.drawEllipse(Object_Manager->return_oneself_me()->return_x_y(),
//                            Object_Manager->return_oneself_me()->volume_(),
//                            Object_Manager->return_oneself_me()->volume_());

//        if(Object_Manager->return_oneself_me()->return_Firing_condition())
//        {
//            pen.setColor(QColor(90,100,60));
//            brush.setColor(QColor(90,100,60));
//            painter.setPen(pen);
//            painter.setBrush(brush);
//    //        painter.drawEllipse(oneself_me->_bullet->setPoint(QPoint(oneself_me->volume_() + oneself_me->_bullet->volume_() + oneself_me->return_x_y().x(),oneself_me->return_x_y().y())),oneself_me->_bullet->volume_(),oneself_me->_bullet->volume_());
//    //        if(oneself_me->_bullet->return_x_y().x() > oneself_me->return_x_y().x())
//    //        {
//    //            oneself_me->_bullet->setPoint(QPoint(oneself_me->return_x_y().x() + oneself_me->volume_() + oneself_me->_bullet->volume_(), oneself_me->return_x_y().y()));
//    //            oneself_me->set_return_Firing_condition(false);
//    //        }
//        }
//        painter.end();
//        painter.begin(manager->return_main_interface());
//        //在Widget上开始绘制
//        painter.drawPixmap(0, 0, *pixmap);
//    }
//}
