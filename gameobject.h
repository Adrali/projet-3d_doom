#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <geometryengine.h>
#include <transformation.h>
#include <vector>
#include "boundingbox.h"

/**
 * @brief Représente un gameobject, celui ci est composé d'un mesh, d'une transformation et d'une texture
 */
class gameobject
{
public :
    ////Constructors
    gameobject();
    gameobject(GeometryEngine * m,transformation t, int id_texture) : mesh(m), transform(t),idTexture(id_texture){

    }

    ////Methods
    void setTransform(transformation t){transform = t;}

    //Display methods
    void displayObject(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayObject(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayAll(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayAll(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void addChild(gameobject * g){childs.push_back(g);}
    std::vector<gameobject *> getChilds(){return childs;}
      //Getters
    int getIdTexture(){return idTexture;}
    std::vector<QVector3D> getActualVertices();
    boundingBox getBBox();
    QVector3D getBarycentre();






    //Debug methods
    void displayBaseValue(){
        qInfo() << "Creation"<<endl;
        std::vector<QVector3D> v = mesh->getBaseVertices();
        for(QVector3D ver : v){
            qInfo()<<ver<<endl;
        }
    }


private:
    ////Variables
    GeometryEngine * mesh;
    transformation transform;
    std::vector<gameobject *> childs;
    int idTexture;
};
#endif

