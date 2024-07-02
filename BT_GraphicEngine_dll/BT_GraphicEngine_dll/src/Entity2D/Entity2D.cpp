#include "Entity2D.h"

Entity2D::Entity2D() : Entity()
{
	color = Color();
	material = nullptr;

	uniformColor = 0;
	uniformAlpha = 0;
	uniformAffectedLight = 0;
	uniformUseTexture = 0;

	vertexs = vector<Vertex>();
	indexes = vector<unsigned int>();

	VAO = 0;
	VBO = 0;
	EBO = 0;

	hasCollider = false;
	moveable = false;

	affectedLight = true;
	useTexture = false;

}

Entity2D::Entity2D(Renderer* renderer) : Entity(renderer)
{
	color = Color();
	material = nullptr;

	uniformColor = 0;
	uniformAlpha = 0;
	uniformAffectedLight = 0;
	uniformUseTexture = 0;

	vertexs = vector<Vertex>();
	indexes = vector<unsigned int>();

	VAO = 0;
	VBO = 0;
	EBO = 0;

	hasCollider = false;
	moveable = false;

	affectedLight = true;
	useTexture = false;
}

Entity2D::~Entity2D()
{
}

void Entity2D::Draw()
{
	renderer->Draw(VAO, indexes.size());
}

void Entity2D::DeInit()
{
	vertexs.clear();
	indexes.clear();
	Entity::DeInit();
}

void Entity2D::SetCollider(bool hasCollider)
{
	this->hasCollider = hasCollider;
}

void Entity2D::SetMoveable(bool moveable)
{
	this->moveable = moveable;
}

void Entity2D::SetAffectedLight(bool affectedLight)
{
	this->affectedLight = affectedLight;
}

bool Entity2D::IsMoveable()
{
	return moveable;
}

bool Entity2D::HasCollider()
{
	return hasCollider;
}

bool Entity2D::IsAffectedLight()
{
	return affectedLight;
}

void Entity2D::SetUniforms()
{
	Entity::SetUniforms();
	renderer->SetUniform(uniformColor, "color");
	renderer->SetUniform(uniformAlpha, "a");
	renderer->SetUniform(uniformAffectedLight, "affectedLight");
	renderer->SetUniform(uniformUseTexture, "useTexture");
}

void Entity2D::UpdateShader()
{
	Entity::UpdateShader();
	renderer->UpdateColor(uniformColor, uniformAlpha, color.GetColorRGBA());
	renderer->UpdateStatus(uniformAffectedLight, affectedLight);
	renderer->UpdateStatus(uniformUseTexture, useTexture);

	if (material != nullptr)
	{
		material->UpdateShader();
	}
}
