#pragma once

#include "Lights.h"
#include "Shader.h"
#include "Cube.h"

class SpotLight : public Lights
{

private:

    static int s_spotLightCount; // Contador de luces puntuales
    int m_index; // Índice de la luz puntual

    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 color;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float constant;
    float linear;
    float quadratic;
    float cutoff;
    float outerCutoff;

public:

    DllExport SpotLight();
    DllExport ~SpotLight();

    DllExport SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
        const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
        float constant, float linear, float quadratic, float cutoff, float outerCutoff);
    
    DllExport void setPosition(const glm::vec3& position);
    DllExport void setDirection(const glm::vec3& direction);
    DllExport void setColor(const glm::vec3& color);

    DllExport void setAmbient(const glm::vec3& ambient);
    DllExport void setDiffuse(const glm::vec3& diffuse);
    DllExport void setSpecular(const glm::vec3& specular);
    DllExport void setAttenuation(float constant, float linear, float quadratic);
    DllExport void setCutoff(float cutoff);
    DllExport void setOuterCutoff(float outerCutoff);
  
    DllExport glm::vec3 getPosition();
    DllExport glm::vec3 getDirection();
    DllExport glm::vec3 getColor();
    DllExport float getCutoff();
    DllExport float getOuterCutoff();


    DllExport void setUniforms(Shader* shader) override;
};

