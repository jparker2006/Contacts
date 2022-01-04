#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QColor>
#include <QPainter>
#include <QPen>
#include <QTimer>
#include <QRandomGenerator>
#include <QRectF>
#include <QtMath>
#include <QMouseEvent>

#include "ui_home.h"
#include "animations/point3.h"
#include "animations/part.h"
#include "animations/firework.h"
#include "animations/particle.h"

namespace Ui {
    class Home;
}

class Home: public QMainWindow {
    Q_OBJECT
public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();
    void updateSlot();
    virtual void paintEvent(QPaintEvent *event);

    void drawDefaultBounce(QPainter *paint, QPen pen);
    void moveRectangle();
    void genColor();

    void drawCube(QPainter *paint, QPen pen);
    QVector<QVector<float>> matmul(QVector<QVector<float>> a, QVector<QVector<float>> b);
    QLineF connectEdge(int i, int j);

    void drawWaterRipple(QPainter *paint);
    void drawPix(QPointF point, float color);
    void mousePressEvent(QMouseEvent *event);
    void calcPixels();

    void drawInverseKinematics(QPainter *paint, QPen pen);
    float map(float num, float min1, float max1, float min2, float max2);

    void drawFireworks(QPainter *paint, QPen pen);
public slots:
    void cubeAnimation();
    void waterRippleAnimation();
    void inverseKinematicsAnimation();
    void fireworksAnimation();
private:
    Ui::Home *ui;
    QPainter *paint = new QPainter(this);

    // dv bounce
    QRandomGenerator rand;
    QRectF dtvRect;
    float xspeed = 2.7, yspeed = 2.7;
    QColor color;

    // cube
    Point3 *points[8];
    float fTheta = 0.0;
    float xoff = 500; // this.width / 2
    float yoff = 450; // this.height / 2
    float scale = 250;
    float distance = 1.4;
    Point3 *projected[8];

    // water
    QTimer *watertime = new QTimer();
    float current[500][500];
    float previous[500][500]; // cols (width) , rows (height)
    float damp = 0.95;

    // kinematics
    Part *last;

    // fireworks
    QVector<Firework*> fireworks;
    int typeCounter;

    enum e_animation {
        Default,
        Cube,
        WaterRipple,
        InverseKinematics,
        Fireworks,
    };

    e_animation ani = Default;
};

#endif // HOME_H
