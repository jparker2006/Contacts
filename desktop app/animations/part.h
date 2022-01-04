#ifndef PART_H
#define PART_H

#include <QPointF>
#include <QLineF>
#include <QtMath>

class Part {
public:
    Part(float fx, float fy, float fLen, float fAngle);
    Part(Part *parent, float fLen, float fAngle);
    void follow(QPointF tFollow);
    void follow();
    void calcB();
    QLineF getLineCoords();
    QPointF normalize(QPointF point);
    Part *getParent();
    void setChild(Part *child);
private:
    QPointF a;
    QPointF b;
    float angle;
    float len;
    Part *parent = nullptr, *child = nullptr;
};

#endif // PART_H
