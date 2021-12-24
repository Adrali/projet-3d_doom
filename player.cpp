#include "player.h"

void Player::actualisePosition(){
        transformation t;
        x = nx;
        z = nz;


        QVector3D newPoint(x,y,z);
        //Actualise la hauteur du joueur
        double minDistance = std::numeric_limits<double>::infinity();
        for(gameobject * go : map->getChilds()){
            if(go->getBBox().isOverBoundingBox(newPoint)){
                double actDistance;
                triangle actTriangle = go->getClosestTriangleDown(newPoint);
                actDistance = actTriangle.hauteurPoint(newPoint);
                //qInfo() << actDistance << endl;

                if(actDistance < minDistance){
                    minDistance = actDistance;
                }
            }

        }
        if(y < std::numeric_limits<double>::infinity()){
            float delta = minDistance - hauteurSol;
            if(vitesseChuteMax < (minDistance - hauteurSol))
                delta = vitesseChuteMax;
            y = y - delta;
        }

        //Actualise la pos du joueur
        t.addTranslation(x,y,z);
        t.addRotationY(anglePlayer);
        //qInfo() << x << " " << y << " " << z << endl;
        this->setTransform(t);
}


void Player::turnLeft(float power){
    power = std::min(power,1.0f);
    power = std::max(0.0f,power);
    anglePlayer+=power*angularSpeed;
}
void Player::turnRight(float power){
    power = std::min(power,1.0f);
    power = std::max(0.0f,power);
    anglePlayer-=power*angularSpeed;
}


void Player::goForward(float power){
    power = std::min(power,1.0f);
    power = std::max(0.0f,power);
    nz-=cos(M_PI * anglePlayer / 180.0)*speed;
    nx-=sin(M_PI * anglePlayer / 180.0)*speed;
}
void Player::goBackward(float power){
    power = std::min(power,1.0f);
    power = std::max(0.0f,power);
    nz+=cos(M_PI * anglePlayer / 180.0)*power*backwardSpeed;
    nx+=sin(M_PI * anglePlayer / 180.0)*power*backwardSpeed;
}

void Player::movePlayer(float power){
    if(power<0)
        goBackward(-power);
    else if(power>0)
         goForward(power);
}
void Player::turnPlayer(float power){
    if(power < 0)
        turnRight(-power);
    else if (power > 0)
        turnLeft(power);
}
