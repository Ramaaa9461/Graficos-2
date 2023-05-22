#include "Material.h"
#include <GL/glew.h>



Material::Material() :
    ambientColor(glm::vec3(1.0f, 1.0f, 1.0f)),
    diffuseColor(glm::vec3(1.0f, 1.0f, 1.0f)),
    specularColor(glm::vec3(1.0f, 1.0f, 1.0f)),
    shininess(32.0f)
{
}

Material::Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess) :
    ambientColor(ambient),
    diffuseColor(diffuse),
    specularColor(specular),
    shininess(shininess)
{
}


void Material::SetUniforms(Shader* shader)
{
    shader->SetUniforms3f("material.ambient", ambientColor.x, ambientColor.y, ambientColor.z);
    shader->SetUniforms3f("material.diffuse", diffuseColor.x, diffuseColor.y, diffuseColor.z);
    shader->SetUniforms3f("material.specular", specularColor.x, specularColor.y, specularColor.z);
    shader->SetUniforms1f("material.shininess", shininess);
}

