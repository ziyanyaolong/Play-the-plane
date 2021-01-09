#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include "Input_mm_zh.h"
#include "main_interface.h"

class Window_managerData;

class Window_manager : public QObject
{
    Q_OBJECT
public:
    explicit Window_manager(QObject *parent = nullptr);
    ~Window_manager();

    Input_mm_zh* new_Input_mm_zh();
    main_interface* new_main_interface();
signals:

private:
    Input_mm_zh * a;
    main_interface * b;

};

#endif // WINDOW_MANAGER_H
