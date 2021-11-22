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


#define RADIUS_SOLEIL 15.0
#define DISTANCE_SOLEIL_TERRE 50.0
#define INCLINAISON_TERRE_Z -23.44
#define RADIUS_TERRE 6.378
#define DISTANCE_TERRE_LUNE 20.405
#define INCLINAISON_TERRE_LUNE 5.14
#define RADIUS_LUNE 1.738
#define INCLINAISON_LUNE_Z 6.68

MainWidget::MainWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    geometries(0),
    texture(0),
    angularSpeed(0)
{
}

MainWidget::~MainWidget()
{
    // Make sure the context is current when deleting the texture
    // and the buffers.
    makeCurrent();
    delete texture;
    delete geometries;
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
    QWidget::keyPressEvent(event);
}

void MainWidget::mouseReleaseEvent(QMouseEvent *e)
{

}
//! [0]

//! [1]
void MainWidget::timerEvent(QTimerEvent *)
{
    float tValue = 2.0f;
    if(keys[Qt::Key_Z])
    {
        projection.translate(0,-tValue,0);
    }
    else if(keys[Qt::Key_S])
    {
        projection.translate(0,tValue,0);
    }
    if(keys[Qt::Key_Q])
    {
        projection.translate(tValue,0,0);
    }
    else if(keys[Qt::Key_D])
    {
        projection.translate(-tValue,0,0);
    }
    if(keys[Qt::Key_Up])
    {
        projection.translate(0,0,tValue);
    }
    else if(keys[Qt::Key_Down])
    {
        projection.translate(0,0,-tValue);
    }
    update();
}
//! [1]

void MainWidget::initializeGL()
{
    QFile infile("/home/e20200007675/M2_IMAGINE/Projet_Moteur_Jeux/TP1_2_code/map.txt");

    transformation t;
    TypeMesh typeOfObject;
    int valueOfObject;
    double tx, ty, tz, rx, ry, rz,sx,sy,sz;

    initializeOpenGLFunctions();

    glClearColor(0, 0, 0, 1);

    initShaders();
    initTextures();
    qDebug() <<"Test" <<endl;
//! [2]
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);
//! [2]
    //Graphe de scène
    geometries = new GeometryEngine;
    root = new gameobject(nullptr,transformation());


    if(!infile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", infile.errorString());
    }


    QTextStream in(&infile);

    while (!in.atEnd())
    {
        std::string line = in.readLine().toStdString();
        std::stringstream(line) >> valueOfObject >> tx >> ty >> tz >> rx >> ry >> rz >> sx >> sy >> sz;
        std::string path;
        typeOfObject = (TypeMesh)valueOfObject;

        //gameengine mesh;
        switch(typeOfObject){
            case PLAN:
                //mesh = gameengine(plan)
                    break;
            case CUBE:
                //mesh = gameengine(plan)
                    break;
            case SPHERE:
                //mesh = gameengine(sphere)
                    break;
            case OBJECT:
                //infile >> path;
                //mesh = gameengine(object,path)
                    break;
        }
        transformation  t = transformation();
        t.addTranslation(tx,ty,tz);
        t.addRotationX(rx);
        t.addRotationY(ry);
        t.addRotationZ(rz);
        t.addScale(sx,sy,sz);
        //appliquer les nouvelles transformations à t
        gameobject * go = new gameobject(geometries,t);
        qDebug() <<"\tTransforms : " << tx << " " << ty <<" " << tz <<endl;
        qDebug() << "\tRotations : " << rx << " " << ry << " " << rz << endl;
        qDebug() << "\tScale " << sx << " " << sy << " " << sz << endl;
        root->addChild(go);
    }
    infile.close();
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
    texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());

    // Set nearest filtering mode for texture minification
    texture->setMinificationFilter(QOpenGLTexture::Nearest);

    // Set bilinear filtering mode for texture magnification
    texture->setMagnificationFilter(QOpenGLTexture::Linear);

    // Wrap texture coordinates by repeating
    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
    texture->setWrapMode(QOpenGLTexture::Repeat);
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
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}
//! [5]

void MainWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind();

//! [6]
    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program.setUniformValue("mvp_matrix", projection * matrix);
//! [6]

    // Use texture unit 0 which contains cube.png
    //program.setUniformValue("texture", 0);

    // Draw cube geometry
    //geometries->drawCubeGeometry(&program);
    root->displayAll(&program,projection);
}
