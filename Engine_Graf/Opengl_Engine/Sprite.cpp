#include "Sprite.h"

Sprite::Sprite(std::string imageName, int initPositionX, int initPositionY) : Entity2d(initPositionX, initPositionY)
{
	setVertices();
	setIndixs();

	va = new VertexArray();
	vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));

	layout = VertexBufferLayout();
	layout.Push<float>(2);		 //Video: Buffer Layout Abstraction in OpenGL - min 27.30 Explica mas cosas qe se pueden hacer
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);
	va->Bind();

	ib = new IndexBuffer(indices, 6);

	shaderType = ShaderType::whithTexture;

	shader = new Shader(shaderType);
	shader->Bind();

	texture = new TextureImporter("res/textures/" + imageName);
	texture->Bind();
	shader->SetUniforms1i("u_Texture", 0);

	va->Unbind();
	vb->UnBind();
	ib->UnBind();
	shader->Unbind();

	textura = texture;
}

Sprite::Sprite() : Entity2d(0, 0)
{
	setVertices();
	setIndixs();

	va = new VertexArray();
	vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));

	layout = VertexBufferLayout();
	layout.Push<float>(2);		 //Video: Buffer Layout Abstraction in OpenGL - min 27.30 Explica mas cosas qe se pueden hacer
	layout.Push<float>(2);
	va->AddBuffer(*vb, layout);
	va->Bind();

	ib = new IndexBuffer(indices, 6);

	shaderType = ShaderType::whithTexture;

	shader = new Shader(shaderType);

	shader->Unbind();
	va->Unbind();
	vb->UnBind();
	ib->UnBind();

}

Sprite::~Sprite()
{
}

void Sprite::setTexture(std::string imageName)
{
	texture = new TextureImporter("res/textures/" + imageName);

	texture->Bind(0);
	shader->Bind();
	shader->SetUniforms1i("u_Texture", 0);

	shader->Unbind();
}

void Sprite::setVertices()
{
	width = 100;
	height = 100;

	positions[0] = -50.0f;
	positions[1] = -50.0f;
	positions[5] = -50.0f;
	positions[4] = 50.0f;
	positions[8] = 50.0f;
	positions[9] = 50.0f;
	positions[12] = -50.0f;
	positions[13] = 50.0f;

	positions[2] = 0.0f;
	positions[3] = 0.0f;
	positions[6] = 1.0f;
	positions[7] = 0.0f;
	positions[10] = 1.0f;
	positions[11] = 1.0f;
	positions[14] = 0.0f;
	positions[15] = 1.0f;

}

void Sprite::setVerticesSpriteSheet()
{
	//Crear animaciones y 
	positions[0] = -50.0f;
	positions[1] = -50.0f;
	positions[5] = -50.0f;
	positions[4] = 50.0f;
	positions[8] = 50.0f;
	positions[9] = 50.0f;
	positions[12] = -50.0f;
	positions[13] = 50.0f;

	positions[2] = 0.0f;
	positions[3] = 0.0f;
	positions[6] = 1.0f;
	positions[7] = 0.0f;
	positions[10] = 1.0f;
	positions[11] = 1.0f;
	positions[14] = 0.0f;
	positions[15] = 1.0f;

}

void Sprite::setIndixs()
{
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 2;
	indices[4] = 3;
	indices[5] = 0;
}

void Sprite::calculateVertices()
{

	int scaleX = getScaleX();
	int scaleY = getScaleY();

	vertices[0] = getPosition() + (-glm::vec3(1.0f * scaleX * width / 2, 0.0f, 0.0f)) + (glm::vec3(0.0f, 1.0f * scaleY * height / 2, 0.0f));
	vertices[1] = getPosition() + (glm::vec3(1.0f * scaleX * width / 2, 0.0f, 0.0f)) + (glm::vec3(0.0f, 1.0f * scaleY * height / 2, 0.0f));
	vertices[2] = getPosition() + (glm::vec3(1.0f * scaleX * width / 2, 0.0f, 0.0f)) + (-glm::vec3(0.0f, 1.0f * scaleY * height / 2, 0.0f));
	vertices[3] = getPosition() + (-glm::vec3(1.0f * scaleX * width / 2, 0.0f, 0.0f)) + (-glm::vec3(0.0f, 1.0f * scaleY * height / 2, 0.0f));

}

DllExport void Sprite::drawTexture()
{
	textura->Bind();
	draw();
	textura->UnBind();
}


