#include "loot.h"

Loot::Loot()
{

}

Loot::Loot(GeometryEngine * m,transformation t, QOpenGLTexture *  texture_, gameobject * map,Player * _player,int _hp, int _armor, bool _keys[3], int _ammo[6],float _x, float _y, float _z) :
    Entity(m,t,texture_,map,_x,_y,_z),player(_player),hp(_hp),armor(_armor)
{
    QVector3D pos = transform.applyTransformation(getBarycentre());
    x = _x;
    y = _y;
    z = _z;

    for(int i=0;i<3;i++)
        keys[i]=_keys[i];
    for(int i=0;i<6;i++)
        ammo[i]=_ammo[i];
    pickupSound = new QSound(QString::fromStdString(":/sounds/pickupLoot.wav"));
    qInfo() << x << y << z ;

}
Loot::~Loot(){
    delete pickupSound;
}

bool Loot::isLootUsed(){return isUsed;}

void Loot::update(){
    transformation t;
    t.addTranslation(x,y,z);
    angleSpriteFaceEntity(player);
    //t.addRotationY(-player->getPlayerAngle()+180+90);
    t.addRotationY(-angleSprite);
    /*qInfo()<< x << y << z << angleSprite;
    qInfo()<< " an : " << angleSprite;
    qInfo()<<"ps : " << z-player->getPlayerPosition().z();*/
    t.addScale(5,5,5);
    setTransform(t);
    //if(getBBox().isOverlapping(player->getBBox())){
    if(getBarycentre().distanceToPoint(player->getBarycentre()) < (HAUTEUR_PLAYER*1.5)){
        player->addHp(hp);
        player->addArmor(armor);
        player->addAmmo(ammo);
        player->addKeys(keys);
        pickupSound->play();

        isUsed = true;
    }
}
