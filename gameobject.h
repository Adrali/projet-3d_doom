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
public :
    gameobject();
    gameobject(GeometryEngine * m,transformation t) : mesh(m), transform(t){}

    void setTransform(transformation t){transform = t;}
    void displayObject(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayObject(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayAll(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void displayAll(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    void addChild(gameobject * g){childs.push_back(g);}

};
#endif

