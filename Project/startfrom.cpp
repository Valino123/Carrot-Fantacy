#include "startfrom.h"
#include "ui_startfrom.h"
#include "mainwindow.h"
class MainWindow;


StartFrom::StartFrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartFrom)
{
    ui->setupUi(this);
    setWindowTitle("保卫萝卜");
    connect(ui->pushButton,&QPushButton::clicked,[=]()
    {
        hide();
        MainWindow * mainwindow=new MainWindow(parent);
        mainwindow->show();
    });
}

void StartFrom::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QString path(":/pics/start.jpg");
    painter.drawPixmap(0,0,900,600,path);
}

StartFrom::~StartFrom()
{
    delete ui;
}
