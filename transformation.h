#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include <QVector3D>
#include <QMatrix4x4>
class transformation
{
private:
    /*float tx,ty,tz,rx,ry,rz,sx,sy,sz;
    QMatrix4x4 rotationX,rotationY,rotationZ,translation,scale;*/
    QMatrix4x4 transform;
public:
    transformation(){transform.setToIdentity();}
    transformation(QMatrix4x4 t) : transform(t){}
    QVector3D applyTransformation(QVector3D);
    QMatrix4x4 getTransformationMatrix(){return transform;}

    void addRotationX(float angle){transform.rotate(angle,QVector3D(1,0,0));}
    void addRotationY(float angle){transform.rotate(angle,QVector3D(0,1,0));}
    void addRotationZ(float angle){transform.rotate(angle,QVector3D(0,0,1));}
    void addTranslation(float tx, float ty, float tz){transform.translate(tx,ty,tz);}
    void addScale(float sx, float sy, float sz){transform.scale(sx,sy,sz);}
};

#endif // TRANSFORMATION_H
