#ifndef ENEMY_H
#define ENEMY_H
#include <QPoint>
#include <QPainter>
#include "mainwindow.h"
class MainWindow;
class Enemy
{
public:
    Enemy();
    Enemy(MainWindow* game);
    void initialize_EnemyFast();
    void initialize_EnemyMid();
    void initialize_EnemySlow();
    ~Enemy();
//    void draw(QPainter* painter_Enemy)  const;
    void ResetPos();
    QPoint GetPosition();
    //new
    void getHurt(int hurt);
    void setX(double x);
    void setY(double y);
    double x() const;
    double y() const;
    void setSpeed(double s);
    //new 1
    bool Alive() {return is_Alive;}
    int GetSize_x1();
    int GetSize_y1();
    int GetSize_x2();
    int GetSize_y2();
    int GetOx();
    int GetOy();
    int GetState();
    int GetMaxState();
    QString GetPath1() {return path1;}
    QString GetPath2() {return path2;}
    int GetTotalBlood() {return Blood_total;}
    int GetCurBlood()  {return Blood_cur;}

    void bullet_push_back(Bullet* bullet) {bulletlist.push_back(bullet);}
    void bullet_removeOne(Bullet* bullet) {bulletlist.removeOne(bullet);}

private:
    int Blood_total = 100;
    int Blood_cur = 100;
    double Speed = 0.8;//像素点/ms
    int Award = 14;
//    int Size_x = 58;
//    int Size_y = 73;//m1
    //new
    bool is_Alive = true;
    int Damage = 1;// damage carrot
    int State = 0;
    int State_max = 60;
    QString path1 = QString(":/pics/m1.PNG");
    QString path2 = QString(":/pics/m2.PNG");
    int Size_x1 = 58;
    int Size_y1 = 66;//m1:smaller one
    int Size_x2 = 58;
    int Size_y2 = 73;//m2:larger one
    double x_pos = 83+79*4;
    double y_pos = 173+77*0+1;

    QList<Bullet*> bulletlist;

    //
//    QPoint Pos = QPoint(83+79*4,173+77*0+1);

    QList<QPoint>::iterator Inflection_next;
    QList<QPoint>::Iterator Inflection_prev;

//    QPoint Inflection_prev;
//    QPoint Inflection_next;
    QList<QPoint> InflectionList;
    MainWindow* Game;

};

#endif // ENEMY_H
