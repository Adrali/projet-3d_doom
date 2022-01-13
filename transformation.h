#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include <QVector3D>
#include <QMatrix4x4>
#include <math.h>


/**
 * @brief Représente une matrice de transformation. On peut lui appliquer diverses transformations supplémentaire et transformer des vecteurs
 * @author Pierre.L
 * @version 0.1
 * @date 20 dec 2021
 *
 * Header de la classe Ennemy. Hérite de Entity
 *
 */
class transformation
{
private:
    QMatrix4x4 transform;
public:
    ////Constructors
    transformation(){transform.setToIdentity();}
    transformation(QMatrix4x4 t) : transform(t){}
    //transformation(float tx,float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);

    ////Methods
    QVector3D applyTransformation(QVector3D);
    QMatrix4x4 getTransformationMatrix(){return transform;}

    //transformation methods
    void addRotationX(float angle){transform.rotate(angle,QVector3D(1,0,0));}
    void addRotationY(float angle){transform.rotate(angle,QVector3D(0,1,0));}
    void addRotationZ(float angle){transform.rotate(angle,QVector3D(0,0,1));}
    void addTranslation(float tx, float ty, float tz){transform.translate(tx,ty,tz);}
    void addScale(float sx, float sy, float sz){transform.scale(sx,sy,sz);}


    float angleBetweenVectors2D(QVector3D v1,QVector3D v2)
    {
        return atan2(v1.x()*v2.y()-v2.x()*v1.y(),v1.x()*v1.y()+v2.x()*v2.y());
    }
};



#endif // TRANSFORMATION_H
