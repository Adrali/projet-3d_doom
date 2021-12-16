#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include <QVector3D>
#include <vector>

/**
 * @brief Représente une bounding box avec un point contenant les coordonées minimales de l'objet et un point représentant les coordonées maximales
 * @author Pierre.L
 * @version 0.1
 * @date 10 dec 2021
 *
 * Header de la classe boundingBox
 *
 */
class boundingBox
{
private :
    ////Variables
    QVector3D minVertex;
    QVector3D maxVertex;

    ////Methods
    /*!
     *  \brief Prédicat qui permet de définir si un segment 1D est partiellement ou totalement superposé à un autre
     *
     *  \param xmin1 : coordonée minimum du segment 1
     *  \param xmax1 : coordonée maximum du segment 1
     *  \param xmin2 : coordonée minimum du segment 2
     *  \param xmax2 : coordonée maximum du segment 2
     *
     *  \return true si un segment est partiellement ou totalement superposé à l'autre, false sinon
     */
    bool isOverlapping1D(float xmin1, float xmax1,float xmin2, float xmax2);
public:
    ////Constructors
    /*!
     *  \brief Constructeur
     *
     *  Constructeur de la classe boundingBox
     *
     */
    boundingBox();
    /*!
     *  \brief Constructeur
     *
     *  \param minVertex_ : vertex de coordonée minimale de la boundingBox
     *  \param maxVertex_ : vertex de coordonée maximale de la boundingBox
     *
     */
    boundingBox(QVector3D minVertex_,QVector3D maxVertex_);
    /*!
     *  \brief Constructeur
     *
     *  \param vertices :liste de vertex contenus dans la boundingBox
     *
     */
    boundingBox(std::vector<QVector3D> vertices);

    ////Methods
    /*!
     *  \brief Prédicat qui permet de définir si une boundingBox est partiellement ou totalement superposé à une autre
     *
     *  \param o : Autre bounding box
     *
     *  \return true si this est partiellement ou totalement superposé à l'autre, false sinon
     */
    bool isOverlapping(boundingBox o);
    /*!
     *  \brief Prédicat qui permet de définir si un vertex est à l'interieur de la bounding Box
     *
     *  \param o : Autre bounding box
     *
     *  \return true si le vertex est présent dans this, false sinon
     */
    bool isInBoundingBox(QVector3D v);
    /*!
     *  \brief Prédicat qui permet de définir si un vertex est à l'interieur de la bounding Box sans prendre en compte la hauteur
     *
     *  \param o : Autre bounding box
     *
     *  \return true si le vertex est présent dans this, au dessus ou au dessous, false sinon
     */
    bool isOverBoundingBox(QVector3D v);
    /*!
     *  \brief Getter minVertex qui retourne le vertex de coordonée minimum de la boundingBox
     *     *
     *  \return vertex de coordonée minimum de la boundingBox
     */
    QVector3D getMinVertex(){return minVertex;}
    /*!
     *  \brief Getter minVertex qui retourne le vertex de coordonée maximum de la boundingBox
     *     *
     *  \return vertex de coordonée maximum de la boundingBox
     */
    QVector3D getMaxVertex(){return maxVertex;}
};

#endif // BOUNDINGBOX_H
