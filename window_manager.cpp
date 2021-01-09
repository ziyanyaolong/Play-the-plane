#include "window_manager.h"

#include "Input_mm_zh.h"
#include "main_interface.h"

Window_manager::Window_manager(QObject *parent) : QObject(parent)
{
}


Window_manager::~Window_manager()
{
}

Input_mm_zh* Window_manager::new_Input_mm_zh()
{
    return a = new Input_mm_zh;
}
main_interface* Window_manager::new_main_interface()
{
    return b = new main_interface;
}
