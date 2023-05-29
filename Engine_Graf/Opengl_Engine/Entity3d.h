#pragma once

#include "entity.h"

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "Shader.h"
#include "Texture.h"
#include "ShaderType.h"
#include "Material.h"

class Entity3d : public Entity
{

protected:

	VertexArray* va;
	VertexBuffer* vb;
	VertexBufferLayout layout;
	IndexBuffer* ib;
	Shader* shader;
	Texture* texture;

	Material* material;
	

	ShaderType shaderType;

	DllExport virtual void  setVertices() = 0;
	DllExport virtual void  setIndixs() = 0;

public:

	DllExport  Entity3d(int initPositionX, int initPositionY, int initPositionZ);
	DllExport ~Entity3d();

	DllExport void draw();
};

