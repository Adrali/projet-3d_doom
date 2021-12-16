#ifndef PLAYER_H
#define PLAYER_H
#include "gameobject.h"
#include "triangle.h"

#include <cmath>
class Player : public gameobject
{
private :
    float x,y,z;
    float nx,ny,nz;
    float anglePlayer = 0;
    const float speed = 1.0f;
    const float backwardSpeed = 0.7f;
    const float angularSpeed = 5.0f;
    const float hauteurSol = 10.0f;
    gameobject * map;
    const float vitesseChuteMax = 0.5f;
public:
    Player() : gameobject(){};
    Player(GeometryEngine * m,transformation t, QOpenGLTexture *  texture_, gameobject * _map) : gameobject(m,t,texture_),map(_map){
        isDisplaying = true;
        QVector3D barycentre = getBarycentre();
        nx = x = barycentre.x();
        ny = y = barycentre.y();
        nz = z = barycentre.z();

    };

    //Movement methods
    void goForward(){
        nz-=cos(M_PI * anglePlayer / 180.0)*speed;
        nx-=sin(M_PI * anglePlayer / 180.0)*speed;
    }
    void goBackward(){
        nz+=cos(M_PI * anglePlayer / 180.0)*backwardSpeed;
        nx+=sin(M_PI * anglePlayer / 180.0)*backwardSpeed;
    }
    void goLeft(){
        nz-=cos(M_PI/2 + M_PI * anglePlayer / 180.0)*speed;
        nx-=sin(M_PI/2 + M_PI * anglePlayer / 180.0)*speed;
    }
    void goRight(){
        nz+=cos(M_PI/2 + M_PI * anglePlayer / 180.0)*speed;
        nx+=sin(M_PI/2 + M_PI * anglePlayer / 180.0)*speed;
    }
    void turnLeft(){anglePlayer+=angularSpeed;}
    void turnRight(){anglePlayer-=angularSpeed;}

    //Predicates
    bool isPositionLegit(QVector3D newPos);

    //Getters
    QVector3D getPlayerPosition(){return QVector3D(x,y,z);}
    float getPlayerAngle(){return anglePlayer;}

    //DisplayMethods

    //Main methods
    void actualisePosition();



};
#endif // PLAYER_H
