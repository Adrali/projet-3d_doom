#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <QVector3D>
#include <QVector4D>
class triangle
{
private:
    QVector3D t1,t2,t3,normal;
    triangle();
    bool PointInTriangle(QVector3D p);

public :
    triangle(QVector3D t1_,QVector3D t2_,QVector3D t3_);
    double hauteurPoint(QVector3D v);

    QVector3D getT1() const{
        return t1;
    }
    QVector3D getT2() const{
        return t2;
    }
    QVector3D getT3() const{
        return t3;
    }
};

#endif // TRIANGLE_H
