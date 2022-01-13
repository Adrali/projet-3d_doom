/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef GEOMETRYENGINE_H
#define GEOMETRYENGINE_H

#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <vector>
#include "boundingbox.h"
#include "triangle.h"
#include <QOpenGLTexture>
#include <math.h>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

/**
 *
 * Remy BARRIOL
 * Conserve les informations necessaires pour la gestion de l'UI, les textures et les donn�es � afficher
 */
struct UIgo
{
                bool key[3];
                int weapon=1;
                int stadeAnim=0;
                int health=100;
                int ammo[6];
                int armor=100;
                int head=0;

                int ammo1[2];
                int ammo2[2];
                int ammo3[2];
                int health1[2];
                int health2[2];
                int health3[2];
                int armor1[2];
                int armor2[2];
                int armor3[2];
                int head1[2];
                int weapon1[2];
                int redKey[2];
                int blueKey[2];
                int yellowKey[2];

                int weaponStade1[2];
                int weaponStade2[2];
                int weaponStade3[2];

                //std::vector<unsigned int>* linkFileTextureGeo;
                float red=0;
                int textureNumber[10];
                int stadeAnimWeapon1[3];
};


/**
 * @brief Représente un mesh avec ses méthodes d'affichage
 * @author Pierre.L
 * @version 0.1
 * @date 10 dec 2021
 *
 * Header de la classe GeometryEngine
 *
 */
class GeometryEngine : protected QOpenGLFunctions_3_1
{
public:
    ////Constructors
    /*!
    *  \brief Constructeur de la classe GeometryEngine
    *
    *  \param lTextures : Liste des textures du mesh
    *  \param type : type du mesh
    */
    GeometryEngine(std::vector<QOpenGLTexture *>* lTextures,int type);
    ////Destructor
    /*!
    *  \brief Destructeur de la classe GeometryEngine
    *
    */
    virtual ~GeometryEngine();
    ////Methods
    /*!
    *  \brief Dessine le mesh
    */
    void drawGeometry(QOpenGLShaderProgram *program);
    /*!
    *  \brief Dessine le mesh
    *  \param transparency : vrai pour activer la transparance
    */
    void drawGeometryObject(QOpenGLShaderProgram *program,bool transparency);
    /*!
    *  \brief Dessine l'UI
    */
    void drawUI(QOpenGLShaderProgram *program);
    /*!
    *  \brief Initialise l'UI
    */
    void setUI();
    /*!
    *  \brief Actualise l'UI à partir des données du joueur
    */
    void updateUI(int health,int ammo[6],bool key[3],int armor,int weapon,int stadeAnim);
    /*!
    *  \brief Initialise le mesh en tant que plan
    */
    void initPlanGeometry();
    /*!
    *  \brief Initialise le mesh en tant que cube
    */
    void initCubeGeometry();
    /*!
    *  \brief Initialise le mesh à partir d'un Obj
    */
    void initOBJGeometry(std::string path);
    /*!
    *  \brief retourne un  pointeur sur l'UI
    */
    UIgo* getUIgo();
    /*!
    *  \brief Retourne la liste des vertices du mesh
    */

    std::vector<QVector3D> getBaseVertices() const{
        std::vector<QVector3D> v(baseVertices);
        return v;}
    /*!
    *  \brief Retourne la liste des indexs du mesh
    */
    std::vector<int> getIndex() const{
        std::vector<int> v(baseIndex);
        return v;}
    /*!
    *  \brief Retourne la BoundingBox englobant le mesh
    */
    boundingBox getBBox();
    /*!
    *  \brief Retourne le type du joueur
    */
    int getType(){
        return typeGeo;
    }


private:

    ////Methods
    ///
    void setBBValue();
    ////Variables
    std::vector<QVector3D> baseVertices;
    std::vector<int> baseIndex;
    QOpenGLBuffer arrayBuf;
    QOpenGLBuffer indexBuf;
    boundingBox bb;
    std::vector<QOpenGLTexture *>* GeolTextures;
    std::vector<unsigned int> linkFileTextureGeo;
    int typeGeo = -1;
    UIgo UI;
};



#endif // GEOMETRYENGINE_H
