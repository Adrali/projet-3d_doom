#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <geometryengine.h>
#include <transformation.h>
#include <QOpenGLTexture>
#include <QSound>
#include <QtMultimedia/QMediaPlayer>
#include <vector>
#include "boundingbox.h"
#include "gameTime.h"






/**
 * @brief Représente un gameobject, celui ci est composé d'un mesh, d'une transformation et d'une texture
 * @author Pierre.L
 * @version 0.1
 * @date 10 dec 2021
 *
 * Header de la classe gameobject
 *
 */
class gameobject
{
public :
    ////Constructors
    ///

    /*!
     *  \brief Constructeur de la classe gameobject
     *
     *  \param mesh_ : représente le mesh du gameobject. Si mesh_ = nullptr, le gameobject ne sera pas affiché
     *  \param transform_ : représente la transformation de la position des vertex du mesh_
     *  \param transform_ : pointeur sur la texure �  afficher
     */
    gameobject(GeometryEngine * mesh_,transformation transform_, QOpenGLTexture * texture_) : mesh(mesh_), transform(transform_),texture(texture_){
    }

    ////Methods
    ///
    /*!
     *  \brief Setter : Remplace la transformation du gameobject par celle donnée en paramêtre
     *  \param transform_ : Nouvelle transformation du gameobject
     */
    void setTransform(transformation transform_){transform = transform_;}

    //Display methods
    /*!
     *  \brief Méthode qui affiche le gameobject avec sa texture associée avec pour origine de transformation la transformation de son parent
     *  \param parentTransform : la transformation qui sert �  déplacer l'origine de la transformation de this
     *  \param program : pointeur vers la fenêtre
     *  \param projection : matrice de projection de la Camera de la scène
     */
    void displayObject(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    /*!
     *  \brief Méthode qui affiche le gameobject avec sa texture associée
     *  \param program : pointeur vers la fenêtre
     *  \param projection : matrice de projection de la Camera de la scène
     */
    void displayObject(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    /*!
     *  \brief Méthode qui affiche le gameobject avec sa texture associée et avec pour origine de transformation la transformation de son parent ainsi que tous ses enfants
     *  \param parentTransform : la transformation qui sert �  déplacer l'origine de la transformation de this
     *  \param program : pointeur vers la fenêtre
     *  \param projection : matrice de projection de la Camera de la scène
     */
    void displayAll(QMatrix4x4 parentTransform, QOpenGLShaderProgram *program,QMatrix4x4 projection);
    /*!
     *  \brief Méthode qui affiche le gameobject avec sa texture associée ainsi que tous ses enfants
     *  \param program : pointeur vers la fenêtre
     *  \param projection : matrice de projection de la Camera de la scène
     */
    void displayAll(QOpenGLShaderProgram *program,QMatrix4x4 projection);
    /*!
     *  \brief Ajoute un enfant �  this dans le graphe de scène
     *  \param go_ : enfant �  ajouter
     */
    void addChild(gameobject * go_){childs.push_back(go_);}




    //Getters

    /*!
     * \brief Retourne la liste des enfants de this dans le graphe de scène
     * \return std::vector de pointeur sur les gameobject enfants
     */
    std::vector<gameobject *> getChilds(){return childs;}

    /*!
     * \brief Retourne la liste des vertex du gameobject �  leurs positions transformées
     * \return std::vector de QVector3D représentant les vertexs
     */
    std::vector<QVector3D> getActualVertices();

    /*!
     * \brief Retourne la liste ordonn�e des indices des vertex du mesh
     * \return std::vector de QVector3D représentant les vertexs
     */
    std::vector<int> getActualIndexs(){return mesh->getIndex();}
    /*!
     * \brief Retourne la boundingBox du gameobject
     * \return La boundingBox du gameobject
     */
    boundingBox getBBox();
    /*!
     * \brief Retourne le barycentre du gameobject
     * \return QVector3D barycentre du gameobject
     */
    QVector3D getBarycentre();
    /*!
     * \brief Retourne le transformation du gameobject
     * \return Transformation du gameobject
     */
    transformation getTransform(){ return transformation(transform);}
    /*!
     * \brief Retourne le triangle du gameobject le plus proche situé sur la droite paramétrique formée par p et le vecteur (0,-1,0) tel que la distance est positive
     *
     * \param p : le point de la droite paramétrique
     *
     * \return Triangle le plus proche. Si il n'y a pas de triangle, alors renvoie un triangle avec pour sommet (0,0,0)
     */
    triangle getClosestTriangleDown(QVector3D p);
    /*!
     * \brief Retourne le triangle du gameobject le plus proche situé sur la droite paramétrique formée par p et le vecteur (0,-1,0) tel que la distance est positive
     *
     * \param p : le point de la droite paramétrique
     * \param distance : référence qui sert �  affecter la distance du point vers le triangle
     *
     * \return Triangle le plus proche. Si il n'y a pas de triangle, alors renvoie un triangle avec pour sommet (0,0,0)
     */
    triangle getClosestTriangleDown(QVector3D p,double & distance);
    /*!
     * \brief Retourne un vector avec la liste des triangles du mesh

     * \return Retourne un vector avec la liste des triangles
     */
    std::vector<triangle> getTriangleList();

    /*!
     * \brief Pr�dicat vrai si la bb donn�e en parametre
     *
     * \param _bb : une boundingbox
     *
     * \return Retourne vrai si _bb intersecte avec l'un des triangles du mesh
     */
    bool isBBoxIntersect(boundingBox _bb);

    //Debug methods
    /*!
     * \brief Fonction de d�bug qui affiche la liste des vertices du mesh de base
     */
    void displayBaseValues(){
        std::vector<QVector3D> v = mesh->getBaseVertices();
        for(QVector3D ver : v){
            qInfo()<<ver;
        }
    }
    /*!
     * \brief Retourne le type de g�om�trie du mesh
     *

     * \return le type de g�om�trie du mesh
     */
    int getGeometryType(){
        return mesh->getType();
    }


protected:
    ////Variables
    ///
    QOpenGLTexture * texture; //Texture du gameobject
    GeometryEngine * mesh; //Mesh du gameobject
    bool isDisplaying = true; //Vrai si l'objet doit d'afficher
    transformation transform; //Transform du gameobject
    std::vector<gameobject *> childs; //Liste des gameobject enfants
    gameobject();

};


#endif

