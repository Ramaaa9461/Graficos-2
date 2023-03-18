#pragma once

#include "Shape.h"


class TriangleShape : public Shape
{

private:

    float positions[6];
    unsigned int indices[3];

    DllExport void  setVertices();
    DllExport void  setIndixs();


public:
    
    DllExport TriangleShape(glm::vec4 RGBA, int initPositionX, int initPositionY);



};

