#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include <QVector3D>
#include <vector>

/**
 * @brief Représente une bounding box avec un point contenant les coordonées minimales de l'objet et un point représentant les coordonées maximales
 */
class boundingBox
{
private :
    ////Variables
    QVector3D minVertex;
    QVector3D maxVertex;

    ////Methods
    bool isOverlapping1D(float xmin1, float xmax1,float xmin2, float xmax2);
public:
    ////Constructors
    boundingBox();
    boundingBox(QVector3D minVertex_,QVector3D maxVertex_);
    boundingBox(std::vector<QVector3D> vertices);

    ////Methods
    bool isOverlapping(boundingBox o);
    bool isInBoundingBox(QVector3D v);
    bool isOverBoundingBox(QVector3D v);
    QVector3D getMinVertex(){return minVertex;}
    QVector3D getMaxVertex(){return maxVertex;}
};

#endif // BOUNDINGBOX_H
