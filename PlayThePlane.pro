QT       += core gui \
    quick
QT       += serialport
QT       += multimedia
CONFIG += resources_big
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Input_mm_zh.cpp \
    bass_object.cpp \
    bullet.cpp \
    com_management.cpp \
    enemy.cpp \
    general_manager.cpp \
    infrastructure.cpp \
    main.cpp \
    main_interface.cpp \
    object_manager.cpp \
    oneself.cpp \
    windows_manager.cpp

HEADERS += \
    Input_mm_zh.h \
    bass_object.h \
    bullet.h \
    com_management.h \
    enemy.h \
    general_manager.h \
    infrastructure.h \
    main_interface.h \
    object_manager.h \
    oneself.h \
    windows_manager.h

FORMS += \
    Input_mm_zh.ui \
    main_interface.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
