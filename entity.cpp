#include "entity.h"


void Entity::turnLeft(float power){
    power = std::min(power,1.0f);
    power = std::max(0.0f,power);
    angleEntity+=power*angularSpeed;
}
void Entity::turnRight(float power){
    power = std::min(power,1.0f);
    power = std::max(0.0f,power);
    angleEntity-=power*angularSpeed;
}


void Entity::goForward(float power){
    power = std::min(power,1.0f);
    power = std::max(0.0f,power);
    nz-=GameTime::getDeltaTime()*cos(M_PI * angleEntity / 180.0)*speed;
    nx-=GameTime::getDeltaTime()*sin(M_PI * angleEntity / 180.0)*speed;
}
void Entity::goBackward(float power){
    power = std::min(power,1.0f);
    power = std::max(0.0f,power);
    nz+=GameTime::getDeltaTime()*cos(M_PI * angleEntity / 180.0)*power*backwardSpeed;
    nx+=GameTime::getDeltaTime()*sin(M_PI * angleEntity / 180.0)*power*backwardSpeed;
}

void Entity::moveEntity(float power){
    if(power<0)
        goBackward(-power);
    else if(power>0)
         goForward(power);
}
void Entity::turnEntity(float power){
    if(power < 0)
        turnRight(-power);
    else if (power > 0)
        turnLeft(power);
}
