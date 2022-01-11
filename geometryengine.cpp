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

#include "geometryengine.h"

#include <iostream>

#include <QVector2D>
#include <QVector3D>
#include <string.h>
#include "file3D.h"
#include "mainwidget.h"





//! [0]

/**
 *
 * Remy BARRIOL
 * Gestion de l'initialisation des meshs suivant leurs types
 */
GeometryEngine::GeometryEngine(std::vector<QOpenGLTexture *>* lTextures,int type)
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();
    GeolTextures=lTextures;
    // Initializes cube geometry and transfers it to VBOs
    //initCubeGeometry();

    typeGeo=type;
    if(type==0)
        initCubeGeometry();
    else if(type==1)
        initPlanGeometry();
    else if(type==2)
        initOBJGeometry(":/obj/FirstStage.obj");
    else if(type==3)
        initOBJGeometry(":/obj/Skybox.obj");
    else if(type==4)
        initOBJGeometry(":/obj/UI2.obj");
    else if(type==5)
        initOBJGeometry(":/obj/Ammo.obj");
    else if(type==6)
        initOBJGeometry(":/obj/Armor.obj");
    else if(type==7)
        initOBJGeometry(":/obj/Health.obj");
    else if(type==8)
        initOBJGeometry(":/obj/BlueKey.obj");
    else if(type==9)
        initOBJGeometry(":/obj/YellowKey.obj");
    else if(type==10)
        initOBJGeometry(":/obj/RedKey.obj");
    else if(type==11)
        initOBJGeometry(":/obj/Ennemie.obj");
    else if(type==12)
        initOBJGeometry(":/obj/Porte.obj");

}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}

void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    // Hence 4 vertices per face and 6 faces vertices = 24 vertices
    unsigned int vertexNumber = 24 ;
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };
    baseVertices.clear();
    for(VertexData ver : vertices){
        baseVertices.push_back(ver.position);
    }


    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    unsigned int indexCount = 34; //Careful update indicesNumber when creating new geometry
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };
    baseIndex.clear();
    for(int i : indices){
        baseIndex.push_back(i);
    }
//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices,  indexCount* sizeof(GLushort));
    setBBValue();
//! [1]
}

void GeometryEngine::initPlanGeometry(){
    int nbrVertex = 64;
    float MIN_POSITION = 0.0f;
    float POSITION_RANGE = 10.0f; //Taille entre deux vertex

    unsigned int vertexNumber = nbrVertex * nbrVertex ;

    VertexData vertices[nbrVertex*nbrVertex];

    int offset = 0;

    // First, build the data for the vertex buffer
    for (int y = 0; y <nbrVertex; y++)
        for (int x = 0; x < nbrVertex; x++) {
            float xRatio = x / (float) (nbrVertex - 1);

            float yRatio = 1.0f - (y / (float) (nbrVertex - 1));

            float xPosition = MIN_POSITION + (xRatio * POSITION_RANGE);
            float yPosition = MIN_POSITION + (yRatio * POSITION_RANGE);

             vertices[offset++]= {QVector3D(xPosition,yPosition,0.0f), QVector2D(float(x)/(nbrVertex-1),float(y)/(nbrVertex-1))};


    };
    baseVertices.clear();
    for(VertexData ver : vertices){
        baseVertices.push_back(ver.position);
    }
    int numStripsRequired = nbrVertex - 1;
    int numDegensRequired = 2 * (numStripsRequired - 1);
    int verticesPerStrip = 2 * nbrVertex;

    GLushort heightMapIndexData [(verticesPerStrip * numStripsRequired)
            + numDegensRequired];

    offset = 0;

    for (int y = 0; y <nbrVertex- 1; y++) {      if (y > 0) {
            // Degenerate begin: repeat first vertex
            heightMapIndexData[offset++] = (short) (y * nbrVertex);
        }

        for (int x = 0; x<nbrVertex; x++) {
            // One part of the strip
            heightMapIndexData[offset++] = (short) ((y * nbrVertex) + x);
            heightMapIndexData[offset++] = (short) (((y + 1) * nbrVertex) + x);
        }

        if (y<nbrVertex - 2) {
            // Degenerate end: repeat last vertex
            heightMapIndexData[offset++] = (short) (((y + 1) *nbrVertex) + (nbrVertex - 1));
        }
    }
    unsigned int indexCount =  sizeof(heightMapIndexData)/sizeof(heightMapIndexData[0]);
    baseIndex.clear();
    for(int i : heightMapIndexData){
        baseIndex.push_back(i);
    }


//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(heightMapIndexData,  indexCount * sizeof(GLushort));
    setBBValue();
}




/**
 *
 * Remy BARRIOL
 * Gestion de l'affichage des meshs suivant leurs types (l'UI est un OBJ avec un affichage spéciale)
 */

void GeometryEngine::drawGeometry(QOpenGLShaderProgram *program)
{

    int transColor = program->attributeLocation("red");
    program->setAttributeValue(transColor,0.0f);
    if((typeGeo==1)||(typeGeo==0))
    {
        // Tell OpenGL which VBOs to use
        arrayBuf.bind();
        indexBuf.bind();

        // Offset for position
        quintptr offset = 0;

        // Tell OpenGL programmable pipeline how to locate vertex position data
        int vertexLocation = program->attributeLocation("a_position");
        program->enableAttributeArray(vertexLocation);
        program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

        // Offset for texture coordinate
        offset += sizeof(QVector3D);

        // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
        int texcoordLocation = program->attributeLocation("a_texcoord");
        program->enableAttributeArray(texcoordLocation);
        program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

        // Draw cube geometry using indices from VBO 1
        glDrawElements(GL_TRIANGLE_STRIP, indexBuf.size(), GL_UNSIGNED_SHORT, 0); //Careful update indicesNumber when creating new geometry
    }
    else if(typeGeo>1)
    {
        if(typeGeo==4)
            drawUI(program);
        else if((typeGeo>=5)&&(typeGeo<=11))
            drawGeometryObject(program,true);
        else
            drawGeometryObject(program,false);
    }
}


/**
 *
 * Remy BARRIOL
 * Initialisation de la geometrie pour les OBJs
 */


void GeometryEngine::initOBJGeometry(std::string path)
{
    std::vector<unsigned int*> faceVertexIndices;
    std::vector<unsigned int> linkTexture;
    std::vector<unsigned int> linkFileTexture;
    std::vector<unsigned int> linkNormal;
    std::vector<float*> temp_vertices;
    std::vector<float*> textureCoor;
    std::vector<float*> normalCoor;
    readOBJ(path,faceVertexIndices,linkTexture,linkFileTexture,linkNormal,temp_vertices,textureCoor,normalCoor);
    unsigned int vertexNumber = linkTexture.size();
    VertexData vertices[vertexNumber];

    for(unsigned int i=0;i<vertexNumber;i++)
    {
        vertices[i]={QVector3D(temp_vertices.at(linkTexture.at(i))[0],temp_vertices.at(linkTexture.at(i))[1],temp_vertices.at(linkTexture.at(i))[2]), QVector2D(textureCoor.at(i)[0],textureCoor.at(i)[1])};
        baseVertices.push_back(QVector3D(temp_vertices.at(linkTexture.at(i))[0],temp_vertices.at(linkTexture.at(i))[1],temp_vertices.at(linkTexture.at(i))[2]));
    }

    unsigned int indexCount = faceVertexIndices.size()*3;
    GLushort indices[indexCount];
    int realIndex=-1;
    for(unsigned int i=0;i<faceVertexIndices.size();i++)
    {
        indices[++realIndex]=faceVertexIndices.at(i)[0];
        indices[++realIndex]=faceVertexIndices.at(i)[1];
        indices[++realIndex]=faceVertexIndices.at(i)[2];
        baseIndex.push_back(faceVertexIndices.at(i)[0]);
        baseIndex.push_back(faceVertexIndices.at(i)[1]);
        baseIndex.push_back(faceVertexIndices.at(i)[2]);
    }
    linkFileTextureGeo=linkFileTexture;

    arrayBuf.bind();
    arrayBuf.allocate(vertices, vertexNumber * sizeof(VertexData));

    indexBuf.bind();
    indexBuf.allocate(indices,  indexCount* sizeof(GLushort));
}


/**
 *
 * Remy BARRIOL
 * Affichage des OBJs (Choix de texture triangle par triangle)
 */
void GeometryEngine::drawGeometryObject(QOpenGLShaderProgram *program,bool transparency)
{
    arrayBuf.bind();
    indexBuf.bind();

    quintptr offset = 0;
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));


    //Pour chaque triangle, on regarde la texture qui lui correspond
    for(int i=0;i<indexBuf.size()/3;i++)
    {
        if(i<linkFileTextureGeo.size())
        {
            GeolTextures->at(linkFileTextureGeo.at(i))->bind();
            if(transparency)
            {
                glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
                glEnable(GL_BLEND);
            }
            glDrawElements(GL_TRIANGLE_FAN, 3 , GL_UNSIGNED_SHORT, (GLvoid*)(sizeof(GLushort)*i*3));
            if(transparency)
                glDisable(GL_BLEND);
        }
    }
}

/**
 *
 * Remy BARRIOL
 * Mise à jour des informations de l'interface
 */
void GeometryEngine::updateUI(int health,int ammo[6],bool key[3],int armor,int weapon,int stadeAnim)
{
    UI.health=health;
    UI.armor=armor;
    UI.weapon=weapon;
    UI.stadeAnim=stadeAnim;
    for(int i=0;i<6;i++)
    {
        UI.ammo[i]=ammo[i];
    }
    for(int i=0;i<3;i++)
    {
        UI.key[i]=key[i];
    }

}

/**
 *
 * Remy BARRIOL
 * Initialisation des valeurs de l'interface
 */
void GeometryEngine::setUI()
{
    UI.key[0]=false;
    UI.key[1]=false;
    UI.key[2]=false;
    UI.ammo[0]=0;
    UI.ammo[1]=40;
    UI.ammo[2]=0;
    UI.ammo[3]=0;
    UI.ammo[4]=0;
    UI.ammo[5]=0;
    int dep=64;
    for(int i=0;i<10;i++)
    {
        UI.textureNumber[i]=dep++;
    }
    for(int i=0;i<2;i++)
    {
        UI.ammo1[i]=-1;
        UI.ammo2[i]=-1;
        UI.ammo3[i]=-1;
        UI.health1[i]=-1;
        UI.health2[i]=-1;
        UI.health3[i]=-1;
        UI.armor1[i]=-1;
        UI.armor2[i]=-1;
        UI.armor3[i]=-1;
        UI.head1[i]=-1;
        UI.weapon1[i]=-1;
        UI.redKey[i]=-1;
        UI.blueKey[i]=-1;
        UI.yellowKey[i]=-1;

        UI.weaponStade1[i]=-1;
        UI.weaponStade2[i]=-1;
        UI.weaponStade3[i]=-1;
    }
    UI.stadeAnimWeapon1[0]=50;
    UI.stadeAnimWeapon1[1]=51;
    UI.stadeAnimWeapon1[2]=52;
    for(unsigned int i=0;i<linkFileTextureGeo.size();i++)
    {
        if(linkFileTextureGeo.at(i)==70-1)
        {
            if(UI.ammo1[0]==-1)
                UI.ammo1[0]=i;
            else
                UI.ammo1[1]=i;
        }
        if(linkFileTextureGeo.at(i)==71-1)
        {
            if(UI.ammo2[0]==-1)
                UI.ammo2[0]=i;
            else
                UI.ammo2[1]=i;
        }
        if(linkFileTextureGeo.at(i)==72-1)
        {
            if(UI.ammo3[0]==-1)
                UI.ammo3[0]=i;
            else
                UI.ammo3[1]=i;
        }
        if(linkFileTextureGeo.at(i)==67-1)
        {
            if(UI.health1[0]==-1)
                UI.health1[0]=i;
            else
                UI.health1[1]=i;
        }
        if(linkFileTextureGeo.at(i)==68-1)
        {
            if(UI.health2[0]==-1)
                UI.health2[0]=i;
            else
                UI.health2[1]=i;
        }
        if(linkFileTextureGeo.at(i)==69-1)
        {
            if(UI.health3[0]==-1)
                UI.health3[0]=i;
            else
                UI.health3[1]=i;
        }
        if(linkFileTextureGeo.at(i)==64-1)
        {
            if(UI.armor1[0]==-1)
                UI.armor1[0]=i;
            else
                UI.armor1[1]=i;
        }
        if(linkFileTextureGeo.at(i)==65-1)
        {
            if(UI.armor2[0]==-1)
                UI.armor2[0]=i;
            else
                UI.armor2[1]=i;
        }
        if(linkFileTextureGeo.at(i)==66-1)
        {
            if(UI.armor3[0]==-1)
                UI.armor3[0]=i;
            else
                UI.armor3[1]=i;
        }
        if(linkFileTextureGeo.at(i)==60-1)
        {
            if(UI.head1[0]==-1)
                UI.head1[0]=i;
            else
                UI.head1[1]=i;
        }
        if(linkFileTextureGeo.at(i)==49-1)
        {
            if(UI.weapon1[0]==-1)
                UI.weapon1[0]=i;
            else
                UI.weapon1[1]=i;
        }
        if(linkFileTextureGeo.at(i)==43-1)
        {
            if(UI.redKey[0]==-1)
                UI.redKey[0]=i;
            else
                UI.redKey[1]=i;
        }
        if(linkFileTextureGeo.at(i)==44-1)
        {
            if(UI.yellowKey[0]==-1)
                UI.yellowKey[0]=i;
            else
                UI.yellowKey[1]=i;
        }
        if(linkFileTextureGeo.at(i)==45-1)
        {
            if(UI.blueKey[0]==-1)
                UI.blueKey[0]=i;
            else
                UI.blueKey[1]=i;
        }
        if(linkFileTextureGeo.at(i)==50-1)
        {
            if(UI.weaponStade1[0]==-1)
                UI.weaponStade1[0]=i;
            else
                UI.weaponStade1[1]=i;
        }
        if(linkFileTextureGeo.at(i)==51-1)
        {
            if(UI.weaponStade2[0]==-1)
                UI.weaponStade2[0]=i;
            else
                UI.weaponStade2[1]=i;
        }
        if(linkFileTextureGeo.at(i)==52-1)
        {
            if(UI.weaponStade3[0]==-1)
                UI.weaponStade3[0]=i;
            else
                UI.weaponStade3[1]=i;
        }
    }

}

UIgo* GeometryEngine::getUIgo()
{
    return &UI;
}



/**
 *
 * Remy BARRIOL
 * Choix des textures selon les valeurs de l'interface
 */
void GeometryEngine::drawUI(QOpenGLShaderProgram *program)
{
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    //qDebug()<<indexBuf.size()<<"  ==  "<<linkFileTextureGeo.size();



    for(int i=0;i<indexBuf.size()/3;i++)
    {
        if(i<linkFileTextureGeo.size())
        {

            int Tex=0;

            if((UI.ammo1[0]==i)||(UI.ammo1[1]==i))
            {
                int number=UI.ammo[UI.weapon]/100;
                Tex=UI.textureNumber[number]-1;
            }
            else if((UI.ammo2[0]==i)||(UI.ammo2[1]==i))
            {
                int number=UI.ammo[UI.weapon]/10;
                int number1=(number/10)*10;
                number-=number1;
                Tex=UI.textureNumber[number]-1;
            }
            else if((UI.ammo3[0]==i)||(UI.ammo3[1]==i))
            {
                int number=UI.ammo[UI.weapon]/10;
                int number1=number*10;
                int number2=UI.ammo[UI.weapon]-number1;
                Tex=UI.textureNumber[number2]-1;
            }
            else if((UI.health1[0]==i)||(UI.health1[1]==i))
            {
                int number=UI.health/100;
                Tex=UI.textureNumber[number]-1;
            }
            else if((UI.health2[0]==i)||(UI.health2[1]==i))
            {
                int number=UI.health/10;
                int number1=(number/10)*10;
                number-=number1;
                Tex=UI.textureNumber[number]-1;
            }
            else if((UI.health3[0]==i)||(UI.health3[1]==i))
            {
                int number=UI.health/10;
                int number1=number*10;
                int number2=UI.health-number1;
                Tex=UI.textureNumber[number2]-1;
            }
            else if((UI.armor1[0]==i)||(UI.armor1[1]==i))
            {
                int number=UI.armor/100;
                Tex=UI.textureNumber[number]-1;
            }
            else if((UI.armor2[0]==i)||(UI.armor2[1]==i))
            {
                int number=UI.armor/10;
                int number1=(number/10)*10;
                number-=number1;
                Tex=UI.textureNumber[number]-1;
            }
            else if((UI.armor3[0]==i)||(UI.armor3[1]==i))
            {
                int number=UI.armor/10;
                int number1=number*10;
                int number2=UI.armor-number1;
                Tex=UI.textureNumber[number2]-1;
            }
            else if((UI.head1[0]==i)||(UI.head1[1]==i))
            {
                Tex=59+UI.head-1;
            }
            else if((UI.weapon1[0]==i)||(UI.weapon1[1]==i))
            {
                if(UI.weapon==1)
                    Tex=48-1;
            }
            else if((UI.redKey[0]==i)||(UI.redKey[1]==i))
            {
               if(UI.key[0])
                    Tex=43-1;
               else
                    Tex=42-1;
            }
            else if((UI.yellowKey[0]==i)||(UI.yellowKey[1]==i))
            {
                if(UI.key[1])
                     Tex=44-1;
                else
                     Tex=42-1;
            }
            else if((UI.blueKey[0]==i)||(UI.blueKey[1]==i))
            {
                if(UI.key[2])
                     Tex=45-1;
                else
                     Tex=42-1;
            }
            else if((UI.weaponStade1[0]==i)||(UI.weaponStade1[1]==i))
            {
                if(UI.stadeAnim==0)
                    Tex=50-1;
                else
                    Tex=42-1;
            }
            else if((UI.weaponStade2[0]==i)||(UI.weaponStade2[1]==i))
            {
                if(UI.stadeAnim==1)
                    Tex=51-1;
                else
                    Tex=42-1;
            }
            else if((UI.weaponStade3[0]==i)||(UI.weaponStade3[1]==i))
            {
                if(UI.stadeAnim==2)
                    Tex=52-1;
                else
                    Tex=42-1;
            }
            else
                Tex=linkFileTextureGeo.at(i);
            GeolTextures->at(Tex)->bind();


            //Gère la transparence seulement pour l'interface
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            glEnable(GL_BLEND);
            glDrawElements(GL_TRIANGLE_FAN, 3 , GL_UNSIGNED_SHORT, (GLvoid*)(sizeof(GLushort)*i*3));
            glDisable(GL_BLEND);

        }
    }
}


boundingBox GeometryEngine::getBBox(){
    return bb;

}
void GeometryEngine::setBBValue(){
    bb = boundingBox(baseVertices);
}



