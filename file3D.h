#ifndef FILE3D_H
#define FILE3D_H

#endif // FILE3D_H


#include <QOpenGLFunctions_3_1>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <math.h>
#include <QVector3D>
#include <QApplication>
#include <QMessageBox>

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <fstream>

using namespace std;


/**
 * @brief Lecture de fichier OBJ
 * @author Remy BARRIOL
 *
 */


bool readOBJ(string path,vector<unsigned int*> &faceVertexIndices,vector<unsigned int> &linkTexture,vector<unsigned int> &linkFileTexture,vector<unsigned int> &linkNormal,vector<float*> &temp_vertices,vector<float*> &textureCoor,vector<float*> &normalCoor)
{
    char char_array[path.length()+1];
    strcpy(char_array, path.c_str());
    QFile infile(char_array);

    int indexFileTexture=0;

    if(!infile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "Erreur : OBJ Introuvable", infile.errorString());
    }
    QTextStream in(&infile);

    while(!in.atEnd())
    {
        QString qLine = in.readLine();
        std::string line = qLine.toStdString();
        if((line[0] == 'v')&&(line[1] == ' '))
        {

            float* vertex=new float[3]();
            sscanf(line.c_str(),"v %f %f %f\n", &vertex[0],&vertex[2],&vertex[1]);
            temp_vertices.push_back(vertex);
        }
        else if((line[0] == 'v')&&(line[1] == 't'))
        {
            float* vertex=new float[2]();
            sscanf(line.c_str(),"vt %f %f %f\n", &vertex[0],&vertex[1]);
            textureCoor.push_back(vertex);

            linkTexture.push_back(0);
        }
        else if((line[0] == 'v')&&(line[1] == 'n'))
        {
            float* vertex=new float[3]();
            sscanf(line.c_str(),"%vn f %f %f\n", &vertex[0],&vertex[1],&vertex[2]);
            normalCoor.push_back(vertex);

            linkNormal.push_back(0);
        }
        else if((line[0] == 'f')&&(line[1] == ' '))
        {
            unsigned int* vertexIndex = new unsigned int[3];
            unsigned int* normalIndex = new unsigned int[3];
            unsigned int* textureIndex = new unsigned int[3];
            sscanf(line.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u\n",&vertexIndex[0],&textureIndex[0],&normalIndex[0],&vertexIndex[1],&textureIndex[1],&normalIndex[1],&vertexIndex[2],&textureIndex[2],&normalIndex[2]);

            linkFileTexture.push_back(indexFileTexture);

            vertexIndex[0]-=1;
            vertexIndex[1]-=1;
            vertexIndex[2]-=1;
            textureIndex[0]-=1;
            textureIndex[1]-=1;
            textureIndex[2]-=1;
            normalIndex[0]-=1;
            normalIndex[1]-=1;
            normalIndex[2]-=1;
            faceVertexIndices.push_back(textureIndex);
            linkTexture.at(textureIndex[0])=vertexIndex[0];
            linkTexture.at(textureIndex[1])=vertexIndex[1];
            linkTexture.at(textureIndex[2])=vertexIndex[2];
            linkNormal.at(normalIndex[0])=vertexIndex[0];
            linkNormal.at(normalIndex[1])=vertexIndex[1];
            linkNormal.at(normalIndex[2])=vertexIndex[2];
        }
        else if((line[0] == 'l')&&(line[1] == ' '))
        {
            unsigned int* vertexIndex = new unsigned int[3];
            sscanf(line.c_str(), "l %d %d\n",&vertexIndex[0],&vertexIndex[1]);
            vertexIndex[2]=-1;
            faceVertexIndices.push_back(vertexIndex);
        }
        else if((line[0] == 'u')&&(line[1] == 's')&&(line[2] == 'e')&&(line[3] == 'm')&&(line[4] == 't')&&(line[5] == 'l'))
        {
            int* value= new int[1];
            sscanf(line.c_str(), "usemtl %d\n",&value[0]);
            indexFileTexture=(value[0]-1);
        }
    }

    return true;
}


