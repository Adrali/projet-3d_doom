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
   /*!
    *  \brief Constructeur de la classe Camera
    *
    *  Construit une caméra avec une matrice de projection identité
    *
    */
   Camera(){
       projection.setToIdentity();
       vue.setToIdentity();
   };

   /*!
    *  \brief Constructeur de la classe Camera
    *
    *
    */
   Camera(QMatrix4x4 projection_) : projection(projection_){
       vue.setToIdentity();
   }

   /*!
    *  \brief Actualise la matrice de vue en fonction de la position du joueur
    */
   void actualiseVueMatrix();

   /*!
    *  \brief Associe un joueur à suivre la caméra
    *
    *  \param player_ : Pointeur vers le joueur à suivre
    */
   void associatePlayer(Player * player_){
       p = player_;
   }

   /*!
    *  \brief Associe une matrice de projection à la caméra
    *
    *  \param projection_ : Matrice de projection de la scène
    */
   void setProjectionMatrix(QMatrix4x4 projection_){
       projection = projection_;
   }

   /*!
    *  \brief Retourne la matrice de vue actuelle de la caméra
    */
   QMatrix4x4 getVueMatrix(){
       return QMatrix4x4(vue);
   }

   /*!
    *  \brief Retourne la matrice de projection de la caméra
    */
   QMatrix4x4 getProjectionMatrix(){
       return QMatrix4x4(projection);
   }

   /*!
    *  \brief Retourne la matrice MVP de la caméra
    */
   QMatrix4x4 getMVPMatrix(){
       return QMatrix4x4(projection * vue);
   }
};

#endif // CAMERA_H
