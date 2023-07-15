#include "enemy.h"
#include <math.h>
#include <QDebug>
Enemy::Enemy(MainWindow* game):Game(game)
{
    //initialize InflectionList
    InflectionList.push_back(QPoint(399, 173));//4 0
    InflectionList.push_back(QPoint(399, 250));//4 1
    InflectionList.push_back(QPoint(83 , 250));//0 1
    InflectionList.push_back(QPoint(83 , 481));//0 4
    InflectionList.push_back(QPoint(162, 481));//1 4
    InflectionList.push_back(QPoint(162, 558));//1 5
    InflectionList.push_back(QPoint(399, 558));//4 5
    InflectionList.push_back(QPoint(399, 404));//4 3
    InflectionList.push_back(QPoint(636, 404));//7 3
    InflectionList.push_back(QPoint(636, 481));//7 4
    InflectionList.push_back(QPoint(794, 481));//9 4
    InflectionList.push_back(QPoint(794, 173));//9 0
    InflectionList.push_back(QPoint(636, 173));//7 0
    Inflection_prev = InflectionList.begin();
    Inflection_next = Inflection_prev+1;
//    Pos((*Inflection_prev).x(),(*Inflection_prev).y());
}
void Enemy::initialize_EnemyFast()
{
    Blood_total = 100;
    Blood_cur = 100;
    Speed = 1.4;
    Award = 14;
    is_Alive = true;
    Damage = 1;
    State = 0;
    State_max = 60;
    path1 = QString(":/pics/m1.PNG");
    path2 = QString(":/pics/m2.PNG");
    Size_x1 = 58;
    Size_y1 = 66;
    Size_x2 = 58;
    Size_y2 = 73;
}
void Enemy::initialize_EnemyMid()
{
    Blood_total = 150;
    Blood_cur = 150;
    Speed = 1.0;
    Award = 14;
    is_Alive = true;
    Damage = 1;
    State = 0;
    State_max = 60;
    path1 = QString(":/pics/m3.PNG");
    path2 = QString(":/pics/m4.PNG");
    Size_x1 = 56;
    Size_y1 = 70;
    Size_x2 = 56;
    Size_y2 = 72;
}
void Enemy::initialize_EnemySlow()
{
    Blood_total = 200;
    Blood_cur = 200;
    Speed = 0.8;
    Award = 14;
    is_Alive = true;
    Damage = 1;
    State = 0;
    State_max = 60;
    path1 = QString(":/pics/m5.PNG");
    path2 = QString(":/pics/m6.PNG");
    Size_x1 = 65;
    Size_y1 = 72;
    Size_x2 = 65;
    Size_y2 = 74;
}
//overload
Enemy::~Enemy(){};

void Enemy::ResetPos()
{
    double Dis = Speed;
    State++;
//    qDebug("Position: %f %f",x(),y());
//    qDebug("Prev    : %d %d",(*Inflection_prev).x(),(*Inflection_prev).y());
//    qDebug("Next    : %d %d",(*Inflection_next).x(),(*Inflection_next).y());
//    qDebug("End     : %d %d",(*(InflectionList.end()-1)).x(),(*(InflectionList.end()-1)).y());
    if(State >= State_max) State = 0;
    if((*Inflection_prev).x() == (*Inflection_next).x())
    {
        if((*Inflection_next).y()-y() >= Dis){
            setY(y()+Dis);
        }else if((*Inflection_next).y()-y() <= Dis*(-1)){
            setY(y()-Dis);
        }else{
            double Dis_r = Dis - std::abs((*Inflection_next).y()-y());
            setY((*Inflection_next).y());
            // change inflection to another
            if(Inflection_next != InflectionList.end()-1)
            {
                Inflection_next++;
                Inflection_prev++;
                if((*Inflection_next).x() > (*Inflection_prev).x())
                    setX(x() + Dis_r);
                else
                    setX(x() - Dis_r);
            }
            else
            {
                is_Alive = false;
                Game->getDamage(Damage);
                Game->removeEnemy(this);                
            }
        }
    }
    else{
        if((*Inflection_next).x()-x() >= Dis){
            setX(x()+Dis);
        }else if((*Inflection_next).x()-x() <= Dis*(-1)){
            setX(x()-Dis);
        }else{
            double Dis_r = Dis - std::abs((*Inflection_next).x()-x());
            setX((*Inflection_next).x());
            // change inflection to another
            if(Inflection_next != InflectionList.end()-1){
                Inflection_next++;
                Inflection_prev++;
                if((*Inflection_next).y() > (*Inflection_prev).y())
                    setY(y() + Dis_r);
                else
                    setY(y() - Dis_r);
            }else{
                is_Alive = false;
                Game->getDamage(Damage);
                Game->removeEnemy(this);
            }
        }
    }
}

//void Enemy::draw(QPainter* painter_Enemy)const
//{
//    if(is_Alive)
//    {
//        painter_Enemy->save();

//        if(State < State_max/2)
//        {
//            painter_Enemy->drawPixmap(int(x()+(Size_x2-Size_x1)/2),int(y()+(Size_y2-Size_y1)/2),Size_x1,Size_y1,path1);
//        }
//        else
//        {
//            painter_Enemy->drawPixmap(int(x()),int(y()),Size_x2,Size_y2,path2);
//        }
//        const int Blood_Width = 3;
//        const int Blood_Length = Size_x2;

//        painter_Enemy->setPen(Qt::NoPen);
//        painter_Enemy->setBrush(Qt::blue);
//        QRect Blood_Background_rect(int(x()),int(y()+Size_y2),Blood_Length,Blood_Width);
//        painter_Enemy->drawRect(Blood_Background_rect);

//        painter_Enemy->setBrush(Qt::green);
//        QRect Blood_current_rect(int(x()),int(y()+Size_y2),Blood_Length*Blood_cur/Blood_total,Blood_Width);
//        painter_Enemy->drawRect(Blood_current_rect);

//        qDebug("paint monster finish");
//        painter_Enemy->restore();
//    }
//}

QPoint Enemy::GetPosition()
{
    return QPoint(int(x()),int(y()));
}

void Enemy::getHurt(int hurt)
{
    if(Blood_cur > hurt)
    {
        Blood_cur -= hurt;
        return;
    }
    else
    {
        //TODO:执行死亡动画
        //
        foreach(Bullet* bullet,bulletlist)
        {
            bullet->GetSrcTower()->bullet_removeOne(bullet);
            this->bullet_removeOne(bullet);
            delete bullet;
        }

        is_Alive = false;
        Game->getCoin(Award);
        Game->removeEnemy(this);
    }
}

void Enemy::setX(double x)
{
    x_pos = x;
}
void Enemy::setY(double y)
{
    y_pos = y;
}
double Enemy::x() const
{
    return x_pos;
}
double Enemy::y() const
{
    return y_pos;
}
void Enemy::setSpeed(double s)
{
    Speed = s;
}

int Enemy::GetSize_x1()
{
    return Size_x1;
}
int Enemy::GetSize_y1()
{
    return Size_y1;
}
int Enemy::GetSize_x2()
{
    return Size_x2;
}
int Enemy::GetSize_y2()
{
    return Size_y2;
}

int Enemy::GetState()
{
    return State;
}
int Enemy::GetMaxState()
{
    return State_max;
}

int Enemy::GetOx()
{
//    if(State < State_max/2)
//        return (int)x_pos + (Size_x2+Size_x1)/2;
//    else
//        return (int)x_pos + Size_x2/2;
    return int(x_pos+Size_x2/2);
}

int Enemy::GetOy()
{
//    if(State < State_max/2)
//        return (int)y_pos + (Size_y2+Size_y1)/2;
//    else
//        return (int)y_pos + Size_y2/2;
    return int(y_pos + Size_y2/2);
}
