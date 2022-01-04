#ifndef PARTICLE_H
#define PARTICLE_H

#include <QPointF>
#include <QRandomGenerator>
#include <QtMath>

class Particle {
public:
    Particle(float x, float y);
    Particle(float x, float y, int type);
    void updatePosition();
    void applyForce(QPointF force);
    QPointF getPosition();
    float getVelo();
    float getLifespan();
private:
    QPointF pos;
    QPointF vel;
    QPointF acc;
    bool firework = false;
    float lifespan;
    QPointF mult;
    float lifespanDeclineMultiple;

    QRandomGenerator *rand = new QRandomGenerator;
};

#endif // PARTICLE_H
