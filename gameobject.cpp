#include "gameobject.h"

gameobject::gameobject(){}


void gameobject::displayObject(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection){
    if(mesh && isDisplaying){
        program->setUniformValue("mvp_matrix", projection * parentTransform * transform.getTransformationMatrix());
        mesh->drawGeometry(program);
    }

}
void gameobject::displayObject(QOpenGLShaderProgram *program,QMatrix4x4 projection){
    QMatrix4x4 mi;
    mi.setToIdentity();
    displayObject(mi,program,projection);

}
void gameobject::displayAll(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection){
    displayObject(parentTransform,program,projection);
    for(gameobject * go : childs){
        go->displayAll(parentTransform * transform.getTransformationMatrix(),program, projection);
    }
}
void gameobject::displayAll(QOpenGLShaderProgram *program,QMatrix4x4 projection){
    QMatrix4x4 mi;
    mi.setToIdentity();
    displayAll(mi,program,projection);
}
std::vector<QVector3D> gameobject::getActualVertices(){
    std::vector<QVector3D> vertices = mesh->getBaseVertices();
    for(unsigned int i=0;i<vertices.size();i++){
        vertices[i] = transform.applyTransformation(vertices[i]);
    }
    return vertices;
}

boundingBox gameobject::getBBox(){
    return boundingBox(getActualVertices());
}

QVector3D gameobject::getBarycentre(){
    QVector3D barycentre(0,0,0);
    std::vector<QVector3D> vertices = getActualVertices();
    for(QVector3D v : vertices){
        barycentre+=(1.0/vertices.size())*v;
    }
    return barycentre;
}

triangle gameobject::getClosestTriangleDown(QVector3D p){
    std::vector<int> indexs = getActualIndexs();
    std::vector<QVector3D> vertices = getActualVertices();
    float minDist = std::numeric_limits<float>::infinity();
    triangle minTriangle(QVector3D(0,0,0),QVector3D(0,0,0),QVector3D(0,0,0));

    for(unsigned int i=0;(i+2)<indexs.size();i++){
        if(indexs[i+1]!=indexs[i+2]){
            triangle tmp = triangle(vertices[indexs[i]],vertices[indexs[i+1]],vertices[indexs[i+2]]);
            float hPoint = tmp.hauteurPoint(p);
            if(minDist > hPoint && hPoint >= 0){
                minDist = hPoint;
                minTriangle = tmp;
            }
        }else{//Si on a un double indice, on passe au triangle suivant.
            i+=3;
        }
    }
    qInfo()<< "Infunc"<<minDist<<endl;
    return minTriangle;
}
triangle gameobject::getClosestTriangleDown(QVector3D p,double & distance){
    std::vector<int> indexs = getActualIndexs();
    std::vector<QVector3D> vertices = getActualVertices();
    float minDist = std::numeric_limits<float>::infinity();
    triangle minTriangle(QVector3D(0,0,0),QVector3D(0,0,0),QVector3D(0,0,0));

    for(unsigned int i=0;(i+2)<indexs.size();i++){
        if(indexs[i+1]!=indexs[i+2]){
            triangle tmp = triangle(vertices[indexs[i]],vertices[indexs[i+1]],vertices[indexs[i+2]]);
            float hPoint = tmp.hauteurPoint(p);
            if(minDist > hPoint && hPoint >= 0){
                minDist = hPoint;
                minTriangle = tmp;
            }
        }else{//Si on a un double indice, on passe au triangle suivant.
            i+=3;
        }
    }
    qInfo()<< "Infunc"<<minDist<<endl;
    distance = minDist;
    return minTriangle;
}
