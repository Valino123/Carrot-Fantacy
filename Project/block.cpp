#include "block.h"

Block::Block(QPoint pos)
{
    isPath = false;
    isTower = false;
    int px = (pos.x()-4)/79*79 + 4;
    int py = (pos.y()-96)/77*77 + 96;//计算block的xy
    Pos.setX(px);
    Pos.setY(py);
}
Block::~Block(){};
bool Block::IsPath(){return isPath;}
bool Block::IsTower(){return isTower;}
void Block::SetPath(){isPath = true;}
void Block::SetTower(Tower* T){isTower = true;tower = T;}
QPoint Block::GetPosition(){return Pos;}
Tower* Block::getTower(){return tower;}
