#include "Input_mm_zh.h"
#include "main_interface.h"
#include "windows_manager.h"
#include "com_management.h"
#include "oneself.h"
#include "object_manager.h"
#include "general_manager.h"

#include <QApplication>
#include <QWidget>

general_manager * General_Manager;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand((int)time(0));
    General_Manager = new general_manager;
    return a.exec();
}
