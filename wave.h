#ifndef WAVE_H
#define WAVE_H
#include <QList>
#include "enemy.h"
class Enemy;
class Wave
{
public:
    Wave();
    Wave(MainWindow* game);
    int getMaxWave();
    void initialize_Wave();
    QList<Enemy*> get_Wave(int wave);

private:
    int max_Wave = 3;
    int max_Enemy_num = 10;
    QList<Enemy*> wave1;
    QList<Enemy*> wave2;
    QList<Enemy*> wave3;

    MainWindow *Game;
};

#endif // WAVE_H
