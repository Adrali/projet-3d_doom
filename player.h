#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include "triangle.h"
#include "const_entity.h"
#include "ennemy.h"
#include <algorithm>
#include <cmath>
#include <QString>
class Player : public Entity
{
private :
    bool keys[3] = {false,false,false};
    int ammo[6] = {100,100,100,100,100,100};

    int armor = 100;
    int weapon = 1;
    int stadeAnim = 1;
    GeometryEngine * UI;
    QSound * shootSound;
public:
    Player() : Entity(){};
    Player(GeometryEngine * m,transformation t, QOpenGLTexture *  texture_, gameobject * _map,GeometryEngine * _UI,float _x, float _y, float _z) :
        Entity(m,t,texture_,_map,_x,_y,_z),UI(_UI){
        speed = 1.5f;
        backwardSpeed = 1.2f;
        angularSpeed = 5.0f;
        hauteurSol = HAUTEUR_SOL_PLAYER;
        isDisplaying = false;
        hp = 80;
        shootSound = new QSound(QString::fromStdString(":/sounds/shoot.wav"));

    };

    ~Player(){
        delete shootSound;
    }
    //Movement methods





    //Predicates
    bool isPositionLegit(QVector3D newPos);

    //Getters
    QVector3D getPlayerPosition(){return QVector3D(x,y,z);}
    float getPlayerAngle(){return angleEntity;}

    //DisplayMethods

    //Main methods
    void actualisePosition();
    void update(){
        actualisePosition();
        UI->updateUI(hp,ammo,keys,armor,weapon,stadeAnim);
    }
    void shoot(std::vector<Ennemy * > _lEnnemy);

    void addHp(int _hpValue){
        hp+=_hpValue;
    }
    void addArmor(int _armorValue){
        armor+=_armorValue;
    }
    void addAmmo(int _ammoValue[6]){
        for (int i=0;i<6;i++){
            ammo[i]+=_ammoValue[i];
        }
    }
    void addKeys(bool _keys[3]){
        for(int i=0;i<3;i++){
            keys[i] = keys[i] || _keys[i];
        }
    }

};
#endif // PLAYER_H
