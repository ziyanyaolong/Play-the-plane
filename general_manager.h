#ifndef GENERAL_MANAGER_H
#define GENERAL_MANAGER_H

#include <QWidget>

#include "main_interface.h"
#include "ui_main_interface.h"
#include "com_management.h"
#include "windows_manager.h"
#include "oneself.h"
#include "object_manager.h"

class general_manager : public QWidget
{
    Q_OBJECT
public:
    explicit general_manager(QWidget *parent = nullptr);
    virtual ~general_manager();

    windows_manager * manager;
    COM_management * COM_m;
    object_manager * Object_Manager;
signals:

};

#endif // GENERAL_MANAGER_H
