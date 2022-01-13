#ifndef ENTITY_H
#define ENTITY_H
#include "gameobject.h"
#include "triangle.h"
#include "const_entity.h"
#include <algorithm>
#include <cmath>

/**
 * @brief Représente une entité abstraite
 * @author Pierre.L
 * @version 0.1
 * @date 20 dec 2021
 *
 * Header de la classe Entity. Hérite de gameobject
 *
 */
class Entity : public gameobject
{
public:

    Entity(){};

    Entity(GeometryEngine * m,transformation t, QOpenGLTexture *  texture_, gameobject * _map,float _x, float _y, float _z) : gameobject(m,t,texture_),map(_map){
        x=_x;
        y=_y;
        z=_z;
        isDisplaying = true;
        QVector3D barycentre = getBarycentre();
        nx = x = barycentre.x();
        ny = y = barycentre.y();
        nz = z = barycentre.z();
        speed = 0.0f;
        backwardSpeed = 0.0f;
        angularSpeed = 0.0f;
        hauteurSol = HAUTEUR_SOL_PLAYER;

    };


    //Geometry
    void goForward(){
        nz-=GameTime::getDeltaTime()*cos(M_PI * angleEntity / 180.0)*speed;
        nx-=GameTime::getDeltaTime()*sin(M_PI * angleEntity / 180.0)*speed;
    }
    void goBackward(){
        nz+=GameTime::getDeltaTime()*cos(M_PI * angleEntity / 180.0)*backwardSpeed;
        nx+=GameTime::getDeltaTime()*sin(M_PI * angleEntity / 180.0)*backwardSpeed;
    }
    void goLeft(){
        nz-=GameTime::getDeltaTime()*cos(M_PI/2 + M_PI * angleEntity / 180.0)*speed;
        nx-=GameTime::getDeltaTime()*sin(M_PI/2 + M_PI * angleEntity / 180.0)*speed;
    }
    void goRight(){
        nz+=GameTime::getDeltaTime()*cos(M_PI/2 + M_PI * angleEntity / 180.0)*speed;
        nx+=GameTime::getDeltaTime()*sin(M_PI/2 + M_PI * angleEntity / 180.0)*speed;
    }
    void turnLeft(){angleEntity+=GameTime::getDeltaTime()*angularSpeed;}
    void turnRight(){angleEntity-=GameTime::getDeltaTime()*angularSpeed;}

    void turnLeft(float power);
    void turnRight(float power);

    void goForward(float power);
    void goBackward(float power);

    /**
     * @brief turn the player with a certains power (-1<=power<=1)
     * @param power : if power = 0, the player dont turn, if -1<=power<0, the player turn to the left with maxRotationSpeed at -1, if 0<power<=1, the player turn to the right with maxRotationSpeed at 1
     */
    void turnEntity(float power);
    /**
     * @brief move the player with a certains power (-1<=power<=1)
     * @param power : if power = 0, the player dont turn, if -1<=power<0, the player go backward with maxSpeed at -1, if 0<power<=1, the playergo forward with maxSpeed at 1
     */
    void moveEntity(float power);

    /**
     * @brief Met à jour l'angle de vue du mesh pour qu'il soit face à l'entité parametre
     */
    void angleSpriteFaceEntity(Entity * entity){
        angleSprite = 360 * acos((x-entity->getBarycentre().x())/QVector2D(x-entity->getBarycentre().x(),z-entity->getBarycentre().z()).length())/(2*M_PI);
        angleSprite = ((z-entity->getBarycentre().z()) > 0) ? angleSprite : (360 - angleSprite);
    }

    /**
     * @brief Prédicat vrai si l'entité est morte
     *
     * @return vrai si this est mort ( hp <=0 )
     */
    bool isDead(){
        return hp<=0;
    }

    /**
     * @brief Inflige des dégats à this
     *
     */
    void takeDamages(int damages){
        hp -=damages;
        hp = std::max(hp,0);
        qInfo()<<hp;
    }

protected:
    //Geometry
    float x,y,z; //Coordonées de l'entité
    float nx,ny,nz; //Ses possibles futures coordonées
    float angleEntity = 0; //L'angle de l'entité du point de vue gameplay
    float speed = 1.5f; //Vitesse du joueur
    float backwardSpeed = 1.2f; //Vitesse de recul
    float angularSpeed = 5.0f; //Vitesse angulaire
    float hauteurSol = HAUTEUR_SOL_PLAYER; //Hauteur de l'entité par rapport au sol
    float angleSprite = 0; //L'angle de l'entité du point de vue de l'affichage
    gameobject * map; //Pointeur sur la map
    const float vitesseChuteMax = 1.0f; //Vitesse de chute d'une entité

    //Gameplay
    int hp=10;

};

#endif // ENTITY_H
