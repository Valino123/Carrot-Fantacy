#ifndef UTILITY_H
#define UTILITY_H
#include <QPoint>
#include <math.h>
inline bool Collision(QPoint p1, int r1, QPoint p2, int r2)
{
    int delta_x = p1.x() - p2.x();
    int delta_y = p1.y() - p2.y();
    int dis = sqrt(delta_x*delta_x+delta_y*delta_y);
    if(dis < r1+r2)
    {
        return true;
    }
    return false;
}
#endif // UTILITY_H
