#include "Entity3d.h"

#include "ImGuiEngine.h"



DllExport Entity3d::Entity3d(int initPositionX, int initPositionY, int initPositionZ) : Entity(initPositionX, initPositionY, initPositionZ)
{
	material = new Material();
}

DllExport Entity3d::~Entity3d()
{
	delete va;
	delete vb;
	delete ib;
	delete shader;
	delete texture;
	delete material;
}

DllExport glm::vec3* Entity3d::getVertices()
{
	return vertices;
}

static int i = 0;
DllExport void Entity3d::draw()
{
	ImGuiEngine::getImGuiEngine()->imGuiDrawObject(this, id);

	glm::mat4 mvp = renderer->proj * renderer->view * TRS;

	shader->Bind();
	
	shader->SetUniformsMat4f("u_MVP", mvp);
	shader->SetUniformsMat4f("model", TRS);
	material->SetUniforms(shader);

	renderer->Draw(va, ib, shader);
	
	shader->Unbind();

}
