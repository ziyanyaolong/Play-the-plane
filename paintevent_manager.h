#ifndef PAINTEVENT_MANAGER_H
#define PAINTEVENT_MANAGER_H

#include <QWidget>
#include <QTimer>
#include <QtOpenGL>
#include <QPaintEvent>

namespace Ui {
class paintevent_manager;
}

class paintevent_manager : public QGLWidget
{
    Q_OBJECT

public:
    paintevent_manager(QWidget* parent = nullptr,bool fs = false);
    ~paintevent_manager();
    void paintEvent(QPaintEvent *);
protected:

  void initializeGL();
  void paintGL();
  void resizeGL( int width, int height );
  void keyPressEvent( QKeyEvent *e );
  bool fullscreen;

private:
    Ui::paintevent_manager *ui;
    QTimer * fps;
};

#endif // PAINTEVENT_MANAGER_H
