#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Input_mm_zh : public QWidget
{
    Q_OBJECT

public:
    Input_mm_zh(QWidget *parent = nullptr);
    virtual ~Input_mm_zh();
private:
    Ui::Widget * ui;
    QString * mm;
    QString * zh;
    QString * mm_sr;
    QString * zh_sr;
    QTimer * timer;
    bool Number_Input_zh_mm;
};
#endif // WIDGET_H
