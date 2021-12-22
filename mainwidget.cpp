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

#include "mainwidget.h"

#include <QMouseEvent>
#include <QKeyEvent>
#include <math.h>
#include <QVector3D>
#include <QApplication>

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    cubeGeometries(0),
    planGeometries(0),
    defaultTexture(0)
{
    setMouseTracking(true);
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete defaultTexture;
    delete cubeGeometries;
    delete planGeometries;
    doneCurrent();
}



//! [0]
void MainWidget::mousePressEvent(QMouseEvent *e)
{
}


void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    keys[event->key()] = false;
    QWidget::keyReleaseEvent(event);
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    keys[event->key()] = true;
    if(event->key() == Qt::Key_P){
        isPause = !isPause;
    }
    else if(event->key() == Qt::Key_Escape)
    {
         QCoreApplication::quit();
    }
    QWidget::keyPressEvent(event);
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void MainWidget::timerEvent(QTimerEvent *)
{

    //Recalcul de la caméra
    //camera->actualiseMatrix();
    mainLoop();
    update();
}

void MainWidget::mouseMoveEvent(QMouseEvent* event){
    const int maxDeltaX = 30;

    //Calcul de la différence entre la dernière pos de la souris et maintenant
    int deltax = width()/2-event->pos().x();
    int deltay = height()/2 - event->pos().y();

    //On restraint la valeur du delta
    deltax = std::max(deltax,-maxDeltaX);
    deltax = std::min(deltax,maxDeltaX);
    /*qInfo() << "X:" <<deltax;
    qInfo() << "Y:" <<deltay;*/
    //On tourne le joueur
    player->turnPlayer(deltax/(maxDeltaX*1.0));

    QPoint glob = mapToGlobal(QPoint(width()/2,height()/2));
    QCursor::setPos(glob);
}

void MainWidget::initializeGL()
{

    transformation t;
    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();
//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]
    //Graphe de scène


    cubeGeometries = new GeometryEngine;
    cubeGeometries->initCubeGeometry();
    planGeometries = new GeometryEngine;
    planGeometries->initPlanGeometry();


    root = new gameobject(nullptr,transformation(),0);
    map = new gameobject(nullptr,transformation(),0);
    entities = new gameobject(nullptr,transformation(),0);

    root->addChild(map);
    root->addChild(entities);


    t = transformation();
    t.addTranslation(0,50,0);
    player = new Player(cubeGeometries,t,defaultTexture,map);
    entities->addChild(player);

    parsingMapFile();
    // Use QBasicTimer because its faster than QTimer
    timer.start(12, this);
}

//! [3]
void MainWidget::initShaders()
{
    // Compile vertex shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compile fragment shader
    if (!program.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Link shader pipeline
    if (!program.link())
        close();

    // Bind shader pipeline for use
    if (!program.bind())
        close();
}
//! [3]
//! [4]
void MainWidget::initTextures()
{
    // Load cube.png image
    defaultTexture = new QOpenGLTexture(QImage(":/textures/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    defaultTexture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    defaultTexture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    defaultTexture->setWrapMode(QOpenGLTexture::Repeat);

    parsingTextureFile();
}
//! [4]
//! [5]
void MainWidget::resizeGL(int w, int h)
{
    // Calculate aspect ratio
    qreal aspect = qreal(w) / qreal(h ? h : 1);
    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 2.0, zFar = 600.0, fov = 45.0;


    // Reset projection
    QMatrix4x4 projection;
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);

    camera = new Camera(QMatrix4x4(projection));
    camera->associatePlayer(player);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //texture->bind();

    program.setUniformValue("mvp_matrix", camera->getMVPMatrix());

    //Affichage du graphe de scène
    root->displayAll(&program, camera->getMVPMatrix());
}


void MainWidget::parsingTextureFile(){
    //////////
    /// Parsing de fichier
    /////////
    QFile infile(":/textures.txt");

    TypeMesh typeOfObject;
    std::string path;
    transformation t;
    GeometryEngine * mesh;
    if(!infile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", infile.errorString());
    }
    QTextStream in(&infile);



    while (!in.atEnd())
    {
        QString qLine = in.readLine();
        std::string line = qLine.toStdString();
        QOpenGLTexture * texture;
        std::string path;

        if(line[0] == '#') {
            //qDebug() << "Commentaire : " << qPrintable(qLine);

        }else{
            std::stringstream(line) >> path;

            lTextures.push_back(new QOpenGLTexture(QImage(QString::fromStdString(path)).mirrored()));

            // Set nearest filtering mode for texture minification
            lTextures.back()->setMinificationFilter(QOpenGLTexture::Nearest);

            // Set bilinear filtering mode for texture magnification
            lTextures.back()->setMagnificationFilter(QOpenGLTexture::Linear);

            // Wrap texture coordinates by repeating
            // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
            lTextures.back()->setWrapMode(QOpenGLTexture::Repeat);
        }

    }
}



void MainWidget::parsingMapFile(){
    //////////
    /// Parsing de fichier
    /////////
    QFile infile(":/map.txt");

    TypeMesh typeOfObject;
    int valueOfObject,idTexture;
    double tx, ty, tz, rx, ry, rz, sx, sy, sz;

    transformation t;
    GeometryEngine * mesh;
    if(!infile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", infile.errorString());
    }
    QTextStream in(&infile);



    while (!in.atEnd())
    {
        QString qLine = in.readLine();
        std::string line = qLine.toStdString();
        if(line[0] == '#') {
            //qDebug() << "Commentaire : " << qPrintable(qLine);

        }else{
            std::stringstream(line) >> valueOfObject >> tx >> ty >> tz >> rx >> ry >> rz >> sx >> sy >> sz >> idTexture;
            std::string path;
            typeOfObject = (TypeMesh)valueOfObject;
            //gameengine mesh;
            switch(typeOfObject){
                case PLAN:
                    mesh = planGeometries;
                        break;
                case CUBE:
                    mesh = cubeGeometries;
                        break;
                case SPHERE:
                    mesh = planGeometries;
                        break;
                case OBJECT:
                    //infile >> path;
                    //mesh = gameengine(object,path)
                    mesh = planGeometries;
                        break;
            }
            t = transformation();
            t.addTranslation(tx,ty,tz);

            t.addRotationX(rx);
            t.addRotationY(ry);
            t.addRotationZ(rz);
            t.addScale(sx,sy,sz);
            QOpenGLTexture * texture = defaultTexture;
            //Choix texture
            qDebug() << idTexture << endl;
            if(idTexture < lTextures.size() && idTexture>=0 ){
                texture = lTextures[idTexture];
            }
            //appliquer les nouvelles transformations à t
            gameobject * go = new gameobject(mesh,t,texture);
            boundingBox bb = go->getBBox();
            //qDebug() <<"\tTransforms : " << bb.getMinVertex() << " " << bb.getMaxVertex() << "" << go->getBarycentre() <<endl;

            map->addChild(go);
        }

    }




    infile.close();
}

void MainWidget::mainLoop(){
    if(!isPause){
        //Inputs Joueur
        if(keys[Qt::Key_Z])
        {
            player->goForward();
        }
        else if(keys[Qt::Key_S])
        {
            player->goBackward();
        }
        if(keys[Qt::Key_Q])
        {
            player->goLeft();
        }
        else if(keys[Qt::Key_D])
        {
            player->goRight();
        }
        if(keys[Qt::Key_Left])
        {
            player->turnLeft();
        }
        else if(keys[Qt::Key_Right])
        {
            player->turnRight();
        }
        player->actualisePosition();
        camera->actualiseVueMatrix();
    }

}
