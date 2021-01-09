#include "general_manager.h"
#include "window_manager.h"
#include "object_manager.h"

general_manager::general_manager(QWidget *parent) : QWidget(parent)
{
    COM_m = new COM_management;
    manager = new  windows_manager;
    Object_Manager = new object_manager(nullptr,QPoint(50,manager->return_highl() / 2 + 5),20,40,0,40,10,10,0,5);
    manager->new_Input_mm_zh()->show();
}
general_manager::~general_manager()
{
    if(manager != nullptr)
    {
        delete manager;
    }
    if(COM_m != nullptr)
    {
        delete COM_m;
    }
    if(Object_Manager != nullptr)
    {
        delete Object_Manager;
    }
}
