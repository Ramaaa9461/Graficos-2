#pragma once

#include "Entity3d.h"

class Cube : public Entity3d
{

private:


    int width, height, depth;
    
    static const int VERTEXPOSITIONSCOUNT = 144;
    static const int INDEXSCOUNT = 36;

    float positions[VERTEXPOSITIONSCOUNT];
    unsigned int indices[INDEXSCOUNT];

    DllExport void  setVertices();
    DllExport void  setIndixs();
    DllExport void calculateVertices();

public:

    DllExport Cube(int initPositionX, int initPositionY, int initPositionZ);

    DllExport void setColor(glm::vec4 RGBA);
    DllExport void updateCameraPos(glm::vec3 cameraPos);
    DllExport void updateLigthPos(glm::vec3 ligthPos);

};

