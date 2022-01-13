#include "player.h"

void Player::actualisePosition(){
        transformation t;
        bool isCollision = false;


        //Detection de collision : Buggé actuellement
        /*std::vector<QVector3D> vertices = mesh->getBaseVertices();
        std::vector<QVector3D> lNewVertices;
        t.addTranslation(nx,y,nz);
        t.addRotationY(angleEntity);
        t.addScale(1,1,1);
        for(unsigned int i=0;i<vertices.size();i++){
            lNewVertices.push_back(t.applyTransformation(vertices[i]));
        }
        boundingBox bbNewPos(lNewVertices);
        for(gameobject * go : map->getChilds()){
            if(go->isBBoxIntersect(bbNewPos)){
                isCollision = true;
            }
        }*/

        if(!isCollision){
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
        }else{
            nx = x;
            nz = z;
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
                closestEnnemy->takeDamages(15);
        }
        stadeAnimTir=1;
        animTirTimeReamening = 0.1;
        shootSound->play();
        ammo[weapon]--;
    }
}


void Player::update(){
    actualisePosition();
    if(stadeAnimTir > 0){
        if(animTirTimeReamening>0){
            animTirTimeReamening -= GameTime::getDeltaTime();
        }else{
            stadeAnimTir=(stadeAnimTir+1)%3;
            animTirTimeReamening = 0.1;
        }
    }
    //qInfo()<<stadeAnimTir;
    UI->updateUI(hp,ammo,keys,armor,weapon,stadeAnimTir);
}
