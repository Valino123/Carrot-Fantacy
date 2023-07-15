#include "bullet.h"

Bullet::Bullet()
{

}
Bullet:: ~Bullet(){};
Bullet::Bullet(QPoint pos, Enemy* target,Tower* tower):Target(target),Pos_cur(pos),src_tower(tower){}
void Bullet::SetPosition(QPoint Pos_new)
{
    Pos_cur.setX(Pos_new.x());
    Pos_cur.setY(Pos_new.y());
}
QPoint Bullet::GetPosCur() const
{
    return Pos_cur;
}

int Bullet::GetSpeed()
{
    return int(speed);
}

void Bullet::SetTheta(double theta)
{
    this->theta = theta;
}

double Bullet::GetTheta ()const
{
    return theta;
}

int Bullet::GetSize_x() const{return Size_x;}
int Bullet::GetSize_y() const{return Size_y;}
