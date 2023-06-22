#pragma once

#include "entity.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "TextureImporter.h"
#include "ShaderType.h"
#include "Material.h"

class Entity3d : public Entity
{

protected:

	glm::mat4 localModel = glm::mat4(1);

	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout layout;
	IndexBuffer* ib;
	Shader* shader;
	TextureImporter* texture;

	Material* material;
	

	ShaderType shaderType;

	DllExport virtual void  setVertices() = 0;
	DllExport virtual void  setIndixs() = 0;

public:

	DllExport  Entity3d(int initPositionX, int initPositionY, int initPositionZ);
	DllExport ~Entity3d();

	DllExport void draw();
};

