#ifndef ENTITY_H
#define ENTITY_H
#include "gameobject.h"
#include "triangle.h"
#include "const_entity.h"
#include <algorithm>
#include <cmath>
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
        nz-=cos(M_PI * angleEntity / 180.0)*speed;
        nx-=sin(M_PI * angleEntity / 180.0)*speed;
    }
    void goBackward(){
        nz+=cos(M_PI * angleEntity / 180.0)*backwardSpeed;
        nx+=sin(M_PI * angleEntity / 180.0)*backwardSpeed;
    }
    void goLeft(){
        nz-=cos(M_PI/2 + M_PI * angleEntity / 180.0)*speed;
        nx-=sin(M_PI/2 + M_PI * angleEntity / 180.0)*speed;
    }
    void goRight(){
        nz+=cos(M_PI/2 + M_PI * angleEntity / 180.0)*speed;
        nx+=sin(M_PI/2 + M_PI * angleEntity / 180.0)*speed;
    }
    void turnLeft(){angleEntity+=angularSpeed;}
    void turnRight(){angleEntity-=angularSpeed;}

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

    void angleSpriteFaceEntity(Entity * entity){
        angleSprite = 360 * acos((x-entity->getBarycentre().x())/QVector2D(x-entity->getBarycentre().x(),z-entity->getBarycentre().z()).length())/(2*M_PI);
        angleSprite = ((z-entity->getBarycentre().z()) > 0) ? angleSprite : (360 - angleSprite);
    }


    bool isDead(){
        return hp<=0;
    }

    void takeDamages(int damages){
        qInfo()<<"Touché";
        hp -=damages;
        hp = std::max(hp,0);
        qInfo()<<hp;
    }

protected:
    //Geometry
    float x,y,z;
    float nx,ny,nz;
    float angleEntity = 0;
    float speed = 1.5f;
    float backwardSpeed = 1.2f;
    float angularSpeed = 5.0f;
    float hauteurSol = HAUTEUR_SOL_PLAYER;
    float angleSprite = 0;
    gameobject * map;
    const float vitesseChuteMax = 1.0f;

    //Gameplay
    int hp=10;

};

#endif // ENTITY_H
