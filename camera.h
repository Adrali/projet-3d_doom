#ifndef CAMERA_H
#define CAMERA_H

#include <QMatrix4x4>
#include <player.h>

/*!
 * \file camera.h
 * \brief Représente une camera avec ses différentes matrices
 * \author Pierre.L
 * \version 0.1
 * \date 10 dec 2021
 *
 * Header de la classe Camera
 *
 */
class Camera
{
private :
   QMatrix4x4 vue;
   QMatrix4x4 projection;
   Player * p;
   const qreal zNear = 2.0, zFar = 600.0, fov = 45.0;
   qreal aspect;

public :
   Camera();
   Camera(QMatrix4x4 projection_) : projection(projection_){
       vue.setToIdentity();
   }
   void actualiseVueMatrix();
   void associatePlayer(Player * p_){
       p = p_;
   }

   QMatrix4x4 getVueMatrix(){
       return QMatrix4x4(vue);
   }
   QMatrix4x4 getProjectionMatrix(){
       return QMatrix4x4(projection);
   }

};

#endif // CAMERA_H
