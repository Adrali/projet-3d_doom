#include "transformation.h"
#include <QQuaternion>
QVector3D transformation::applyTransformation(QVector3D v){
    QVector3D vf = QVector3D(0,0,0);
    for(int i=0;i<3;i++){
        for(int j=0;j<4;j++){
            vf[i]+=transform(i,j);
        }
    }
    return vf;
}
/*void transformation::printMatrix(){
    qInfo() << translation * scale * rotationX * rotationY * rotationZ;

}*/
