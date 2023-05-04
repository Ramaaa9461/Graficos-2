#include "Cube.h"


DllExport Cube::Cube(int initPositionX, int initPositionY, int initPositionZ, Shader* shader) : Entity3d(initPositionX, initPositionY, initPositionZ)
{
	setVertices();
	setIndixs();
	calculateVertices();

	va = new VertexArray();
	vb = new VertexBuffer(positions, VERTEXPOSITIONSCOUNT * 6 * sizeof(float)); // El size: Cantidad de vertices * cantidad de floats por vertices

	layout = VertexBufferLayout();
	layout.Push<float>(3);
	layout.Push<float>(3);
	va->AddBuffer(*vb, layout);
	va->Bind();

	ib = new IndexBuffer(indices, INDEXSCOUNT);

	this->shader = shader;

	va->Unbind();
	vb->UnBind();
	ib->UnBind();
}

void Cube::setMaterial(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
{
	material = new Material(ambient, diffuse, specular, shininess);
}

void Cube::setMaterial(Material* material)
{
	this->material = material;
}

//DllExport void Cube::setColor(glm::vec4 RGBA)
//{
//	shader->Bind();
//	shader->SetUniforms4f("u_Color", RGBA.x, RGBA.y, RGBA.z, RGBA.w);
//	shader->Unbind();
//}

DllExport void Cube::setVertices()
{
	width = 1.0f;
	height = 1.0f;
	depth = 1.0f;

	float vertexs[] =
	{
		// Cara frontal
	   -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Vértice 0
		0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Vértice 1
		0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Vértice 2
	   -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,  // Vértice 3

	   // Cara trasera
		0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // Vértice 4
	   -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // Vértice 5
	   -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // Vértice 6
		0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,  // Vértice 7

	   // Cara superior
	   -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  // Vértice 8
		0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,  // Vértice 9
		0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  // Vértice 10
	   -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,  // Vértice 11

		// Cara inferior
		 0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f, // Vértice 12
		-0.5f, -0.5f,  0.5f,    0.0f, -1.0f,  0.0f, // Vértice 13
		-0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f, // Vértice 14
		 0.5f, -0.5f, -0.5f,    0.0f, -1.0f,  0.0f, // Vértice 15

		// Cara derecha
		 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // Vértice 16
		 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // Vértice 17
		 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f, // Vértice 18
		 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f, // Vértice 19

		// Cara izquierda
		-0.5f, -0.5f, -0.5f,   -1.0f,  0.0f,  0.0f, // Vértice 20
		-0.5f, -0.5f,  0.5f,   -1.0f,  0.0f,  0.0f, // Vértice 21
		-0.5f,  0.5f,  0.5f,   -1.0f,  0.0f,  0.0f, // Vértice 22
		-0.5f,  0.5f, -0.5f,   -1.0f,  0.0f,  0.0f  // Vértice 23

	};

	for (int i = 0; i < VERTEXPOSITIONSCOUNT; i++)
	{
		positions[i] = vertexs[i];
	}

}

DllExport void Cube::setIndixs()
{

	float indexs[] =
	{
		// Cara frontal
		0, 1, 2,
		2, 3, 0,

		// Cara trasera
		4, 5, 6,
		6, 7, 4,

		// Cara superior
		8, 9, 10,
		10, 11, 8,

		// Cara inferior
		12, 13, 14,
		14, 15, 12,

		// Cara derecha
		16, 17, 18,
		18, 19, 16,

		// Cara izquierda
		20, 21, 22,
		22, 23, 20
	};

	for (int i = 0; i < INDEXSCOUNT; i++)
	{
		indices[i] = indexs[i];
	}
}

DllExport void Cube::calculateVertices()
{
	float halfWidth = 0.5f * getScaleX() * width;
	float halfHeight = 0.5f * getScaleY() * height;
	float halfDepth = 0.5f * getScaleZ() * depth;

	// Front face
	vertices[0] = getPosition() + glm::vec3(-halfWidth, -halfHeight, halfDepth);
	vertices[1] = getPosition() + glm::vec3(halfWidth, -halfHeight, halfDepth);
	vertices[2] = getPosition() + glm::vec3(halfWidth, halfHeight, halfDepth);
	vertices[3] = getPosition() + glm::vec3(-halfWidth, halfHeight, halfDepth);

	// Back face
	vertices[4] = getPosition() + glm::vec3(halfWidth, -halfHeight, -halfDepth);
	vertices[5] = getPosition() + glm::vec3(-halfWidth, -halfHeight, -halfDepth);
	vertices[6] = getPosition() + glm::vec3(-halfWidth, halfHeight, -halfDepth);
	vertices[7] = getPosition() + glm::vec3(halfWidth, halfHeight, -halfDepth);
}






