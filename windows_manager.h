#ifndef WINDOWS_MANAGER_H
#define WINDOWS_MANAGER_H

#include <QObject>

#include "Input_mm_zh.h"
#include "main_interface.h"
#include "infrastructure.h"

class windows_manager : public QObject , public infrastructure
{
    Q_OBJECT
public:
    virtual ~windows_manager();

    explicit windows_manager(QObject *parent = nullptr);
    Input_mm_zh * new_Input_mm_zh();
    main_interface * new_main_interface();
    Input_mm_zh * return_Input_mm_zh();
    main_interface * return_main_interface();

    int return_highl() { return highly_; }
    int return_width() { return width_; }

signals:

private:
    Input_mm_zh * a;
    main_interface * b;
};

#endif // WINDOWS_MANAGER_H
