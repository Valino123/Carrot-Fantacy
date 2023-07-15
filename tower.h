#ifndef TOWER_H
#define TOWER_H
#include <QPoint>
#include <QPainter>
#include <QString>
#include "bullet.h"
#include "Utility.h"
class MainWindow;
class Enemy;
class Bullet;
class Tower
{
public:
    Tower();
    Tower(QPoint pos, MainWindow* game);
    ~Tower();
private:
    int Power = 20;
    int Attack_Interval = 100;
    int Bullet_ini_pos = 28;
    int Interval =0;
    int Range = 150;
    int buyCost = 100;
    int Cost = 150;
    int level = 1;
    int Size_x = 56;
    int Size_y = 25;//level 1
    QString path_TowerLevel = QString(":/pics/t1-1.PNG");
    bool HasBullet;
    QPoint Pos;
    MainWindow* Game;
//    Bullet bullet;
    Enemy* targetcur = nullptr;
    //new new
    QList<Bullet*> BulletList;
    //news
    int Power_Level[3] = {20,30,40};
    int Attack_Interval_Level[3] = {100,80,60};
    int Range_Level[3] = {150,175,200};
    int Cost_Level[3] = {150,200,0};
    int Size_x_Level[3] = {56,63,70};
    int Size_y_Level[3] = {25,35,46};
    int bullet_ini_pos_Level[3] = {28,31,35};
    double Theta;//初始化-90
    QString path_TowerLevel1 = QString(":/pics/t1-1.PNG");
    QString path_TowerLevel2 = QString(":/pics/t1-2.PNG");
    QString path_TowerLevel3 = QString(":/pics/t1-3.PNG");

    QString path_TowerBG = QString(":/pics/tower1_BG.PNG");
    //
public:
    QPoint getPos();
    int getSize_x();
    int getSize_y();
//    void draw(QPainter* painter_Tower) ;//传入鼠标点击点
    void UpdateBullet();
    void SetTarget(Enemy* target);
    //newnew
    Enemy* getTarget(){return targetcur;};
    int getInterval(){return Attack_Interval;}
    void AddBullet(Bullet* bullet){BulletList.push_back(bullet);};
    //news
    void setTheta();
//    void setTheta(Enemy* front);
    int getRange();
    int getCost() {return Cost;}
    int getLevel() {return level;}
    int getSellGold();
    void LevelUp();

    void bullet_removeOne(Bullet* bullet) {BulletList.removeOne(bullet);}
    int getispeed() {return Bullet_ini_pos;}

    friend class MainWindow;
    //
};

#endif // TOWER_H
