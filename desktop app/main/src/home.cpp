#include "main/include/home.h"
#include "main/include/mainwindow.h"

extern MainWindow *w;

Home::Home(QWidget *parent): QMainWindow(parent), ui(new Ui::Home) {
    ui->setupUi(this);
    this->setWindowTitle("Home");

    this->dtvRect.setRect(rand.global()->bounded(250, 750), rand.global()->bounded(200, 700), 120, 90);
    genColor();

    connect(ui->a_cube, &QPushButton::clicked, this, &Home::cubeAnimation);

    connect(ui->a_waterripple, &QPushButton::clicked, this, &Home::waterRippleAnimation);
    for (int i=0; i<5; i++) {
        connect(watertime, &QTimer::timeout, this, &Home::calcPixels);
    }

    connect(ui->a_kinematics, &QPushButton::clicked, this, &Home::inverseKinematicsAnimation);

    connect(ui->a_fireworks, &QPushButton::clicked, this, &Home::fireworksAnimation);

    QTimer *time = new QTimer(this);
    connect(time, &QTimer::timeout, this, &Home::updateSlot);
    time->start(17);
}

Home::~Home() {
    delete ui;
}

void Home::cubeAnimation() {
    points[0] = new Point3(-0.5, -0.5, -0.5);
    points[1] = new Point3(0.5, -0.5, -0.5);
    points[2] = new Point3(0.5, 0.5, -0.5);
    points[3] = new Point3(-0.5, 0.5, -0.5);
    points[4] = new Point3(-0.5, -0.5, 0.5);
    points[5] = new Point3(0.5, -0.5, 0.5);
    points[6] = new Point3(0.5, 0.5, 0.5);
    points[7] = new Point3(-0.5, 0.5, 0.5);
    this->ani = Cube;
}

void Home::waterRippleAnimation() {
    for (int i=0; i<500; i++) {
        for (int j=0; j<500; j++) {
            current[i][j] = 0;
            previous[i][j] = 0;
        }
    }

    watertime->start(17);

    this->ani = WaterRipple;
}

void Home::inverseKinematicsAnimation() {
    Part *curr = new Part(300, 200, rand.global()->bounded(9, 34), 0);;
    for (int i=0; i<30; i++) {
        Part *next = new Part(curr, rand.global()->bounded(9, 34), 0);
        curr->setChild(next);
        curr = next;
    }
    this->last = curr;

    this->ani = InverseKinematics;
}

void Home::fireworksAnimation() {
    this->ani = Fireworks;
}

void Home::updateSlot() {
    update();
}

void Home::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter *paint = new QPainter(this);
    QPen pen(Qt::white);

    switch (this->ani) {
        case Default: // disc tv bounce
            drawDefaultBounce(paint, pen);
            break;
        case Cube:
            drawCube(paint, pen);
            break;
        case WaterRipple:
            drawWaterRipple(paint);
            break;
        case InverseKinematics:
            drawInverseKinematics(paint, pen);
            break;
        case Fireworks:
            drawFireworks(paint, pen);
            break;
    }

    delete paint;
}

void Home::drawDefaultBounce(QPainter *paint, QPen pen) {
    pen.setWidth(1);
    pen.setColor(this->color);
    paint->setPen(pen);

    moveRectangle();

    paint->drawRect(this->dtvRect);
    paint->setFont(QFont("Times New Roman", 50));
    paint->drawText(
       this->dtvRect.x(), this->dtvRect.y(),
       this->dtvRect.width(), this->dtvRect.height(),
       Qt::AlignmentFlag::AlignCenter, "JP" // change to text of 1st last
    );
}

void Home::moveRectangle() {
    this->dtvRect.moveTo(this->dtvRect.x() + this->xspeed, this->dtvRect.y() + this->yspeed);

    if (this->dtvRect.x() <= 250) {
        this->xspeed = -this->xspeed;
        this->dtvRect.moveTo(250, this->dtvRect.y());
        genColor();
    }
    else if (this->dtvRect.x() >= 630) { // dont calc
        this->xspeed = -this->xspeed;
        this->dtvRect.moveTo(630, this->dtvRect.y());
        genColor();
    }

    if (this->dtvRect.y() <= 200) {
        this->yspeed = -this->yspeed;
        this->dtvRect.moveTo(this->dtvRect.x(), 200);
        genColor();
    }
    else if (this->dtvRect.y() >= 610) {
        this->yspeed = -this->yspeed;
        this->dtvRect.moveTo(this->dtvRect.x(), 610);
        genColor();
    }
}

void Home::genColor() {
    this->color = QColor(
        rand.global()->bounded(100, 255),
        rand.global()->bounded(100, 255),
        rand.global()->bounded(100, 255)
    );
}

void Home::drawCube(QPainter *paint, QPen pen) {
    QVector<QVector<float>> rotX = {
        { 1, 0, 0 },
        { 0, (float) qCos(fTheta), (float) -qSin(fTheta) },
        { 0, (float) qSin(fTheta), (float) qCos(fTheta) },
    };

    QVector<QVector<float>> rotY = {
        { (float) qCos(fTheta), 0, (float) -qSin(fTheta) },
        { 0, 1, 0 },
        { (float) qSin(fTheta), 0, (float) qCos(fTheta) },
    };

    QVector<QVector<float>> rotZ = {
        { (float) qCos(fTheta), (float) -qSin(fTheta), 0 },
        { (float) qSin(fTheta), (float) qCos(fTheta), 0 },
        { 0, 0, 1 }
    };

    for (int i=0; i<8; i++) {
        QVector<QVector<float>> curr = {
            { this->points[i]->getX() },
            { this->points[i]->getY() },
            { this->points[i]->getZ() }
        };

        QVector<QVector<float>> rotated;
        rotated = matmul(rotX, curr);
        rotated = matmul(rotY, rotated);
        rotated = matmul(rotZ, rotated);

        float depth = 1 / (this->distance - rotated[2][0]);
        QVector<QVector<float>> projection = {
            {depth, 0, 0},
            {0, depth, 0}
        };

        QVector<QVector<float>> projected2d = matmul(projection, rotated);

        float x = (projected2d[0][0] * this->scale) + xoff;
        float y = (projected2d[1][0] * this->scale) + yoff;
        float z = projected2d[2][0] * this->scale;
        // paint->drawPoint(x, y);
        projected[i] = new Point3(x, y, z);
    }

    pen.setColor(QColor(0, 0, 34));
    pen.setWidth(4);
    paint->setPen(pen);

    for (int i=0; i<4; i++) {
        paint->drawLine(connectEdge(i, ((i + 1)  % 4)));
        paint->drawLine(connectEdge(i + 4, ((i + 1)  % 4) + 4));
        paint->drawLine(connectEdge(i, i + 4));
    }

    this->fTheta += 0.03;
}

QLineF Home::connectEdge(int i, int j) {
    Point3 *a = this->projected[i];
    Point3 *b = this->projected[j];
    return QLineF(a->getX(), a->getY(), b->getX(), b->getY());
}

QVector<QVector<float>> Home::matmul(QVector<QVector<float>> a, QVector<QVector<float>> b) {
    int colsA = a[0].size();
    int rowsA = a.size();
    int colsB = b[0].size();
    int rowsB = b.size();

    if (colsA != rowsB) {
      QMessageBox al;
      al.setText(QString::number(colsA) + ", " + QString::number(rowsB));
      al.exec();
      exit(69); // quit program (Should never happen)
    }

    QVector<QVector<float>> result = {
      {0},
      {0},
      {0}
    };

    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            float sum = 0;
            for (int k = 0; k < colsA; k++) {
                sum += a[i][k] * b[k][j];
            }
            result[i][j] = sum;
        }
    }
    return result;
}

void Home::drawWaterRipple(QPainter *paint) {
    for (int i=0; i<500; i++) {
        for (int j=0; j<500; j++) {
            float rgb = this->current[i][j];
            QColor color(rgb, rgb, rgb);
            paint->setPen(QPen(color));
            paint->drawPoint(i + 250, j + 200);
        }
    }
}

void Home::mousePressEvent(QMouseEvent *event) {
    if (WaterRipple != this->ani)
        return;

    int x = event->pos().x();
    int y = event->pos().y();
    if (x <= 250 || x >= 750 || y <= 200 || y >= 700) // clicking out of frame
        return;

    this->current[x - 250][y - 200] = 255;
}

void Home::calcPixels() {
    for (int x=1; x<499; x++) {
        for (int y=1; y<499; y++) {
            float currPixel = this->previous[x-1][y] + this->previous[x+1][y];
            currPixel += this->previous[x][y+1] + this->previous[x][y-1];
            currPixel /= 2;
            currPixel -= this->current[x][y];
            this->current[x][y] = currPixel * this->damp;
        }
    }

    for (int x=0; x<500; x++) {
        for (int y=0; y<500; y++) {
            float temp = this->previous[x][y];
            this->previous[x][y] = this->current[x][y];
            this->current[x][y] = temp;
        }
    }
}

void Home::drawInverseKinematics(QPainter *paint, QPen pen) {
    pen.setColor(QColor(0, 0, 34));
    pen.setWidth(4);
    paint->setPen(pen);

    last->follow(QWidget::mapFromGlobal(QCursor::pos()));
    last->calcB();
    paint->drawLine(last->getLineCoords());

    Part *next = last->getParent();
    while (nullptr != next) {
        next->follow();
        next->calcB();
        QLineF seg = next->getLineCoords();
        paint->drawLine(seg);
        next = next->getParent();
    }
}

float Home::map(float num, float min1, float max1, float min2, float max2) {
    return min2 + (max2 - min2) * ((num - min1) / (max1 - min1));
}

void Home::drawFireworks(QPainter *paint, QPen pen) {
    if (3 >= rand.global()->bounded(0, 125))
            fireworks.push_back(new Firework(this->typeCounter++ % 8));

    for (int i=0; i<fireworks.length(); i++) {
        if (!fireworks[i]->update()) {
            pen.setColor(Qt::white);
            pen.setWidth(6);
            paint->setPen(pen);
            paint->drawPoint(fireworks[i]->show(-1));
        }
        else {
            QVector<Particle*> vParticles = fireworks[i]->getParticleArray();
            pen.setColor(fireworks[i]->getColor());
            pen.setWidth(fireworks[i]->getStroke());
            paint->setPen(pen);
            for (int j=vParticles.length()-1; j>=0; j--) {
                paint->drawPoint(fireworks[i]->show(j));
            }
        }
    }
}
