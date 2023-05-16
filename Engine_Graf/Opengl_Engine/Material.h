#pragma once

#include <glm/glm.hpp>

#include "Shader.h"

#include "DDLExport.h"

class Material
{
private:
    glm::vec3 ambientColor;
    glm::vec3 diffuseColor;
    glm::vec3 specularColor;
    float shininess;

public:

   DllExport Material();
   DllExport Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess);

   DllExport void SetUniforms(Shader* shader);

};

