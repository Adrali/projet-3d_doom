#ifndef ENNEMY_H
#define ENNEMY_H
#include "entity.h"
#include "triangle.h"
#include "const_entity.h"
#include "entity.h"
#include <algorithm>
#include <cmath>


/**
 * @brief Représente un ennemi immobile qui frappe au corps a corps
 * @author Pierre.L
 * @version 0.1
 * @date 20 dec 2021
 *
 * Header de la classe Ennemy. Hérite de Entity
 *
 */
class Ennemy : public Entity
{


public:

    ////Constructors
    /*!
     *  \brief Constructeur
     *
     *  \param _mesh : représente le mesh du gameobject
     *  \param _transfo : représenta la transformation du gameobject
     *  \param _texture : représenta la texture du gameobject
     *  \param _map : pointeur sur le gameobject de la carte
     *  \param _p : pointeur sur le joueur
     *  \param _x : coordonnée x d'apparition
     *  \param _y : coordonnée y d'apparition
     *  \param _z : coordonnée z d'apparition
     *  Constructeur de la classe Ennemy
     *
     */
    Ennemy(GeometryEngine * _mesh,transformation _transfo, QOpenGLTexture *  _texture, gameobject * _map, Entity * _p,float _x, float _y, float _z, int _hp=10) : Entity(_mesh,_transfo,_texture,_map,x,y,z),player(_p){
        isDisplaying = true;
        QVector3D barycentre = getBarycentre();
        /*nx = x = barycentre.x();
        ny = y = barycentre.y();
        nz = z = barycentre.z();*/
        nx = x = _x;
        ny = y = _y;
        nz = z = _z;
        damageSound = new QSound(QString::fromStdString(":/sounds/hit.wav"));
        hp = _hp;
    };


    /*!
     *  @brief Update la position de l'ennemi
     *
     */
    void updatePosition();

    /*!
     *  @brief Update l'ennemi
     *
     */
    void update();
    //Gameplay


private:
    Entity * player; //Un pointeur vers le joueur
    double attackCooldown = COOLDOWN_MAX_ATTAQUE_ENNEMI; //Temps d'attente avant la prochaine attaque
    QSound * damageSound; //Pointeur vers le player du son de dégat au joueur

    Ennemy() : Entity(){};

};

#endif // ENNEMY_H
