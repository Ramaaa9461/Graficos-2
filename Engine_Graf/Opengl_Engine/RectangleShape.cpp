#include "RectangleShape.h"

DllExport RectangleShape::RectangleShape(int initPositionX, int initPositionY) : Shape(initPositionX, initPositionY)
{
	setVertices();
	setIndixs();
	calculateVertices();

	va = new VertexArray();
	vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));

	layout = VertexBufferLayout();
	layout.Push<float>(2);		 //Video: Buffer Layout Abstraction in OpenGL - min 27.30 Explica mas cosas qe se pueden hacer
	va->AddBuffer(*vb, layout);
	va->Bind();

	ib = new IndexBuffer(indices, 6);

	shaderType = ShaderType::noTexture;

	shader = new Shader(shaderType);
	shader->Bind();
	shader->SetUniforms4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

	va->Unbind();
	vb->UnBind();
	ib->UnBind();
	shader->Unbind();
}

DllExport void RectangleShape::setColor(glm::vec4 RGBA)
{
	shader->Bind();
	shader->SetUniforms4f("u_Color", RGBA.x, RGBA.y, RGBA.z, RGBA.w);
	shader->Unbind();
}

DllExport void RectangleShape::setVertices()
{
	width = 100;
	height = 100;

	positions[0] = -50.0f;
	positions[1] = -50.0f;

	positions[2] = 50.0f;
	positions[3] = -50.0f;

	positions[4] = 50.0f;
	positions[5] = 50.0f;

	positions[6] = -50.0f;
	positions[7] = 50.0f;

}

DllExport void RectangleShape::setIndixs()
{
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
}

DllExport void RectangleShape::calculateVertices()
{
	//glm::vec3 scale = getScale();
	//glm::vec3 rotation = getRotation();
	//int scaleX = scale.x;
	//int scaleY = scale.y;
	//int rotZ   = rotation.z;

	vertices[0] = getPosition() + (-glm::vec3(1.0f * getScaleX() * width / 2, 0.0f, 0.0f)) + (glm::vec3(0.0f, 1.0f  * getScaleY() * height / 2, 0.0f));
	vertices[1] = getPosition() + (glm::vec3(1.0f  * getScaleX() * width / 2, 0.0f, 0.0f)) + (glm::vec3(0.0f, 1.0f  * getScaleY() * height / 2, 0.0f));
	vertices[2] = getPosition() + (glm::vec3(1.0f  * getScaleX() * width / 2, 0.0f, 0.0f)) + (-glm::vec3(0.0f, 1.0f * getScaleY() * height / 2, 0.0f));
	vertices[3] = getPosition() + (-glm::vec3(1.0f * getScaleX() * width / 2, 0.0f, 0.0f)) + (-glm::vec3(0.0f, 1.0f * getScaleY() * height / 2, 0.0f));
}

