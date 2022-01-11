#ifndef ENNEMY_H
#define ENNEMY_H
#include "entity.h"
#include "triangle.h"
#include "const_entity.h"
#include "entity.h"
#include <algorithm>
#include <cmath>

class Ennemy : public Entity
{


public:

    Ennemy() : Entity(){};
    Ennemy(GeometryEngine * m,transformation t, QOpenGLTexture *  texture_, gameobject * _map, Entity * _p,float _x, float _y, float _z) : Entity(m,t,texture_,_map,x,y,z),player(_p){
        isDisplaying = true;
        QVector3D barycentre = getBarycentre();
        nx = x = barycentre.x();
        ny = y = barycentre.y();
        nz = z = barycentre.z();

    };


    void updatePosition();

    void update(){
        updatePosition();
    }
    //Gameplay


private:
    int hp = 1;
    Entity * player;
};

#endif // ENNEMY_H
