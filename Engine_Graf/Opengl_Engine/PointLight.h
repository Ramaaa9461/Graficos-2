#pragma once

#include "Lights.h"

#include "Shader.h"

class PointLight : public Lights
{
private:

    static int s_pointLightCount; // Contador de luces puntuales
    int m_index; // Índice de la luz puntualshab

    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float     constant;
    float     linear;
    float     quadratic;

public:

    DllExport PointLight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse,
    glm::vec3 specular, float constant, float linear, float quadratic);

    DllExport PointLight();

    DllExport void setPosition(const glm::vec3& position);
    DllExport void setColor(const glm::vec3& color);
    DllExport void setAmbient(const glm::vec3& ambient);
    DllExport void setDiffuse(const glm::vec3& diffuse);
    DllExport void setSpecular(const glm::vec3& specular);
    DllExport void setAttenuation(float constant, float linear, float quadratic);

    DllExport glm::vec3 getPosition();
    DllExport glm::vec3 getColor();


    DllExport void setUniforms(Shader* shader);
};

