#include "PointLight.h"

#include "ImGuiEngine.h"

int PointLight::s_pointLightCount = 0; // Inicializamos el contador de luces puntuales en 0

PointLight::PointLight(glm::vec3 position, glm::vec3 color, glm::vec3 ambient, glm::vec3 diffuse, 
	glm::vec3 specular, float constant, float linear, float quadratic) : m_index(s_pointLightCount++), position(position), 
	color(color), ambient(ambient),	diffuse(diffuse), constant(constant), linear(linear), quadratic(quadratic)
{
}

PointLight::PointLight() :
	m_index(s_pointLightCount++),
	position(glm::vec3(0.0f)), 
	color(glm::vec3(1.0f)), 
	ambient(glm::vec3(0.2f)),
	diffuse(glm::vec3(1.0f)),
	specular(glm::vec3(1.0f)),
	constant(1.0f),
	linear(0.09f),
	quadratic(0.032f)
{
}

void PointLight::setPosition(const glm::vec3& position)
{
	this->position = position;
}

void PointLight::setColor(const glm::vec3& color)
{
	this->color = color;
}

void PointLight::setAmbient(const glm::vec3& ambient)
{
	this->ambient = ambient;
}

void PointLight::setDiffuse(const glm::vec3& diffuse)
{
	this->diffuse = diffuse;
}

void PointLight::setSpecular(const glm::vec3& specular)
{
	this->specular = specular;
}

void PointLight::setAttenuation(float constant, float linear, float quadratic)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

glm::vec3 PointLight::getPosition()
{
	return position;
}

glm::vec3 PointLight::getColor()
{
	return color;
}

void PointLight::setUniforms(Shader* shader)
{
	shader->Bind();

	shader->SetUniforms1i("numPointLights", s_pointLightCount);

	shader->SetUniforms3f("pointLights[" + std::to_string(m_index) + "].position", position.x, position.y, position.z);
	shader->SetUniforms3f("pointLights[" + std::to_string(m_index) + "].color", color.x, color.y, color.z);

	shader->SetUniforms3f("pointLights[" + std::to_string(m_index) + "].ambient", ambient.x, ambient.y, ambient.z);
	shader->SetUniforms3f("pointLights[" + std::to_string(m_index) + "].diffuse", diffuse.x, diffuse.y, diffuse.z);
	shader->SetUniforms3f("pointLights[" + std::to_string(m_index) + "].specular", specular.x, specular.y, specular.z);

	shader->SetUniforms1f("pointLights[" + std::to_string(m_index) + "].constant", constant);
	shader->SetUniforms1f("pointLights[" + std::to_string(m_index) + "].linear", linear);
	shader->SetUniforms1f("pointLights[" + std::to_string(m_index) + "].quadratic", quadratic);

	shader->Unbind();

	ImGuiEngine::getImGuiEngine()->imGuiDrawPointLight(this, m_index);
}
