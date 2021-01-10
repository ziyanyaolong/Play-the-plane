#include "Input_mm_zh.h"
#include "ui_Input_mm_zh.h"
#include "windows_manager.h"
#include "main_interface.h"
#include "ui_main_interface.h"
#include "com_management.h"
#include "object_manager.h"
#include "general_manager.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <QDebug>
#include <QTimer>
#include <QPushButton>

#define MMSHEDING ""
#define ZHSHEDING ""

extern general_manager * General_Manager;

Input_mm_zh::Input_mm_zh(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    timer = new QTimer;
    mm = new QString;
    zh = new QString;
    mm_sr = new QString;
    zh_sr = new QString;

    Number_Input_zh_mm = false;

    ui->setupUi(this);
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        ui->lineEdit_2->clear();
        ui->lineEdit->clear();
        *mm_sr = "";
        *zh_sr = "";
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
       *mm_sr = ui->lineEdit_2->text();
       *zh_sr = ui->lineEdit->text();
        if(*mm_sr == MMSHEDING && *zh_sr == ZHSHEDING)
        {
            General_Manager->manager->new_main_interface()->show();
            QTimer::singleShot(25,this,[=](){
               close();
            });
        }
    });
    timer->start(250);
     connect(timer,&QTimer::timeout,this,[=](){
         if(General_Manager->COM_m->Read_COM_Open())
         {
             *(General_Manager->COM_m->COM_Buffer_Read) = General_Manager->COM_m->serial->readLine();
             if(*(General_Manager->COM_m->COM_Buffer_Read) != "")
             {
                 switch(General_Manager->COM_m->COM_Buffer_Read->data()[0])
                 {

                 case 'A':
                     if(Number_Input_zh_mm)
                     {
                        Number_Input_zh_mm = false;
                     }else
                    {
                        Number_Input_zh_mm = true;
                    }
                     break;

                 case 'B':
                     if(!Number_Input_zh_mm)
                     {
                         *zh_sr = zh_sr->left(zh_sr->size() - 1);
                         ui->lineEdit->setText(*zh_sr);
                     }else if(Number_Input_zh_mm)
                     {
                         *mm_sr = mm_sr->left(mm_sr->size() - 1);
                         ui->lineEdit_2->setText(*mm_sr);
                     }
                     break;

                 case 'C':
                     ui->pushButton->click();
                     break;

                 case 'D':
                     ui->pushButton_2->click();
                     break;

                 default:
                     for(int i = 0;i < 10; i++)
                     {
                         QString temp_number;
                         temp_number = QString(General_Manager->COM_m->COM_Buffer_Read->data()[0]);
                         if(temp_number == QString::number(i) && !Number_Input_zh_mm)
                         {
                             *zh_sr += General_Manager->COM_m->COM_Buffer_Read->data()[0];
                             ui->lineEdit->setText(*zh_sr);
                         }else if(temp_number == QString::number(i) && Number_Input_zh_mm)
                         {
                             *mm_sr += General_Manager->COM_m->COM_Buffer_Read->data()[0];
                             ui->lineEdit_2->setText(*mm_sr);
                         }
                      }
                     break;
                 }
             }
         }
         });
}

Input_mm_zh::~Input_mm_zh()
{
    delete ui;
    if(mm != nullptr)
    {
        delete mm;
    }
    if(zh != nullptr)
    {
        delete zh;
    }
    if(mm_sr != nullptr)
    {
        delete mm_sr;
        qDebug() << mm_sr;
    }
    if(zh_sr != nullptr)
    {
        delete zh_sr;
    }
    if(timer != nullptr)
    {
        delete timer;
    }
}
