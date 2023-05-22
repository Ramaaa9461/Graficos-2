#pragma once

#include "Lights.h"

#include "Shader.h"


class DirectionalLight : public Lights
{

private:

    static int s_DirectionalLightCount; // Contador de luces puntuales
    int m_index; // Índice de la luz puntualshab

    glm::vec3 direction;
    glm::vec3 color;
    glm::vec3 ambient;
    glm::vec3 diffuse; 
    glm::vec3 specular; 
   
public:

    DllExport DirectionalLight();
    DllExport DirectionalLight(const glm::vec3& direction, const glm::vec3& color,
        const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);

   DllExport void setDirection(const glm::vec3& direction);
   DllExport void setColor(const glm::vec3& color);
   DllExport void setAmbient(const glm::vec3& ambient);
   DllExport void setDiffuse(const glm::vec3& diffuse);
   DllExport void setSpecular(const glm::vec3& specular);
   
   DllExport glm::vec3 getDirection();
   DllExport glm::vec3 getColor();

    DllExport void setUniforms(Shader* shader) override;
};

