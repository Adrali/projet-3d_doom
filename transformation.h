#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include <QVector3D>
#include <QMatrix4x4>
#include <math.h>


/**
 * @brief Représente une matrice de transformation. On peut lui appliquer diverses transformations supplémentaire et transformer des vecteurs
 * @author Pierre.L
 * @version 0.1
 * @date 20 dec 2021
 *
 * Header de la classe Ennemy. Hérite de Entity
 *
 */
class transformation
{
private:
    QMatrix4x4 transform;
public:
    ////Constructors
    /*!
    *  \brief Constructeur
    *  Construit la transformation à partir d'une matrice unitaire I4
    */
    transformation(){transform.setToIdentity();}
    /*!
     *  \brief Constructeur
     *  Construit la transformation à partir d'une matrice 4x4
     */
    transformation(QMatrix4x4 t) : transform(t){}
    //transformation(float tx,float ty, float tz, float rx, float ry, float rz, float sx, float sy, float sz);

    ////Methods
    /*!
     *  \brief Applique la transformation au vecteur passé en paramêtre
     */
    QVector3D applyTransformation(QVector3D);
    /*!
     *  \brief Retourne la transformation sous forme de matrice 4x4
     *  \return Une matrice 4x4
     */
    QMatrix4x4 getTransformationMatrix(){return transform;}

    //transformation methods
    /*!
     *  \brief Ajoute une rotation autour de l'axe X à la transformation
     */
    void addRotationX(float angle){transform.rotate(angle,QVector3D(1,0,0));}
    /*!
     *  \brief Ajoute une rotation autour de l'axe Y à la transformation
     */
    void addRotationY(float angle){transform.rotate(angle,QVector3D(0,1,0));}
    /*!
     *  \brief Ajoute une rotation autour de l'axe Z à la transformation
     */
    void addRotationZ(float angle){transform.rotate(angle,QVector3D(0,0,1));}
    /*!
     *  \brief Ajoute une translation à la transformation
     */
    void addTranslation(float tx, float ty, float tz){transform.translate(tx,ty,tz);}
    /*!
     *  \brief Ajoute une mise à l'échelle à la transformation
     */
    void addScale(float sx, float sy, float sz){transform.scale(sx,sy,sz);}

};



#endif // TRANSFORMATION_H
