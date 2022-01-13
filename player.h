#ifndef PLAYER_H
#define PLAYER_H
#include "entity.h"
#include "triangle.h"
#include "const_entity.h"
#include "ennemy.h"
#include <algorithm>
#include <cmath>
#include <QString>

/**
 * @brief Représente le joueur
 * @author Pierre.L
 * @version 0.1
 * @date 20 dec 2021
 *
 * Header de la classe Player. Hérite de Entity
 *
 */
class Player : public Entity
{
private :
    bool keys[3] = {false,false,false}; //Clé que le joueur possèdee
    int ammo[6] = {100,100,100,100,100,100}; //Munitions qu'à le joueur

    int armor = 100; //Armure possédé par le joueur
    int weapon = 1; //index de l'arme actuelle
    GeometryEngine * UI; //Pointeur vers l'UI
    QSound * shootSound; //Pointeur sur le player du son de tir

    //Animation
    int stadeAnimTir = 0; //index du sprite de l'animation de tir
    double animTirTimeReamening = 0; //Temps restant avant le changement de sprite


    /*!
     *  \brief Constructeur privé
     *
     */
    Player() : Entity(){};
public:




    /*!
     *  \brief Constructeur
     *
     *  \param _mesh : représente le mesh du gameobject
     *  \param _transfo : représenta la transformation du gameobject
     *  \param _texture : représenta la texture du gameobject
     *  \param _map : pointeur sur le gameobject de la carte
     *  \param _UI : pointeur sur l'e joueur l'UI
     *  \param _x : coordonnée x d'apparition
     *  \param _y : coordonnée y d'apparition
     *  \param _z : coordonnée z d'apparition
     *  Constructeur de la classe Ennemy
     *
     */
    Player(GeometryEngine * m,transformation t, QOpenGLTexture *  texture_, gameobject * _map,GeometryEngine * _UI,float _x, float _y, float _z) :
        Entity(m,t,texture_,_map,_x,_y,_z),UI(_UI){
        speed = 100.0f;
        backwardSpeed = 80.0f;
        angularSpeed = 5.0f;
        hauteurSol = HAUTEUR_SOL_PLAYER;
        isDisplaying = false;
        hp = 80;
        shootSound = new QSound(QString::fromStdString(":/sounds/shoot.wav"));

    };


    /*!
     *  \brief Destructeur
     *
     */
    ~Player(){
        delete shootSound;
    }
    //Movement methods





    //Predicates

    /*!
     *  \brief Prédicat qui retourne vrai si une position est valide
     *
     *  \param newPos : un point dans l'espace
     *
     *  \return true si la position est valide
     */
    bool isPositionLegit(QVector3D newPos);

    //Getters

    /*!
     *  \brief Retourne la position du joueur
     *
     *  \return Vecteur3D avec la position du joueur
     */
    QVector3D getPlayerPosition(){return QVector3D(x,y,z);}
    /*!
     *  \brief Retourne l'angle du joueur
     *
     *  \return angle du joueur
     */
    float getPlayerAngle(){return angleEntity;}

    //DisplayMethods

    //Main methods

    /*!
     *  \brief Actualise la position du joueur
     */
    void actualisePosition();

    /*!
     *  \brief Actualise le joueur
     */
    void update();

    /*!
     *  \brief Tire sur l'ennemie le plus proche devant le joueur
     *
     *  \param _lEnnemy : Liste des ennemis
     */
    void shoot(std::vector<Ennemy * > _lEnnemy);

    /*!
     *  \brief Ajoute des hp au joueur
     *
     *  \param _hpValue : nombre de point de vie à ajouter
     */
    void addHp(int _hpValue){
        hp + = _hpValue;
        hp = std::min(hp, HP_MAX_JOUEUR);
    }

    /*!
     *  \brief Ajoute des points d'armure au joueur
     *
     *  \param _armorValue : nombre de point d'e vie'armure à ajouter
     */
    void addArmor(int _armorValue){
        armor+=_armorValue;
        armor = std::min(armor,ARMOR_MAX_JOUEUR);
    }

    /*!
     *  \brief Ajoute des munitions au joueur
     *
     *  \param _ammoValue : le tableau des munition à ajouter
     */
    void addAmmo(int _ammoValue[6]){
        for (int i=0;i<6;i++){
            ammo[i]+=_ammoValue[i];
            ammo[i] = std::min(ammo[i],AMMO_MAX_JOUEUR);
        }
    }

    /*!
     *  \brief Ajoute des clés au joueur
     *
     *  \param _keys : les clés à ajouter
     */
    void addKeys(bool _keys[3]){
        for(int i=0;i<3;i++){
            keys[i] = keys[i] || _keys[i];
        }
    }

};
#endif // PLAYER_H
