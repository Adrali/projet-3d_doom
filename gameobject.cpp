#include "gameobject.h"

gameobject::gameobject()
{

}
void gameobject::displayObject(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection){
    if(mesh){
        program->setUniformValue("mvp_matrix", projection * parentTransform * transform.getTransformationMatrix());
        mesh->drawCubeGeometry(program);
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
