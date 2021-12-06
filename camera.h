#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <player.h>

class Camera
{
private :

   QMatrix4x4 projection;
   Player * p;
   const qreal zNear = 2.0, zFar = 600.0, fov = 45.0;
   qreal aspect;

public :
   Camera(qreal aspect_) : aspect(aspect_){
       projection.setToIdentity();
   }
   void actualiseMatrix(){
       projection.setToIdentity();
       projection.perspective(fov, aspect, zNear, zFar);
       projection*=p->getTransform().getTransformationMatrix();
   }
   Camera();
   void associatePlayer(Player * p_){
       p = p_;
   }
   QMatrix4x4 getProjectionMatrix(){
       return QMatrix4x4(projection);
   }

};

#endif // CAMERA_H
