#ifndef PLAYER_H
#define PLAYER_H
#include "gameobject.h"

class Player : public gameobject
{
private :
    float speed = 0.5f;
    float angularSpeed = 1.0f;
public:
    Player() : gameobject(){};
    Player(GeometryEngine * m,transformation t, int id_texture) : gameobject(m,t,id_texture){};
    void goForward();
    void goBackward();
    void goLseft();
    void goRight();

};

#endif // PLAYER_H
