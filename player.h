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
    float speed = 0.5f;
    float backwardSpeed = 0.7f;
    float angularSpeed = 1.0f;
    float hauteurSol = 10.0f;
    gameobject * map;
public:
    Player() : gameobject(){};
    Player(GeometryEngine * m,transformation t, int id_texture, gameobject * _map) : gameobject(m,t,id_texture),map(_map){
        QVector3D barycentre = getBarycentre();
        nx = x = barycentre.x();
        ny = y = barycentre.y();
        nz = z = barycentre.z();

    };

    void displayObject(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection){

    }
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

    //Main methods
    void actualisePosition(){
        transformation t;
        x = nx;
        z = nz;
        QVector3D newPoint(x,y,z);
        double minDistance = std::numeric_limits<double>::infinity();
        for(gameobject * go : map->getChilds()){
            if(go->getBBox().isOverBoundingBox(newPoint)){
                double actDistance;
                triangle actTriangle = go->getClosestTriangleDown(newPoint);
                actDistance = actTriangle.hauteurPoint(newPoint);
                qInfo() << actDistance << endl;

                if(actDistance < minDistance){
                    minDistance = actDistance;
                }
            }

        }
        if(y < std::numeric_limits<double>::infinity())
            y = y - minDistance + hauteurSol;

        t.addTranslation(x,y,z);
        t.addRotationY(anglePlayer);
        qInfo() << x << " " << y << " " << z << endl;
        this->setTransform(t);
    }

};

#endif // PLAYER_H
