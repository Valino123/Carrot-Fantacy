#include "tower.h"
#include "enemy.h"
#include <QPoint>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
Tower::Tower(){};
Tower::~Tower(){};
QPoint Tower:: getPos()
{
    return Pos;
}
Tower::Tower(QPoint pos, MainWindow* game):Pos(pos),Game(game),HasBullet(false)
{
//    Bullet b(pos);
//    bullet = b;
};

void Tower::setTheta()
{
    if(targetcur != NULL){
        int ox = Pos.x()+79/2;
        int oy = Pos.y()+77/2;
        int ofx = targetcur->GetOx();
        int ofy = targetcur->GetOy();
        Theta = atan2(ofy-oy,ofx-ox);
        Theta = Theta*180.0/3.1415926;
    }else{
        //Theta = -90;
        //垂直指向最近路径;
    }
}
//void Tower::setTheta(Enemy* front)
//{
//    int ox = Pos.x()+79/2;
//    int oy = Pos.y()+77/2;
//    int ofx = front->GetOx();
//    int ofy = front->GetOy();
//    Theta = atan2(ofy-oy,ofx-ox);
//    Theta = Theta*180.0/3.1415926;
//}

//void Tower::draw(QPainter* painter_Tower)
//{
//    Interval++;
//    painter_Tower->save();

//    int ox = Pos.x()+79/2;
//    int oy = Pos.y()+77/2;
//    int nx = ox - Size_x/2;
//    int ny = oy - Size_y/2;

//    qDebug("paint tower");
//    painter_Tower->drawPixmap(ox-30,oy-30,60,60,path_TowerBG);

//    // if inside range, rotate
//    if(true){
//        //set rotation center
//        painter_Tower->translate(ox,oy);
//        painter_Tower->rotate(Theta);
//        // recovery rotation center
//        painter_Tower->translate(-1*ox,-1*oy);
//    }
//    //paint
//    painter_Tower->drawPixmap(nx,ny,Size_x,Size_y,path_TowerLevel);
//    qDebug("paint tower finish");
//    //lettuce 77*77
//    painter_Tower->restore();

//    //draw bullet
//    if(HasBullet&&Interval==100){
//        Interval=0;
//        painter_Tower->save();
//        int pos_bx = bullet.GetPosCur().x();
//        int pos_by = bullet.GetPosCur().y();
//        int size_bx = bullet.GetSize_x();
//        int size_by = bullet.GetSize_y();
//        QString path_b(":/pics/b1-1.PNG");
//        int o_bx = pos_bx + size_bx/2;
//        int o_by = pos_by + size_by/2;
//        //set rotation center
//        painter_Tower->translate(o_bx,o_by);
//        //set theta
//        painter_Tower->rotate(bullet.GetTheta());
//        // recovery rotation center
//        painter_Tower->translate(-1*o_bx,-1*o_by);
//        //paint
//        painter_Tower->drawPixmap(pos_bx,pos_by,size_bx,size_by,path_b);
//        painter_Tower->restore();
//    }

//}

int Tower::getSize_x()
{
    return Size_x;
}
int Tower::getSize_y()
{
    return Size_y;
}
void Tower::UpdateBullet()
{
    foreach(Bullet* bullet, BulletList){
        int x1 = bullet->GetPosCur().x();                 //x1:子弹当前位置
        int y1 = bullet->GetPosCur().y();
        int x2 = bullet->GetTarget()->GetOx();            //x2:目标当前位置
        int y2 = bullet->GetTarget()->GetOy();
        int speed = bullet->GetSpeed();

        double theta = atan2(y2-y1,x2-x1);

        int x3,y3;
        if(x2 > x1)
            x3 = int(x1+speed*fabs(cos(theta)));
        else
            x3 = int(x1-speed*fabs(cos(theta)));
        if(y2 > y1)
            y3 = int(y1+speed*fabs(sin(theta)));
        else
            y3 = int(y1-speed*fabs(sin(theta)));
        bullet->SetTheta(theta);
        bullet->SetPosition(QPoint(x3,y3));

        if(Collision(bullet->GetPosCur(),30,QPoint(bullet->GetTarget()->GetOx(),bullet->GetTarget()->GetOy()),0)){
            bullet->GetTarget()->bullet_removeOne(bullet);
            bullet->GetTarget()->getHurt(Power);
            BulletList.removeOne(bullet);
            delete bullet;
        }
    }

}
void Tower::SetTarget(Enemy* target)
{
    this->targetcur = target;
}

int Tower::getRange()
{
    return this->Range;
}

void Tower::LevelUp()
{
    level++;
    Power           = Power_Level[level-1];
    Attack_Interval = Attack_Interval_Level[level-1];
    Range           = Range_Level[level-1];
    Cost            = Cost_Level[level-1];
    Size_x          = Size_x_Level[level-1];
    Size_y          = Size_y_Level[level-1];
    Bullet_ini_pos  = bullet_ini_pos_Level[level-1];
    if(level==1) path_TowerLevel = path_TowerLevel1;
    else if(level==2) path_TowerLevel = path_TowerLevel2;
    else path_TowerLevel = path_TowerLevel3;
}

int Tower::getSellGold()
{
    if(level==1) return int(buyCost*0.8);
    else if(level==2) return int((buyCost+Cost_Level[0])*0.8);
    else return int((buyCost+Cost_Level[0]+Cost_Level[1])*0.8);
}
