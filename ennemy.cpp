#include "ennemy.h"

void Ennemy::updatePosition(){

    transformation t;
    angleSpriteFaceEntity(player);
    //angleEntity += (rand()%200)/10.0-10;
    //moveEntity((rand()%1000)/2000.0+0.5);
    x = nx;
    z = nz;

    QVector3D newPoint(x,y,z);
    //Actualise la hauteur du joueur
    double minDistance = std::numeric_limits<double>::infinity();
    /*for(gameobject * go : map->getChilds()){
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
    }*/

    //Actualise la pos du joueur
    t.addTranslation(x,y,z);
    t.addScale(10,10,10);
    t.addRotationY(-angleSprite+180);
    //qInfo() << x << " " << y << " " << z << endl;
    this->setTransform(t);

}
