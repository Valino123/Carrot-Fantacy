#include "drawlist.h"

DrawInfo::DrawInfo()
{}

DrawInfo::DrawInfo(int x_,int y_,int size_x_,int size_y_,QString path_):
    x(x_),y(y_),size_x(size_x_),size_y(size_y_),path(path_)
{}

DrawList::DrawList()
{

}

void DrawList::GenerateCircleList(int center_x,int center_y,int min_r,int max_r,int show_time,bool isIncrease,QString path)
{
    double tmp_r,div;
    if(isIncrease) {tmp_r = min_r ; div = (max_r-min_r)/show_time; }
    else {tmp_r = max_r ; div = -(max_r-min_r)/show_time; }

    int i;
    for(i=0;i<show_time;i++)
    {
        DrawInfo* info = new DrawInfo(int(center_x-tmp_r),int(center_y-tmp_r),int(2*tmp_r),int(2*tmp_r),path);
        push_back(info);
        tmp_r += div;
    }
}
