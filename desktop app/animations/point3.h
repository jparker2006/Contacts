#ifndef POINT3_H
#define POINT3_H


class Point3 {
public:
    Point3(float x, float y, float z);
    float getX();
    float getY();
    float getZ();
private:
    float x, y, z;
};

#endif // POINT3_H
