#include "DirectionalLight.h"

#include "ImGuiEngine.h"


int DirectionalLight::s_DirectionalLightCount = 0; // Inicializamos el contador de luces puntuales en 0

DirectionalLight::DirectionalLight() : 
    m_index(s_DirectionalLightCount++),
    direction(glm::vec3(1.0, -1.0f, 0.0f)),
    color(glm::vec3(1.0f)),
    ambient(glm::vec3(0.2f)),
    diffuse(glm::vec3(1.0f)),
    specular(glm::vec3(1.0f))
{
}

DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color, const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) :
    m_index(s_DirectionalLightCount++),
    direction(direction),
    color(color),
    ambient(ambient),
    diffuse(diffuse),
    specular(specular)

{
}

void DirectionalLight::setDirection(const glm::vec3& direction)
{
    this->direction = direction;
}

void DirectionalLight::setColor(const glm::vec3& color) 
{
    this->color = color;
}

void DirectionalLight::setAmbient(const glm::vec3& ambient)
{
    this->ambient = ambient;
}

void DirectionalLight::setDiffuse(const glm::vec3& diffuse)
{
    this->diffuse = diffuse;
}

void DirectionalLight::setSpecular(const glm::vec3& specular)
{
    this->specular = specular;
}

glm::vec3 DirectionalLight::getDirection()
{
    return direction;
}

glm::vec3 DirectionalLight::getColor()
{
    return color;
}

void DirectionalLight::setUniforms(Shader* shader)
{
    shader->Bind();

    shader->SetUniforms1i("numDirectionalLights", s_DirectionalLightCount);
    
    shader->SetUniforms3f("directionalLights[" + std::to_string(m_index) + "].direction", direction.x, direction.y, direction.z);
    shader->SetUniforms3f("directionalLights[" + std::to_string(m_index) + "].color", color.x, color.y, color.z);
    shader->SetUniforms3f("directionalLights[" + std::to_string(m_index) + "].ambient", ambient.x, ambient.y, ambient.z);
    shader->SetUniforms3f("directionalLights[" + std::to_string(m_index) + "].diffuse", diffuse.x, diffuse.y, diffuse.z);
    shader->SetUniforms3f("directionalLights[" + std::to_string(m_index) + "].specular", specular.x, specular.y, specular.z);

    shader->Unbind();

    ImGuiEngine::getImGuiEngine()->imGuiDrawDirectionalLight(this, m_index);
}

