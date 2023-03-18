#include "TriangleShape.h"

DllExport TriangleShape::TriangleShape(glm::vec4 RGBA, int initPositionX, int initPositionY) : Shape(initPositionX, initPositionY)
{
	setVertices();
	setIndixs();

	va = new VertexArray();
	vb = new VertexBuffer(positions, 4 * 4 * sizeof(float));

	layout = VertexBufferLayout();
	layout.Push<float>(2);		 //Video: Buffer Layout Abstraction in OpenGL - min 27.30 Explica mas cosas qe se pueden hacer
	va->AddBuffer(*vb, layout);
	va->Bind();

	ib = new IndexBuffer(indices, 3);

	shaderType = ShaderType::noTexture;

	shader = new Shader(shaderType);
	shader->Bind();
	shader->SetUniforms4f("u_Color", RGBA.x, RGBA.y, RGBA.z, RGBA.w);

	//texture = new Texture("res/textures/Logo.jpg");
	//texture->Bind();
	//shader->SetUniforms1i("u_Texture", 0);


	va->Unbind();
	vb->UnBind();
	ib->UnBind();
	shader->Unbind();
}

DllExport void TriangleShape::setVertices()
{

	positions[0] = -50.0f;
	positions[1] = -50.0f;
	
	positions[2] = 50.0f;
	positions[3] = -50.0f;
	
	positions[4] = 0.0f;
	positions[5] = 50.0f;
	

}

DllExport void TriangleShape::setIndixs()
{

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;

}
