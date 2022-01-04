#include "animations/part.h"

Part::Part(float fx, float fy, float fLen, float fAngle) {
    this->a.setX(fx);
    this->a.setY(fy);
    this->len = fLen;
    this->angle = fAngle;
    calcB();
}

Part::Part(Part *parent, float fLen, float fAngle) {
    this->parent = parent;
    this->a = QPointF(parent->b.x(), parent->b.y());
    this->len = fLen;
    this->angle = fAngle;
    calcB();
}

void Part::follow(QPointF tFollow) {
    QPointF dir (tFollow.x() - this->a.x(), tFollow.y() - this->a.y());
    this->angle = (float) qAtan2(dir.y(), dir.x());

    dir = normalize(dir);
    dir.setX(dir.x() * this->len * -1);
    dir.setY(dir.y() * this->len * -1);
    this->a.setX(tFollow.x() + dir.x());
    this->a.setY(tFollow.y() + dir.y());
}

void Part::follow() {
    float tx = this->child->a.x();
    float ty = this->child->a.y();
    follow(QPointF(tx, ty));
}

void Part::calcB() {
    float dx = this->len * qCos(this->angle);
    float dy = this->len * qSin(this->angle);
    this->b.setX(this->a.x() + dx);
    this->b.setY(this->a.y() + dy);
}

QLineF Part::getLineCoords() {
    return QLineF(this->a.x(), this->a.y(), this->b.x(), this->b.y());
}

QPointF Part::normalize(QPointF point) {
    float mag = (float) qSqrt(qPow(point.x(), 2) + qPow(point.y(), 2));
    if (0 != mag && 1 != mag) {
        point.setX(point.x() / mag);
        point.setY(point.y() / mag);
    }
    return point;
}

Part *Part::getParent() {
    return this->parent;
}

void Part::setChild(Part *child) {
    this->child = child;
}
