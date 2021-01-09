#include "com_management.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>

#define DUANKO "COM20"

COM_management::COM_management(QWidget *parent) : QWidget(parent)
{
    COM_Swith = new QString;
    serial = new QSerialPort;
    COM_Buffer_Read = new QByteArray;

    serial->setPortName(DUANKO);
    //设置波特率
    serial->setBaudRate(QSerialPort::Baud9600);
    //设置数据位数
    serial->setDataBits(QSerialPort::Data8);
    //设置奇偶校验
    serial->setParity(QSerialPort::NoParity);
    //设置停止位
    serial->setStopBits(QSerialPort::OneStop);
    //设置流控制
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if(!serial->open(QIODevice::ReadWrite))
    {
        COM_Open = false;
        qDebug() << "no!";
    }else
    {
        COM_Open = true;
        qDebug() << "OK!";
    }
}
COM_management::~COM_management()
{
    delete COM_Swith;
    delete serial;
    delete COM_Buffer_Read;
    delete info;
}
