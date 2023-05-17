#include "SpotLight.h"


int SpotLight::s_spotLightCount = 0; // Inicializamos el contador de luces puntuales en 0

SpotLight::SpotLight()
	: m_index(s_spotLightCount++),
	position(glm::vec3(0.0f)),
	direction(glm::vec3(0.0f, -1.0f, 0.0f)),
	color(glm::vec3(1.0f)),
	ambient(glm::vec3(0.1f)),
	diffuse(glm::vec3(1.0f)),
	specular(glm::vec3(1.0f)),
	constant(1.0f),
	linear(0.09f),
	quadratic(0.032f),
	cutoff(0.0f),
	outerCutoff(0.0f)
{
}

SpotLight::~SpotLight()
{
}

SpotLight::SpotLight(const glm::vec3& position, const glm::vec3& direction, const glm::vec3& color,
	const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular,
	float constant, float linear, float quadratic, float cutoff, float outerCutoff)
	: m_index(s_spotLightCount++),
	position(position),
	direction(direction),
	color(color),
	ambient(ambient),
	diffuse(diffuse),
	specular(specular),
	constant(constant),
	linear(linear),
	quadratic(quadratic),
	cutoff(cutoff),
	outerCutoff(outerCutoff)
{
}

void SpotLight::setPosition(const glm::vec3& position)
{
	this->position = position;
}

void SpotLight::setDirection(const glm::vec3& direction)
{
	this->direction = direction;
}

void SpotLight::setColor(const glm::vec3& color)
{
	this->color = color;
}

void SpotLight::setAmbient(const glm::vec3& ambient)
{
	this->ambient = ambient;
}

void SpotLight::setDiffuse(const glm::vec3& diffuse)
{
	this->diffuse = diffuse;
}

void SpotLight::setSpecular(const glm::vec3& specular)
{
	this->specular = specular;
}

void SpotLight::setAttenuation(float constant, float linear, float quadratic)
{
	this->constant = constant;
	this->linear = linear;
	this->quadratic = quadratic;
}

void SpotLight::setCutoff(float cutoff)
{
	this->cutoff = cutoff;
}

void SpotLight::setOuterCutoff(float outerCutoff)
{
	this->outerCutoff = outerCutoff;
}

void SpotLight::setUniforms(Shader* shader)
{
	shader->Bind();

	shader->SetUniforms3f("spotLights[" + std::to_string(m_index) + "].position", position.x, position.y, position.z);
	shader->SetUniforms3f("spotLights[" + std::to_string(m_index) + "].direction", direction.x, direction.y, direction.z);
	shader->SetUniforms3f("spotLights[" + std::to_string(m_index) + "].color", color.x, color.y, color.z);
	shader->SetUniforms3f("spotLights[" + std::to_string(m_index) + "].ambient", ambient.x, ambient.y, ambient.z);
	shader->SetUniforms3f("spotLights[" + std::to_string(m_index) + "].diffuse", diffuse.x, diffuse.y, diffuse.z);
	shader->SetUniforms3f("spotLights[" + std::to_string(m_index) + "].specular", specular.x, specular.y, specular.z);

	shader->SetUniforms1f("spotLights[" + std::to_string(m_index) + "].constant", constant);
	shader->SetUniforms1f("spotLights[" + std::to_string(m_index) + "].linear", linear);
	shader->SetUniforms1f("spotLights[" + std::to_string(m_index) + "].quadratic", quadratic);
	shader->SetUniforms1f("spotLights[" + std::to_string(m_index) + "].cutoff", cutoff);
	shader->SetUniforms1f("spotLights[" + std::to_string(m_index) + "].outerCutoff", outerCutoff);

	shader->Unbind();
}