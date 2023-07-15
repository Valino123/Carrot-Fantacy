#ifndef BLOCK_H
#define BLOCK_H
#include <QPoint>
#include <tower.h>
class Tower;
class Block
{
public:
    Block(QPoint pos);
    ~Block();
    bool IsPath();
    bool IsTower();
    void SetPath();
    void setNoTower() {isTower=false;}
    void SetTower(Tower* T);
    QPoint GetPosition();
    Tower* getTower();
private:
    bool isPath; // 0:非路径，1:路径
    bool isTower;// 0:未建塔，1:建塔
    QPoint Pos;
    Tower* tower;
};

#endif // BLOCK_H
