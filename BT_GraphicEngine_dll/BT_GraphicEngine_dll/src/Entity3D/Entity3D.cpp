#include "Entity3D.h"

Entity3D::Entity3D() : Entity()
{
	meshes = vector<Mesh*>();
	uniformAffectedLight = 0;

	affectedLight = true;
}

Entity3D::Entity3D(Renderer* renderer) : Entity(renderer)
{
	meshes = vector<Mesh*>();
	uniformAffectedLight = 0;

	affectedLight = true;
}

Entity3D::Entity3D(vector<Mesh*> meshes, Renderer* renderer) : Entity(renderer)
{
	this->meshes = meshes;
	uniformAffectedLight = 0;

	affectedLight = true;
}

Entity3D::~Entity3D()
{
}

void Entity3D::Init()
{
	SetUniforms();

	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Init();
	}
}

void Entity3D::Draw()
{
	if (IsCanDraw())
	{
		renderer->UseShader();
		renderer->BlendEnable();
		renderer->TextureEnable();
		UpdateShader();

		for (int i = 0; i < meshes.size(); i++)
		{
			meshes[i]->Draw();
		}

		renderer->TextureDisable();
		renderer->BlendDisable();
		renderer->CleanShader();

		Entity::DrawVolume();
	}
	else
	{
		//cout << "DONT DRAW: " << name << endl;
	}

	Entity::Draw();
}

void Entity3D::DeInit()
{
	for (int i = 0; i < meshes.size(); i++)
	{
		meshes[i]->DeInit();
	}

	Entity::DeInit();
}

void Entity3D::SetUniforms()
{
	Entity::SetUniforms();
	renderer->SetUniform(uniformAffectedLight, "affectedLight");
}

void Entity3D::UpdateShader()
{
	Entity::UpdateShader();
	renderer->UpdateStatus(uniformAffectedLight, affectedLight);
}

