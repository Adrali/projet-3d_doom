#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <geometryengine.h>
#include <transformation.h>
#include <QOpenGLTexture>
#include <vector>
#include "boundingbox.h"

/*!
 * \file gameobject.h
 * \brief Représente un gameobject, celui ci est composé d'un mesh, d'une transformation et d'une texture
 * \author Pierre.L
 * \version 0.1
 * \date 10 dec 2021
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
     *  \param transform_ : pointeur sur la texure à afficher
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
     *  \param parentTransform : la transformation qui sert à déplacer l'origine de la transformation de this
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
     *  \param parentTransform : la transformation qui sert à déplacer l'origine de la transformation de this
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
     *  \brief Ajoute un enfant à this dans le graphe de scène
     *  \param go_ : enfant à ajouter
     */
    void addChild(gameobject * go_){childs.push_back(go_);}




    //Getters

    /*!
     * \brief Retourne la liste des enfants de this dans le graphe de scène
     * \return std::vector de pointeur sur les gameobject enfants
     */
    std::vector<gameobject *> getChilds(){return childs;}

    /*!
     * \brief Retourne la liste des vertex du gameobject à leurs positions transformées
     * \return std::vector de QVector3D représentant les vertexs
     */
    std::vector<QVector3D> getActualVertices();
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
     * \param distance : référence qui sert à affecter la distance du point vers le triangle
     *
     * \return Triangle le plus proche. Si il n'y a pas de triangle, alors renvoie un triangle avec pour sommet (0,0,0)
     */
    triangle getClosestTriangleDown(QVector3D p,double & distance);

    //Debug methods
    /*!
     * \brief Fonction de débug qui affiche la liste des vertices du mesh de base
     */
    void displayBaseValue(){
        qInfo() << "Creation"<<endl;
        std::vector<QVector3D> v = mesh->getBaseVertices();
        for(QVector3D ver : v){
            qInfo()<<ver<<endl;
        }
    }




protected:
    ////Variables
    ///
    QOpenGLTexture * texture;
    GeometryEngine * mesh;
    bool isDisplaying = true;
    transformation transform;
    std::vector<gameobject *> childs;
    gameobject();

};
#endif

