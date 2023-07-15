#include "wave.h"

Wave::Wave(MainWindow* game):Game(game)
{

}

void Wave::initialize_Wave()
{
    //0:no   1:Fast   2:Mid   3:Slow
    const int enemies[3][10] = { {1,1,1,1,1,1,1,3,3,3},
                                 {1,1,1,1,1,1,1,3,3,3},
                                 {3,3,3,0,0,0,0,0,0,0} };
    int i;
    for(i=0;i<10;i++)
    {
        if(enemies[0][i] == 0)
            break;
        Enemy* enemy = new Enemy(Game);
        switch (enemies[0][i]) {
            case 1: enemy->initialize_EnemyFast(); wave1.push_back(enemy); break;
            case 2: enemy->initialize_EnemyMid() ; wave1.push_back(enemy); break;
            case 3: enemy->initialize_EnemySlow(); wave1.push_back(enemy); break;
        }
    }

    for(i=0;i<10;i++)
    {
        if(enemies[1][i] == 0)
            break;
        Enemy* enemy = new Enemy(Game);
        switch (enemies[1][i]) {
            case 1: enemy->initialize_EnemyFast(); wave2.push_back(enemy); break;
            case 2: enemy->initialize_EnemyMid() ; wave2.push_back(enemy); break;
            case 3: enemy->initialize_EnemySlow(); wave2.push_back(enemy); break;
        }
    }

    for(i=0;i<10;i++)
    {
        if(enemies[2][i] == 0)
            break;
        Enemy* enemy = new Enemy(Game);
        switch (enemies[2][i]) {
            case 1: enemy->initialize_EnemyFast(); wave3.push_back(enemy); break;
            case 2: enemy->initialize_EnemyMid() ; wave3.push_back(enemy); break;
            case 3: enemy->initialize_EnemySlow(); wave3.push_back(enemy); break;
        }
    }
}

QList<Enemy*> Wave::get_Wave(int wave)
{
    switch (wave) {
        case 1 : return wave1;
        case 2 : return wave2;
        case 3 : return wave3;
    }
    return wave1;
}

int Wave::getMaxWave()
{
    return max_Wave;
}
