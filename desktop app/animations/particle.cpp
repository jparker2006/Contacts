#include "particle.h"

Particle::Particle(float x, float y) {
    this->pos = QPointF(x, y);
    this->lifespan = 255;
    this->lifespanDeclineMultiple = rand->global()->bounded(2, 5);
    this->vel = QPointF(0, rand->global()->bounded(-13, -9));
    this->acc = QPointF(0, 0);
}

Particle::Particle(float x, float y, int type) {
    this->pos = QPointF(x, y);
    this->lifespan = 255;
    this->lifespanDeclineMultiple = rand->global()->bounded(2, 5);
    float angle = rand->global()->bounded(150.0) * M_PI_2;
    float multiple = rand->global()->bounded(4, 16);
    this->firework = true;
    float multX = rand->global()->bounded(74, 92) / 100.0;
    float multY = rand->global()->bounded(74, 92) / 100.0;
    this->mult = QPointF(multX, multY);
    this->acc = QPointF(0, 0);

    switch(type) {
        case 0:
            this->vel = QPointF(qSin(angle) * multiple, qSin(angle) * multiple);
            break;
        case 1:
            this->vel = QPointF(-qSin(angle) * multiple, qSin(angle) * multiple);
            break;
        case 2:
            this->vel = QPointF(qSin(angle) * multiple, qCos(angle) * multiple);
            break;
        case 3:
            this->vel = QPointF(qTan(angle) * multiple, qTan(angle) * multiple);
            break;
        case 4:
            this->vel = QPointF(qAtan(angle) * multiple, qTan(angle) * multiple);
            break;
        case 5:
            this->vel = QPointF(-qAtan(angle) * multiple, qTan(angle) * multiple);
            break;
        case 6:
            this->vel = QPointF(qCos(angle) * (M_PI * 4), qSin(angle) * (M_PI * 4));
            break;
        default:
            this->vel = QPointF(qCos(angle) * multiple, qSin(angle) * multiple);
            break;
    }
}

void Particle::updatePosition() {
    if (this->firework) {
        this->vel.setX(this->vel.x() * this->mult.x());
        this->vel.setY(this->vel.y() * this->mult.y());
        this->lifespan -= lifespanDeclineMultiple;
    }

    this->pos.setX(this->pos.x() + this->vel.x());
    this->pos.setY(this->pos.y() + this->vel.y());

    this->vel.setX(this->vel.x() + this->acc.x());
    this->vel.setY(this->vel.y() + this->acc.y());

    this->acc.setX(0);
    this->acc.setY(0);
}

void Particle::applyForce(QPointF force) {
    this->acc.setX(this->acc.x() + force.x());
    this->acc.setY(this->acc.y() + force.y());
}

QPointF Particle::getPosition() {
    return this->pos;
}

float Particle::getLifespan() {
    return this->lifespan;
}

float Particle::getVelo() {
    return this->vel.y();
}
