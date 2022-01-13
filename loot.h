#ifndef LOOT_H
#define LOOT_H
#include "entity.h"
#include "player.h"


/**
 * @brief Représente les loots disponibles ( objets ramassables )
 * @author Pierre.L
 * @version 0.1
 * @date 20 dec 2021
 *
 * Header de la classe Loot. Hérite de Entity
 *
 */
class Loot : public Entity
{
public:
    /*!
     *  \brief Constructeur
     *
     *  \param _mesh : représente le mesh du gameobject
     *  \param _transfo : représenta la transformation du gameobject
     *  \param _texture : représenta la texture du gameobject
     *  \param _map : pointeur sur le gameobject de la carte
     *  \param _player : pointeur sur le joueur
     *  \param _hp : hp rendu par le loot
     *  \param _armor : armor rendu par le loot
     *  \param _keys[3] : clé contenus dans le loot
     *  \param _ammo[6] : munitions données par le loot
     *  \param _x : coordonnée x d'apparition
     *  \param _y : coordonnée y d'apparition
     *  \param _z : coordonnée z d'apparition
     *  Constructeur de la classe Loot
     *
     */
    Loot(GeometryEngine * _mesh,transformation _transfo, QOpenGLTexture *  _texture, gameobject * _map,Player * _player,int _hp, int _armor, bool _keys[3], int _ammo[6],float _x, float _y, float _z);
    ~Loot();
    /*!
     *  \brief update le loot
     *
     */
    void update();
    /*!
     *  \brief predicat qui retourne vrai si le loot à été utilisé
     *  \return retour vrai si le loot a été utilisé
     */
    bool isLootUsed();

private :
    Player * player;
    int hp;
    int armor;
    bool keys[3];
    int ammo[6];
    bool isUsed = false;
    QSound * pickupSound;
    Loot();

};

#endif // LOOT_H
