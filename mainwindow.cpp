#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
#include <QTimerEvent>
#include <QTimer>
#include <QDebug>
#include <QTime>
#include <assert.h>
#include<startfrom.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(960,640);
    ui->setupUi(this);
    //initialize BlockList
    for(int idx = -1; idx <= 10; idx++){
        for(int idy = -1; idy <=5; idy++){
            int px = 83 + 79*idx;
            int py = 173 + 77*idy;
            Block* block = new Block(QPoint(px,py));
            if(idy == -1){
                if(idx == 6 || idx == 4)
                    block->SetPath();
            }else if(idy == 0){
                if(idx == 4|| idx==6||idx == 7 || idx==8 || idx == 9)
                    block->SetPath();
            }else if(idy == 1){
                if(idx == 0|| idx == 1 || idx == 2|| idx == 3|| idx == 4|| idx == 9)
                    block->SetPath();
            }else if(idy == 2){
                if(idx == 0|| idx == 9)
                    block->SetPath();
            }else if(idy == 3){
                if(idx == 0|| idx == 4|| idx == 5||idx == 6|| idx == 7|| idx == 9)
                    block->SetPath();
            }else if(idy == 4){
                if(idx == 0|| idx == 1|| idx ==4 || idx == 7|| idx==8||idx==9)
                    block->SetPath();
            }else if(idy == 5){
                if(idx==1||idx==2||idx==3||idx==4)
                    block->SetPath();
            }
            BlockList.push_back(block);
        }
    }
    //initialize EnemyList;
//    Enemy* Enemy1 = new Enemy(this);
//    Enemy* Enemy2 = new Enemy(this);
//    Enemy* Enemy3 = new Enemy(this);
//    Enemy1->initialize_EnemyFast();
//    Enemy2->initialize_EnemyMid();
//    Enemy3->initialize_EnemySlow();
//    EnemyList.push_back(Enemy1);
//    EnemyList.push_back(Enemy2);
//    EnemyList.push_back(Enemy3);
    Player_wave_info = new Wave(this);
    Player_wave_info->initialize_Wave();
    tmp_EnemyList = Player_wave_info->get_Wave(Player_wave);

    // timer complete action
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()), this, SLOT(UpdateEnemy()));
    connect(timer,SIGNAL(timeout()), this, SLOT(UpdateTower()));
    connect(timer,SIGNAL(timeout()), this, SLOT(inputEnemy()));
    timer->start(10);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
{
    QPainter painter_BG(this);
    QString path1(":/pics/BG.PNG");//960*640
    painter_BG.drawPixmap(0,0,960,640,path1);
    QPainter painter_ROAD(this);
//    painter_ROAD.setOpacity(0.2);
    QString path2(":/pics/Road4.PNG");//960*475
    painter_ROAD.drawPixmap(0,166,960,475,path2);
    QPainter painter_CARROT(this);
    QString path3(":/pics/c-0.PNG");//75*106, 6,-1
    QString path3_1(":/pics/Hp.png");
    painter_CARROT.drawPixmap(83+79*6,173+77*(-1)+30+106,72,37,path3_1);
    painter_CARROT.drawPixmap(83+79*6, 173+77*(-1)+30,75,106,path3);

    if(Player_Hp==10)
    {
        paintSingleNum(&painter_CARROT,83+79*6+28,173+77*(-1)+30+106,23,30,1);
        paintSingleNum(&painter_CARROT,83+79*6+42,173+77*(-1)+30+106,23,30,0);
    }
    else
    {
        paintNumber(&painter_CARROT,83+79*6+35,173+77*(-1)+30+106,23,30,Player_Hp);
    }
    QPainter painter(this);
    QPainter painter_StartPoint(this);
    QString path4(":/pics/startPoint.PNG");//start point 94*73; 4,-1
    painter_StartPoint.drawPixmap(83+79*4, 173+77*(-1),94,73,path4);
    //
    QPainter painter_StatusBar(this);
    QString path5(":/pics/StatusBar.png");
    painter_StatusBar.drawPixmap(0,0,960,80,path5);
    QString path6(":/pics/waves.png");
    painter_StatusBar.drawPixmap(300,10,277,60,path6);
    paintSingleNum(&painter_StatusBar,323,17,27,36,0);
    paintSingleNum(&painter_StatusBar,371,17,27,36,Player_wave);
    paintSingleNum(&painter_StatusBar,428,17,27,36,0);
    paintSingleNum(&painter_StatusBar,453,17,27,36,Player_wave_info->getMaxWave());

    QPainter painter_coin(this);
    paintNumber(&painter_coin,80,10,30,40,Player_coin);
    //


    foreach(Tower* tower, TowerList)
    {
        if(!EnemyList.empty())
        {
            tower->setTheta();
        }
        draw_Tower(&painter,tower);
        draw_Bullet(&painter,tower);
    }

    foreach(Enemy* enemy, EnemyList)
        draw_Enemy(&painter,enemy);

    foreach(DrawList* drawlist, Filmlist)
    {
        DrawInfo* info = drawlist->front();
        painter.drawPixmap(info->x,info->y,info->size_x,info->size_y,info->path);
        drawlist->pop_front();
        delete info;
        if(drawlist->isEmpty())
        {
            Filmlist.removeOne(drawlist);
            is_building_filming = false;
        }
    }
    if(!is_stop)
    {
        painter.drawPixmap(700,10,56,60,QString(":/pics/tostop.PNG"));
    }
    if(is_stop)
    {
        painter.drawPixmap(700,10,56,60,QString(":/pics/tobegin.PNG"));
    }
    if(is_lose)
    {
        timer->stop();
        QPainter painter_lose(this);
        painter_lose.drawPixmap(221,145,519,351,QString(":/pics/lose.PNG"));
        painter_lose.drawPixmap(375,390,180,44,QString(":/pics/button.jpg"));
    }
    if(is_win)
    {
        timer->stop();
        QPainter painter_win(this);
        painter_win.drawPixmap(221,145,519,351,QString(":/pics/win.PNG"));
        painter_win.drawPixmap(375,390,180,44,QString(":/pics/button.jpg"));
    }
    if(is_win||is_lose)//显示波数
    {
        if(is_lose)
        {
            Player_wave--;
        }
        QPainter painter_num(this);
        painter_num.drawPixmap(310,285,300,31,QString(":/pics/over.PNG"));
        if(Player_wave<10)
        {
            paintNumber(&painter_num,438,285,21,28,0);//第一位数
        }
        if(Player_wave>=10)
        {
            paintNumber(&painter_num,438,285,21,28,1);//第一位数
        }
        paintNumber(&painter_num,470,285,21,28,Player_wave%10);
    }
    if(is_building)
    {
        if(!is_building_filming)
        {
            QPainter painter_Tower(this);
            int memory_x = last_press_x;
            int memory_y = last_press_y < 100 ? last_press_y+79:last_press_y-78;
            if (canBuyTower1()) painter_Tower.drawPixmap(memory_x,memory_y,78,78,QString(":/pics/CanClick1.PNG"));
            else painter_Tower.drawPixmap(memory_x,memory_y,78,78,QString(":/pics/CanClick0.PNG"));
        }
    }

    if(is_upgrading)
    {
        if(!is_building_filming)
        {
            QPainter painter_Tower(this);
            int r = chosen_block->getTower()->getRange();
            painter_Tower.drawPixmap(last_press_x-r,last_press_y-r,2*r,2*r,QString(":/pics/AttackRange.PNG"));
            int tmp_level = chosen_block->getTower()->getLevel();

            if(tmp_level==3)
            {
                painter_Tower.drawPixmap(up_x,up_y,76,76,QString(":/pics/Btn_ReachHighestLevel.PNG"));
                painter_Tower.drawPixmap(down_x,down_y,76,76,QString(":/pics/Btn_SellTower.png"));
                paintNumber(&painter_Tower,down_x+30,down_y+52,15,20,chosen_block->getTower()->getSellGold());
            }
            else
            {
                if (canUpgradeTower1()) painter_Tower.drawPixmap(up_x,up_y,76,76,QString(":/pics/Btn_CanUpLevel.png"));
                else painter_Tower.drawPixmap(up_x,up_y,76,76,QString(":/pics/Btn_CantUpLevel.png"));
                painter_Tower.drawPixmap(down_x,down_y,76,76,QString(":/pics/Btn_SellTower.png"));
                paintNumber(&painter_Tower,up_x+30,up_y+52,15,20,chosen_block->getTower()->getCost());
                paintNumber(&painter_Tower,down_x+30,down_y+52,15,20,chosen_block->getTower()->getSellGold());
            }
        }
    }
}




void MainWindow::mousePressEvent(QMouseEvent* event)
{
    QPoint pos = event->pos();
    if(event->button() == Qt::LeftButton)
    {
        QPainter painter_Tower(this);
        int px1=375;//begin:to out
        int py1=390;
        int px2=555;
        int py2=434;
        if(is_win==true||is_lose==true)
        {
            if(pos.x()>=px1&&pos.y()>=py1&&pos.x()<=px2&&pos.y()<=py2)
            {
                out();
            }
        }//end:to out
        int xstop1 = 700;//begin 暂停
        int xstop2 = 756;
        int ystop1 = 10;
        int ystop2 = 70;
        if(pos.x()>=xstop1&&pos.y()>=ystop1&&pos.x()<=xstop2&&pos.y()<=ystop2)
        {
            QPainter painter;
            if(is_stop==false)
            {
                is_stop = true;
                return;
            }
            if(is_stop==true)
            {
                is_stop = false;
                return;
            }
        }//end 暂停
        int px = (pos.x()-4)/79*79 + 4;
        int py = (pos.y()-96)/77*77 + 96;//计算block的xy
        if((!is_building)&&(!is_upgrading)){
             foreach(Block* block, BlockList){
                if(block->GetPosition().x() == px && block->GetPosition().y() == py){
                    if(block->IsPath()==false&&block->IsTower()==false){
                        into_building(px,py,block);
                        DrawList* BuyTowerList = new DrawList;
                        QString path;
                        if (canBuyTower1()) path = QString(":/pics/CanClick1.PNG");
                        else path = QString(":/pics/CanClick0.PNG");
                        int tmp_y = py < 100? py+79+39 : py-39;
                        BuyTowerList->GenerateCircleList(px+39,tmp_y,0,39,15,true,path);
                        Filmlist.push_back(BuyTowerList);
                        is_building_filming = true;
                        break;
                    }
                    if(block->IsPath()==false&&block->IsTower()==true){
                        int up_x1,up_y1,down_x1,down_y1;
                        int last_press_x1 = px+79/2,last_press_y1 = py+77/2;
                        if(last_press_y1<=90)
                        {
                            if(last_press_x1>960-90)
                            {
                                up_x1   = last_press_x1-79-38; up_y1   = last_press_y1-38;
                                down_x1 = last_press_x1-38; down_y1 = last_press_y1+77-38;
                            }
                            else
                            {
                                up_x1   = last_press_x1+79-38; up_y1   = last_press_y1-38;
                                down_x1 = last_press_x1-38; down_y1 = last_press_y1+77-38;
                            }
                        }
                        else if(last_press_y1>=640-90)
                        {
                            up_x1   = last_press_x1-38; up_y1   = last_press_y1-77-38;
                            down_x1 = last_press_x1+79-38; down_y1 = last_press_y1-38;
                        }
                        else
                        {
                            up_x1   = last_press_x1-38; up_y1   = last_press_y1-77-38;
                            down_x1 = last_press_x1-38; down_y1 = last_press_y1+77-38;
                        }
                        into_upgrading(last_press_x1,last_press_y1,block,up_x1,up_y1,down_x1,down_y1);
                        DrawList* show_Range = new DrawList;
                        show_Range->GenerateCircleList(last_press_x,last_press_y,0,chosen_block->getTower()->getRange(),
                                                       15,true,QString(":/pics/AttackRange.PNG"));
                        Filmlist.push_back(show_Range);
                        is_building_filming = true;
                        break;
                    }
                }
            }
        }
        else if(is_building)
        {
            int memory_x = last_press_x;
            int memory_y = last_press_y < 100 ? last_press_y+79:last_press_y-78;
            if(pos.x()-memory_x<=76 && pos.x()-memory_x>=0 && pos.y()-memory_y<=78 && pos.y()-memory_y>=0 && canBuyTower1())
            {
                BuyTower1(last_press_x,last_press_y,chosen_block);
            }
            out_building();
        }
        else if(is_upgrading)
        {
            int tmp_level = chosen_block->getTower()->getLevel();

            if(tmp_level==3)
            {
                if(pos.x()-down_x<=76 && pos.y()-down_y<=76 && pos.x()-down_x>=0 && pos.y()-down_y>=0)
                {
                    SellTower1();
                }                          
            }
            else
            {
                if(pos.x()-up_x<=76 && pos.y()-up_y<=76 && pos.x()-up_x>=0 && pos.y()-up_y>=0 && canUpgradeTower1())
                {
                    UpgradeTower1();
                }
                else if(pos.x()-down_x<=76 && pos.y()-down_y<=76 && pos.x()-down_x>=0 && pos.y()-down_y>=0)
                {
                    SellTower1();
                }
            }
            DrawList* disappear_Range = new DrawList;
            disappear_Range->GenerateCircleList(last_press_x,last_press_y,0,chosen_block->getTower()->getRange(),
                                           15,false,QString(":/pics/AttackRange.PNG"));
            Filmlist.push_back(disappear_Range);
            out_upgrading();
        }


        update();
    }
};

void MainWindow::UpdateEnemy()
{
    if(!is_stop){
        qDebug("update enemy");
        foreach(Enemy* enemy, EnemyList){
            enemy->ResetPos();
        }
    }
    update();
}

void MainWindow::UpdateTower()
{
    // qDebug("update bullet");
    if(!is_stop){
        if (AttackInterval_count++ >=3600000) AttackInterval_count = 0;
        qDebug("count = %d", AttackInterval_count);

        foreach(Tower* tower, TowerList){
            tower->SetTarget(nullptr);
            if(!EnemyList.empty()){
                foreach(Enemy* enemy, EnemyList){
                    if(Collision(tower->getPos(),tower->getRange(),enemy->GetPosition(),40)){
                        tower->SetTarget(enemy);
                        break;
                    }
                }
            }
            if(AttackInterval_count % tower->getInterval() == 0){
                if(tower->getTarget()!=nullptr)
                {
                    Bullet* bul = new Bullet(tower->getPos(),tower->getTarget(),tower);
                    //                int pos_bul_ox = tower->getPos().x()+tower->getSize_x();
                    //                int pos_bul_oy = tower->getPos().y()+tower->getSize_y()/2;
                    //                int pos_bul_x = pos_bul_ox-bul->GetSize_x()/2;
                    //                int pos_bul_y = pos_bul_oy-bul->GetSize_y()/2;
                    int t_ox = tower->getPos().x()+tower->getSize_x()/2;
                    int t_oy = tower->getPos().y()+tower->getSize_y()/2;
                    int e_ox = tower->getTarget()->GetOx();
                    int e_oy = tower->getTarget()->GetOy();
                    double ini_theta = atan2(e_oy-t_oy,e_ox-t_ox);
                    int pos_bul_ox, pos_bul_oy;
                    if(e_ox > t_ox)
                        pos_bul_ox = t_ox + (int)(fabs(cos(ini_theta))*(tower->getSize_x()/2+bul->GetSize_x()/2));
                    else
                        pos_bul_ox = t_ox - (int)(fabs(cos(ini_theta))*(tower->getSize_x()/2+bul->GetSize_x()/2));
                    if(e_oy > t_oy)
                        pos_bul_oy = t_oy + (int)(fabs(sin(ini_theta))*(tower->getSize_x()/2+bul->GetSize_x()/2));
                    else
                        pos_bul_oy = t_oy - (int)(fabs(sin(ini_theta))*(tower->getSize_x()/2+bul->GetSize_x()/2));
                    bul->SetPosition(QPoint(pos_bul_ox,pos_bul_oy));
                    tower->AddBullet(bul);
                    tower->getTarget()->bullet_push_back(bul);
                }
            }
            tower->UpdateBullet();
        }
    }

    update();
}

// new
void MainWindow::inputEnemy()
{
    if(!tmp_EnemyList.empty()&& !is_stop)
    {
        input_Clock++;
        if(input_Clock == 100)
        {
            Enemy* tmp_Enemy = tmp_EnemyList.front();
            EnemyList.push_back(tmp_Enemy);
            tmp_EnemyList.pop_front();
            input_Clock = 0;
        }
    }
    update();
}

void MainWindow::getCoin(int award)
{
    Player_coin += award;
}

void MainWindow::getDamage(int damage)
{
    Player_Hp -= damage;
    if(Player_Hp <= 0)
    {
        //TODO: game lose
        is_lose=true;
    }
}

void MainWindow::removeEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    EnemyList.removeOne(enemy);
    delete enemy;
    if(EnemyList.empty()&&tmp_EnemyList.empty())
    {
        Player_wave++;
        if(Player_wave > 3)
        {
            //TODO: game win!
            is_win=true;
        }
        else
        {
            input_Clock = -200;
            tmp_EnemyList = Player_wave_info->get_Wave(Player_wave);
        }
    }
}

void MainWindow::paintNumber(QPainter *Painter,int x,int y,int size_x,int size_y,int num)
{
    if(num >= 1000) num = 999;
    if(num < 10)
    {
        paintSingleNum(Painter,x,y,size_x,size_y,num);
    }
    else if(num < 100)
    {
        paintSingleNum(Painter,x,y,size_x,size_y,num/10);
        paintSingleNum(Painter,x+size_x,y,size_x,size_y,num%10);
    }
    else
    {
        paintSingleNum(Painter,x,y,size_x,size_y,num/100);
        paintSingleNum(Painter,x+size_x,y,size_x,size_y,(num%100)/10);
        paintSingleNum(Painter,x+size_x*2,y,size_x,size_y,num%10);
    }
}

void MainWindow::paintSingleNum(QPainter *Painter,int x,int y,int size_x,int size_y,int num)
{
    if(num>=10) num = 9;
    switch (num) {
        case 0 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite0.png")); break;
        case 1 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite1.png")); break;
        case 2 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite2.png")); break;
        case 3 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite3.png")); break;
        case 4 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite4.png")); break;
        case 5 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite5.png")); break;
        case 6 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite6.png")); break;
        case 7 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite7.png")); break;
        case 8 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite8.png")); break;
        case 9 : Painter->drawPixmap(x,y,size_x,size_y,QString(":/pics/numwhite9.png")); break;
    }
}

bool MainWindow::canBuyTower1()
{
    if (Player_coin >= 100) return true;
    else return false;
}
bool MainWindow::canUpgradeTower1()
{
    assert(is_upgrading);
    if (Player_coin >= chosen_block->getTower()->getCost()) return true;
    else return false;
}
void MainWindow::BuyTower1(int px,int py,Block* block)
{
    Player_coin -= 100;
    Tower* T = new Tower(QPoint(px,py),this);
    TowerList.push_back(T);
    block->SetTower(T);
}
void MainWindow::UpgradeTower1()
{
    Player_coin -= chosen_block->getTower()->getCost();
    chosen_block->getTower()->LevelUp();
}

void MainWindow::into_building(int x,int y,Block* b)
{
    is_building = true;
    last_press_x = x;
    last_press_y = y;
    chosen_block = b;
}
void MainWindow::out_building()
{
    is_building = false;
}
void MainWindow::into_upgrading(int x,int y,Block* b,int up1,int up2,int down1,int down2)
{
    is_upgrading = true;
    last_press_x = x;
    last_press_y = y;
    chosen_block = b;
    up_x = up1;
    up_y = up2;
    down_x = down1;
    down_y = down2;
}
void MainWindow::out_upgrading()
{
    is_upgrading = false;
}
void MainWindow::SellTower1()
{
    Tower* tmp = chosen_block->getTower();
    Player_coin += tmp->getSellGold();
    TowerList.removeOne(tmp);
    chosen_block->setNoTower();
    delete tmp;
}


void MainWindow::draw_Enemy(QPainter* painter_Enemy,Enemy* enemy) const
{
    if(enemy->Alive())
    {
        painter_Enemy->save();

        if(enemy->GetState() < enemy->GetMaxState()/2)
        {
            painter_Enemy->drawPixmap(int(enemy->x()+(enemy->GetSize_x2()-enemy->GetSize_x1())/2),int(enemy->y()+(enemy->GetSize_y2()-enemy->GetSize_y1())/2),enemy->GetSize_x1(),enemy->GetSize_y1(),enemy->GetPath1());
        }
        else
        {
            painter_Enemy->drawPixmap(int(enemy->x()),int(enemy->y()),enemy->GetSize_x2(),enemy->GetSize_y2(),enemy->GetPath2());
        }
        const int Blood_Width = 3;
        const int Blood_Length = enemy->GetSize_x2();

        painter_Enemy->setPen(Qt::NoPen);
        painter_Enemy->setBrush(Qt::blue);
        QRect Blood_Background_rect(int(enemy->x()),int(enemy->y()+enemy->GetSize_y2()),Blood_Length,Blood_Width);
        painter_Enemy->drawRect(Blood_Background_rect);

        painter_Enemy->setBrush(Qt::green);
        QRect Blood_current_rect(int(enemy->x()),int(enemy->y()+enemy->GetSize_y2()),Blood_Length*enemy->GetCurBlood()/enemy->GetTotalBlood(),Blood_Width);
        painter_Enemy->drawRect(Blood_current_rect);

        // qDebug("paint monster finish");
        painter_Enemy->restore();
    }
}

void MainWindow::draw_Tower(QPainter* painter_Tower,Tower* tower)
{
    //    tower->Interval++;
        painter_Tower->save();
        // ?
    //    int ox = tower->Pos.x()+tower->getSize_x()/2;
    //    int oy = tower->Pos.y()+tower->getSize_y()/2;
    //    int nx = tower->Pos.x();
    //    int ny = tower->Pos.y();

        int ox = tower->Pos.x()+79/2;
        int oy = tower->Pos.y()+77/2;
        int nx = ox - tower->Size_x/2;
        int ny = oy - tower->Size_y/2;


        // qDebug("paint tower");
        painter_Tower->drawPixmap(ox-30,oy-30,60,60,tower->path_TowerBG);

        //set rotation center
        painter_Tower->translate(ox,oy);
        painter_Tower->rotate(tower->Theta);
        // recovery rotation center
        painter_Tower->translate(-1*ox,-1*oy);

        //paint
        painter_Tower->drawPixmap(nx,ny,tower->getSize_x(),tower->getSize_y(),tower->path_TowerLevel);
//        painter_Tower->rotate(-1*tower->Theta);
        // qDebug("paint tower finish");
        //lettuce 77*77
        painter_Tower->restore();

        //draw bullet
//        foreach(Bullet* bullet, tower->BulletList){
//             qDebug("Paint Bullet");
//            painter_Tower->save();
//            int pos_bx = bullet->GetPosCur().x();
//            int pos_by = bullet->GetPosCur().y();
//            int size_bx = bullet->GetSize_x();
//            int size_by = bullet->GetSize_y();
//            QString path_b(":/pics/b1-1.PNG");
//            int o_bx = pos_bx + size_bx/2;
//            int o_by = pos_by + size_by/2;
//            //set rotation center
//            painter_Tower->translate(o_bx,o_by);
//            //set theta
//            qDebug("theta when paint: %f---------------------------", bullet->GetTheta());
//            painter_Tower->rotate(bullet->GetTheta());
//            // recovery rotation center
//            painter_Tower->translate(-1*o_bx,-1*o_by);
//            //paint
//            painter_Tower->drawPixmap(pos_bx,pos_by,size_bx,size_by,path_b);
//            painter_Tower->restore();
//        }

}
//qDebug
void MainWindow::draw_Bullet(QPainter* painter_Bullet, Tower* tower)
{
    foreach(Tower* tower, TowerList){
        foreach(Bullet* bullet, tower->BulletList){
//             qDebug("Paint Bullet");
            painter_Bullet->save();
            int o_bx = bullet->GetPosCur().x();
            int o_by = bullet->GetPosCur().y();
            int size_bx = bullet->GetSize_x();
            int size_by = bullet->GetSize_y();
            QString path_b(":/pics/b1-1.PNG");
            int pos_bx = o_bx - size_bx/2;
            int pos_by = o_by - size_by/2;
//            int pos_bx = o_bx - int(size_bx/2*fabs(cos(bullet->GetTheta())));
//            int pos_by = o_by - int(size_by/2*fabs(cos(bullet->GetTheta())));
            //set rotation center
            painter_Bullet->translate(o_bx,o_by);
            //set theta
//            qDebug("theta when paint: %f---------------------------", bullet->GetTheta());
            painter_Bullet->rotate(bullet->GetTheta()/3.1415926*180);
            // recovery rotation center
            painter_Bullet->translate(-1*o_bx,-1*o_by);
            //paint
            painter_Bullet->drawPixmap(pos_bx,pos_by,size_bx,size_by,path_b);
            painter_Bullet->restore();
        }
    }
}
void MainWindow::out(QWidget *parent)
{
    hide();
    StartFrom * startfrom=new StartFrom(parent);
    startfrom->show();
}

