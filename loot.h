#ifndef LOOT_H
#define LOOT_H
#include "entity.h"
#include "player.h"

class Loot : public Entity
{
public:
    Loot();
    Loot(GeometryEngine * m,transformation t, QOpenGLTexture *  texture_, gameobject * map,Player * _player,int _hp, int _armor, bool _keys[3], int _ammo[6],float _x, float _y, float _z);
    ~Loot();
    void update();
    bool isLootUsed();

private :
    Player * player;
    int hp;
    int armor;
    bool keys[3];
    int ammo[6];
    bool isUsed = false;
    QSound * pickupSound;
};

#endif // LOOT_H
