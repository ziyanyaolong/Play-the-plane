#include "windows_manager.h"
#include "object_manager.h"
#include "main_interface.h"
#include "general_manager.h"

extern general_manager * General_Manager;

windows_manager::windows_manager(QObject *parent) : QObject(parent)
{
    a = NULL;
    b = NULL;
}
Input_mm_zh* windows_manager::new_Input_mm_zh()
{
    a = new Input_mm_zh;
    a->resize(width_,highly_);
    return a;
}
main_interface* windows_manager::new_main_interface()
{
    b = new main_interface(0,nullptr,General_Manager->Object_Manager);
    if(b != nullptr)
    {
        b->resize(width_,highly_);
        return b;
    }else
    {
        return nullptr;
    }
}
Input_mm_zh* windows_manager::return_Input_mm_zh()
{
    if(a != nullptr)
    {
        return a;
    }else
    {
        return nullptr;
    }
}
main_interface* windows_manager::return_main_interface()
{
    if(b != nullptr)
    {
        return b;
    }else
    {
        return nullptr;
    }
}
windows_manager::~windows_manager()
{
    if(a != nullptr)
    {
        delete a;
    }
    if(b != nullptr)
    {
        delete b;
    }
}
