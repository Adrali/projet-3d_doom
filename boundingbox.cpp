#include "boundingbox.h"

boundingBox::boundingBox()
{

}

boundingBox::boundingBox(QVector3D minVertex_,QVector3D maxVertex_): minVertex(minVertex_),maxVertex(maxVertex_)
{

}
boundingBox::boundingBox(std::vector<QVector3D> vertices)
{
    minVertex = QVector3D(std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity());
    maxVertex = QVector3D(-1 * std::numeric_limits<float>::infinity(),-1 * std::numeric_limits<float>::infinity(),-1 * std::numeric_limits<float>::infinity());
    for(QVector3D v : vertices){
        for(int i=0;i<3;i++){
            if(v[i] < minVertex[i])
                minVertex[i] = v[i];
            else if(v[i] > maxVertex[i])
                maxVertex[i] = v[i];
        }
    }
}


boundingBox::boundingBox(triangle _triangle){
    QVector3D lVertices[3] = {_triangle.getT1(),_triangle.getT2(),_triangle.getT3()};

    minVertex = QVector3D(std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity(),std::numeric_limits<double>::infinity());
    maxVertex = QVector3D(-1 * std::numeric_limits<float>::infinity(),-1 * std::numeric_limits<float>::infinity(),-1 * std::numeric_limits<float>::infinity());
    for(QVector3D v : lVertices){
        for(int i=0;i<3;i++){
            if(v[i] < minVertex[i])
                minVertex[i] = v[i];
            else if(v[i] > maxVertex[i])
                maxVertex[i] = v[i];
        }
    }
}
bool boundingBox::isOverlapping1D(float vmin1, float vmax1,float vmin2, float vmax2){
    return !(vmax1<vmin2 || vmax2 < vmin1);
}

bool boundingBox::isOverlapping(boundingBox o){
    bool overlapping = true;
    QVector3D minO = o.getMinVertex();
    QVector3D maxO = o.getMaxVertex();
    for(int i=0;i<3;i++){
        overlapping = overlapping && isOverlapping1D(minVertex[i],maxVertex[i],minO[i],maxO[i]);
    }
    return overlapping;
}

bool boundingBox::isInBoundingBox(QVector3D v){
    bool overlapping = true;
    for(int i=0;i<3;i++){
        overlapping = overlapping and isOverlapping1D(minVertex[i],maxVertex[i],v[i],v[i]);
    }
    return overlapping;
}

bool boundingBox::isOverBoundingBox(QVector3D v){
    return isOverlapping1D(minVertex.x(),maxVertex.x(),v.x(),v.x()) and isOverlapping1D(minVertex.z(),maxVertex.z(),v.z(),v.z());
}
