#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QMouseEvent>
#include "tower.h"
#include "block.h"
#include "enemy.h"
#include "wave.h"
#include "drawlist.h"
#include "Utility.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class Wave;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    void getCoin(int award);
    void getDamage(int damage);
    void removeEnemy(Enemy *enemy);
    void update_EnemyList();
    void paintNumber(QPainter *Painter,int x,int y,int size_x,int size_y,int num);
    void paintSingleNum(QPainter *Painter,int x,int y,int size_x,int size_y,int num);

    void into_building(int x,int y,Block* b);
    void out_building();
    void into_upgrading(int x,int y,Block* b,int up1,int up2,int down1,int down2);
    void out_upgrading();
    bool canBuyTower1();
    bool canUpgradeTower1();
    void BuyTower1(int px,int py,Block* block);
    void UpgradeTower1();
    void SellTower1();

    void draw_Enemy(QPainter* painter_Enemy,Enemy* enemy)const;
    void draw_Tower(QPainter* painter_Tower,Tower* tower);
    void draw_Bullet(QPainter* painter_Bullet, Tower* tower);
    void out(QWidget *parent = nullptr);

private:
    Ui::MainWindow *ui;
    QList<Tower*> TowerList;
    QList<Block*> BlockList;
    QList<Enemy*> EnemyList;
    QList<Enemy*> tmp_EnemyList;
    QList<DrawList*> Filmlist;

    int Player_Hp = 10;
    int Player_coin = 500;
    int Player_wave = 1;
    Wave* Player_wave_info;
    int input_Clock = 0;

    bool is_building = false;
    bool is_upgrading = false;
    int last_press_x;
    int last_press_y;
    Block* chosen_block;

    bool is_building_filming = false;
    bool is_upgrading_filming = false;
    bool is_lose = false;//to out
    bool is_win = false;// to out
    bool is_stop=false;
    int up_x;
    int up_y;
    int down_x;
    int down_y;
    QTimer* timer;

    //new
    int AttackInterval_count = 0;//计时子弹发射间隔,initialized as 0

protected:
    void paintEvent(QPaintEvent* );
    void mousePressEvent(QMouseEvent *);    
private slots:
    void UpdateEnemy();
    void UpdateTower();
    void inputEnemy();
};
#endif // MAINWINDOW_H
