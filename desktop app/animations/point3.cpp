#include "point3.h"

Point3::Point3(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

float Point3::getX() {
    return this->x;
}

float Point3::getY() {
    return this->y;
}

float Point3::getZ() {
    return this->z;
}
