#include "transformation.h"
#include <QQuaternion>
#include <QVector4D>
QVector3D transformation::applyTransformation(QVector3D v){
    QVector4D v_to_4D =  QVector4D(v, 1.0);
    v_to_4D = transform*v_to_4D;
    return v_to_4D.toVector3D();
}
/*void transformation::printMatrix(){
    qInfo() << translation * scale * rotationX * rotationY * rotationZ;

}*/
