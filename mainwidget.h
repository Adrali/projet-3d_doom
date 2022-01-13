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

#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "geometryengine.h"
#include "gameobject.h"
#include "transformation.h"
#include "player.h"
#include "camera.h"
#include "ennemy.h"
#include "loot.h"
#include "const_entity.h"
#include "gameTime.h"

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_1>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QTimer>
#include <QMessageBox>
#include <QtDebug>
#include <QSound>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
class GeometryEngine;

enum TypeMesh {PLAN,CUBE,SPHERE,OBJECT};



/**
 * @brief Classe centrale du moteur. Gère la scène 3D ainsi que la gameloop
 * @author Pierre.L
 * @version 0.1
 * @date 10 dec 2021
 *
 * Header de la classe MainWidget
 *
 */
class MainWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_1
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();

protected:
    /*!
    *  \brief Fonction qui gère les appuis des touches de la souris
    */
    void mousePressEvent(QMouseEvent *e) override;
    /*!
    *  \brief Fonction qui gère les fin d'appuis des touches de le clavier
    */
    void keyReleaseEvent(QKeyEvent *event) override;
    /*!
    *  \brief Fonction qui gère les appuis des touches de la clavier
    */
    void keyPressEvent( QKeyEvent * event ) override;
    /*!
    *  \brief Fonction qui gère les fin d'appuis des touches de la souris
    */
    void mouseReleaseEvent(QMouseEvent *e) override;
    /*!
    *  \brief Fonction appelée lors du déplacement de la souris
    *  Cette fonction gère le déplacement d'angle de la caméra et la mobilité du joueur
    */
    void mouseMoveEvent(QMouseEvent* event);
    /*!
    *  \brief Fonction appelé pèriodiquement par Qt
    */
    void timerEvent(QTimerEvent *e) override;
    /*!
    *  \brief Initialise la plupars des objets nécéssaire au fonctionnement du moteur
    */
    void initializeGL() override;
    /*!
    *  \brief Fonction appelé quand la taille de la fenêtre est modifé
    */
    void resizeGL(int w, int h) override;
    /*!
    *  \brief Affiche les objets présents dans la scène
    */
    void paintGL() override;
    /*!
    *  \brief Boucle de jeu qui gère les updates des objets de la scène
    */
    void mainLoop();
    /*!
    *  \brief Parse le fichier de map pour construire la map et remplir le graphe de scène
    */
    void parsingMapFile();
    /*!
    *  \brief Initialise le tableau des textures
    */
    void parsingTextureFile();
    /*!
    *  \brief Initialise les listes d'entités
    */
    void parsingEntityFile();
    /*!
    *  \brief Initialise les shaders d'openGL
    */
    void initShaders();
    /*!
    *  \brief Initialise des textures
    */
    void initTextures();
    /*!
    *  \brief Active/Désactive le plein écran
    */
    void on_action_Fullscreen_triggered();
    /*!
    *  \brief Initialise le niveau 1
    */
    void initialiseLevel();

private:
    QTimer *timers;
    QMap<int, bool> keys;
    QBasicTimer timer;
    QOpenGLShaderProgram program;
    ////Variables
    //Geometries
    GeometryEngine *cubeGeometries;
    GeometryEngine *planGeometries;
    std::vector<GeometryEngine*> objGeometries;
    //Gameobjects
    gameobject * root;
    gameobject * map;
    gameobject * entities;
    gameobject * UI;
    Player * player;
    std::vector<Ennemy *> lEnnemy;
    std::vector<Loot *> lLoots;

    //Textures
    QOpenGLTexture *defaultTexture;
    std::vector<QOpenGLTexture *> lTextures;
    QOpenGLTexture * medicTexture;
    QOpenGLTexture * monsterTexture;
    QOpenGLTexture * armorTexture;
    //Cameras
    Camera * camera;
    //gameBooleans
    bool isPause = false;
    bool isMouseForward = false;

    //Sound
    QSound * mainMusic;

};

#endif // MAINWIDGET_H
