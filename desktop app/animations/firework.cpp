#include "firework.h"

Firework::Firework(int type) {
    this->firework = new Particle(rand.global()->bounded(275, 725), 700);
    this->bExploded = false;
    this->color = QColor(
        rand.global()->bounded(70, 255),
        rand.global()->bounded(70, 255),
        rand.global()->bounded(70, 255)
    );
    this->stroke = rand.global()->bounded(2, 5);
    this->type = type;
}

bool Firework::update() { // return true if its a firework post explode
    if (this->bExploded) {
        for (int i=vParticles.length()-1; i>=0; i--) {
            this->vParticles[i]->applyForce(this->gravity); //
            this->vParticles[i]->updatePosition();
        }
        return true;
    }

    this->firework->applyForce(this->gravity);
    this->firework->updatePosition();

    if (0 <= this->firework->getVelo()) {
        this->bExploded = true;
        explode();
    }

    return false;
}

QPointF Firework::show(int index) {
    if (-1 == index)
        return this->firework->getPosition();

    if (this->bExploded)
        return this->vParticles[index]->getPosition();

    return QPointF(-10, -10); // should never hit
}

void Firework::explode() {
    for (int i=0; i<rand.global()->bounded(75, 350); i++) {
        QPointF apex = this->firework->getPosition();
        this->vParticles.push_back(new Particle(apex.x(), apex.y(), this->type));
    }
}

QVector<Particle*> Firework::getParticleArray() {
    return this->vParticles;
}

QColor Firework::getColor() {
    this->color.setAlpha(vParticles[0]->getLifespan());
    return this->color;
}

int Firework::getStroke() {
    return this->stroke;
}
