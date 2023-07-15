#ifndef BULLET_H
#define BULLET_H
#include <QPoint>
#include <tower.h>
class Tower;
class Enemy;
class Bullet
{
public:
    Bullet();
    Bullet(QPoint posprev, Enemy* target, Tower* tower = nullptr);
    ~Bullet();
    int GetSpeed();
    void SetTheta(double theta);
    double GetTheta() const;
    void SetPosition(QPoint Pos_new);//维护中心的位置
//    QPoint GetPosPrev() const;
    QPoint GetPosCur() const;
    int GetSize_x() const;
    int GetSize_y() const;
    Enemy* GetTarget(){return Target;}
    Tower* GetSrcTower() {return src_tower;}
//    int IsFirst(){return First_draw;}
//    void SetFirst(){First_draw = 0;}
private:
//    QPoint Pos_prev;
    Enemy* Target;
    QPoint Pos_cur;//中心位置
    double theta = 90;
    double speed = 10;
    int Size_x = 49;
    int Size_y = 25;
//    int First_draw = 1;
    Tower* src_tower;
};

#endif // BULLET_H
