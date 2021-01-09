#ifndef COM_MANAGEMENT_H
#define COM_MANAGEMENT_H

#include <QWidget>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class COM_management : public QWidget
{
    Q_OBJECT
public:
    explicit COM_management(QWidget *parent = nullptr);
    virtual ~COM_management();

    QSerialPortInfo * info;
    QSerialPort * serial;
    QByteArray * COM_Buffer_Read;
    QString * COM_Swith;
    bool Read_COM_Open() { return COM_Open; };
signals:

private:
    bool COM_Open = false;
};

#endif // COM_MANAGEMENT_H
