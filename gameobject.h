#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <geometryengine.h>
#include <transformation.h>
#include <vector>
class gameobject
{
private:
    GeometryEngine * mesh;
    transformation transform;
    std::vector<gameobject *> childs;

    int idTexture;



public :
    gameobject();
    gameobject(GeometryEngine * m,transformation t, int id_texture) : mesh(m), transform(t),idTexture(id_texture){

    }

    void setTransform(transformation t){transform = t;}
    void displayObject(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayObject(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayAll(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayAll(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void addChild(gameobject * g){childs.push_back(g);}
    int getIdTexture(){return idTexture;}
    std::vector<QVector3D> getActualVertices();
    void displayBaseValue(){
        qInfo() << "Creation"<<Qt::endl;
        std::vector<QVector3D> v = mesh->getBaseVertices();
        for(QVector3D ver : v){
            qInfo()<<ver<<Qt::endl;
        }
    }

};
#endif

