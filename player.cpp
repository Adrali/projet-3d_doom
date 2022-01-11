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
            y = y - delta ;
        }

        //Actualise la pos du joueur
        t.addTranslation(x,y,z);
        t.addRotationY(angleEntity);
        t.addScale(1,1,1);
        //qInfo() << x << " " << y << " " << z << endl;
        this->setTransform(t);
}

void Player::shoot(std::vector<Ennemy * > _lEnnemy){
    if(ammo[weapon] > 0){
        double minDist = std::numeric_limits<double>::infinity();
        Ennemy * closestEnnemy = nullptr;
        if(_lEnnemy.size() > 0){
            for(Ennemy * ennemy : _lEnnemy){
                QVector2D forwardDir(sin(M_PI * angleEntity / 180.0),cos(M_PI * angleEntity / 180.0));
                QVector2D ennemyDir(x-ennemy->getBarycentre().x(),z-ennemy->getBarycentre().z());
                if( 360 * acos((forwardDir.x()*ennemyDir.x()+forwardDir.y()*ennemyDir.y())/(forwardDir.length()*ennemyDir.length()))/(2*M_PI) < ANGLE_OUVERTURE_TIR){
                    double dist = getBarycentre().distanceToPoint(ennemy->getBarycentre());
                    if( dist < minDist){
                        minDist = dist;
                        closestEnnemy = ennemy;
                    }
                }

            }
            if (closestEnnemy)
                closestEnnemy->takeDamages(100);
        }
        shootSound->play();
        ammo[weapon]--;
    }
}


