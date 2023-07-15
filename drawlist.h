#ifndef DRAWLIST_H
#define DRAWLIST_H

#include <QString>
#include <QList>

class DrawInfo
{
public:
    DrawInfo();
    DrawInfo(int x_,int y_,int size_x_,int size_y_,QString path_);
    ~DrawInfo() {}

private:
    int x;
    int y;
    int size_x;
    int size_y;
    QString path;

    friend class DrawList;
    friend class MainWindow;
};


class DrawList
{
public:
    DrawList();
    ~DrawList() {}
    void push_back(DrawInfo* info) { m_drawlist.push_back(info); }
    DrawInfo* front() { return m_drawlist.front(); }
    void pop_front() { m_drawlist.pop_front(); }
    bool isEmpty() {return m_drawlist.isEmpty();}
    void GenerateCircleList(int center_x,int center_y,int min_r,int max_r,int show_time,bool isIncrease,QString path);


private:
    QList<DrawInfo*> m_drawlist;

};

#endif // DRAWLIST_H
