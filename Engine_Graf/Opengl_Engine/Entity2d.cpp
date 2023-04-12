#include "Entity2d.h"

#include "ImGuiEngine.h"


DllExport Entity2d::Entity2d(int initPositionX, int initPositionY) : Entity(initPositionX, initPositionY, 0)
{
}

DllExport Entity2d::~Entity2d()
{
	delete va;
	delete vb;
	delete ib;
	delete shader;
	delete texture;
}

DllExport glm::vec3* Entity2d::getVertices()
{
	return vertices;
}

DllExport void Entity2d::draw()
{
	ImGuiEngine::getImGuiEngine()->imGuiDrawObject(this, id);

	glm::mat4 mvp = renderer->proj * renderer->view * TRS;

	shader->Bind();
	shader->SetUniformsMat4f("u_MVP", mvp);

	renderer->Draw(va, ib, shader); 
}
