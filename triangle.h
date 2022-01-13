#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <QVector3D>
#include <QVector4D>

/**
 * @brief Représente un ennemi immobile qui frappe au corps a corps
 * @author Pierre.L
 * @version 0.1
 * @date 20 dec 2021
 *
 * Header de la classe Ennemy. Hérite de Entity
 *
 */
class triangle
{
private:
    QVector3D t1,t2,t3,normal;
    triangle();
    /*!
     *  \brief Prédicat qui indique si un point est dans le triangle
     *  \return vrai si un point est dans le triangle
     */
    bool PointInTriangle(QVector3D p);

public :
    /*!
     *  \brief Constructeurs
     *  \param t1_,t2_,t3_ : Les trois points du triangle
     */
    triangle(QVector3D t1_,QVector3D t2_,QVector3D t3_);
    /*!
     *  \brief Retourne la distance entre un point et sa projection sur le plan formé par le triangle
     *  \return un double représentant la hauteur du point
     */
    double hauteurPoint(QVector3D v);

    QVector3D getT1() const{
        return t1;
    }
    QVector3D getT2() const{
        return t2;
    }
    QVector3D getT3() const{
        return t3;
    }

};

#endif // TRIANGLE_H
