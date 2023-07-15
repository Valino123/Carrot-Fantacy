#ifndef STARTFROM_H
#define STARTFROM_H

#include <QWidget>
#include <mainwindow.h>
#include "ui_startfrom.h"
QT_BEGIN_NAMESPACE
namespace Ui {class StartFrom;}
QT_END_NAMESPACE
class StartFrom : public QWidget
{
    Q_OBJECT

public:
    explicit StartFrom(QWidget *parent = nullptr);
    ~StartFrom();
    void paintEvent(QPaintEvent *);

private:
    Ui::StartFrom *ui;
};

#endif // STARTFROM_H
