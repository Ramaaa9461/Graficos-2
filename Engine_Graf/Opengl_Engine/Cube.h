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

    DllExport Cube(int initPositionX, int initPositionY, int initPositionZ, Shader* shader);
    
    DllExport void setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);
    DllExport void setMaterial(Material* material);


};

