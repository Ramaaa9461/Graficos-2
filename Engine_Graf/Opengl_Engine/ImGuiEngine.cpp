#include "ImGuiEngine.h"

#include "Window.h"

ImGuiEngine* ImGuiEngine::S_ImGuiEngine = nullptr;

DllExport ImGuiEngine::ImGuiEngine()
{
	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(Window::getWindow()->getNativeWindow(), true);
	ImGui::StyleColorsDark();
}

DllExport ImGuiEngine* ImGuiEngine::getImGuiEngine()
{
	if (S_ImGuiEngine == nullptr)
	{
		S_ImGuiEngine = new ImGuiEngine();
	}
	return S_ImGuiEngine;
}

DllExport ImGuiEngine::~ImGuiEngine()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();
}

DllExport void ImGuiEngine::imGuiStartDraw()
{
	ImGui_ImplGlfwGL3_NewFrame();
}

DllExport void ImGuiEngine::imGuiEndDraw()
{
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

DllExport void ImGuiEngine::imGuiDrawObject(Entity2d* entity2d, int index)
{
	traslation = entity2d->getPosition();
	rotation = entity2d->getRotation();
	scale = entity2d->getScale();

	if (ImGui::CollapsingHeader(("Entity" + std::to_string(index)).c_str()))
	{
		ImGui::DragFloat3(("Translation " + std::to_string(index)).c_str(), &traslation.x, 0.0f, 960.0f);
		ImGui::DragFloat (("Rotation " + std::to_string(index)).c_str(), &rotation.z, 1.0f, 0.0f, 360.0f);
		ImGui::DragFloat2(("Scale " + std::to_string(index)).c_str(), &scale.x, 0.1f, 0.0f, 10.0f);

	}

	entity2d->setPosition(traslation);
	entity2d->setRotation(rotation);
	entity2d->setScale(scale);
}

void ImGuiEngine::imGuiDrawObject(Entity3d* entity3d, int index)
{
	traslation = entity3d->getPosition();
	rotation = entity3d->getRotation();
	scale = entity3d->getScale();

	if (ImGui::CollapsingHeader(("Entity " + std::to_string(index)).c_str()))
	{
		ImGui::DragFloat3(("Translation " + std::to_string(index)).c_str(), &traslation.x, 0.1f);
		ImGui::DragFloat3(("Rotation " + std::to_string(index)).c_str(), &rotation.x, 1.0f);
		ImGui::DragFloat3(("Scale " + std::to_string(index)).c_str(), &scale.x, 0.1f);

	}

	entity3d->setPosition(traslation);
	entity3d->setRotation(rotation);
	entity3d->setScale(scale);
}

void ImGuiEngine::imGuiDrawDirectionalLight(DirectionalLight* directionalLight, int index)
{
	glm::vec3 direction = directionalLight->getDirection();
	glm::vec3 color = directionalLight->getColor();

	if (ImGui::CollapsingHeader(("Directional Light " + std::to_string(index)).c_str()))
	{
		ImGui::DragFloat3(("Direction " + std::to_string(index)).c_str(), &direction.x, 0.01f, -1.0f, 1.0f);
		ImGui::ColorPicker3(("Color " + std::to_string(index)).c_str(), &color.x, 0.1f);
	}

	directionalLight->setDirection(direction);
	directionalLight->setColor(color);
}

void ImGuiEngine::imGuiDrawPointLight(PointLight* pointLight, int index)
{
	glm::vec3 position = pointLight->getPosition();
	glm::vec3 color = pointLight->getColor();

	if (ImGui::CollapsingHeader(("Point Light " + std::to_string(index)).c_str()))
	{
		ImGui::DragFloat3(("Position " + std::to_string(index)).c_str(), &position.x, 0.1f);
		ImGui::ColorPicker3(("Color " + std::to_string(index)).c_str(), &color.x, 0.1f);
	}

	pointLight->setPosition(position);
	pointLight->setColor(color);
}


void ImGuiEngine::imGuiDrawSpotLight(SpotLight* spotLight, int index)
{
	glm::vec3 position = spotLight->getPosition();
	glm::vec3 direction = spotLight->getDirection();
	glm::vec3 color = spotLight->getColor();

	float cutoff = spotLight->getCutoff(); 
	float outerCutoff = spotLight->getOuterCutoff();


	if (ImGui::CollapsingHeader(("Spot Light " + std::to_string(index)).c_str()))
	{
		ImGui::DragFloat3(("Position " + std::to_string(index)).c_str(), &position.x, 0.1f);
		ImGui::DragFloat3(("Direction " + std::to_string(index)).c_str(), &direction.x, 0.01f, -1.0f, 1.0f);
		ImGui::ColorPicker3(("Color " + std::to_string(index)).c_str(), &color.x, 0.1f);
		
		ImGui::DragFloat(("Cut Off " + std::to_string(index)).c_str(), &cutoff);
		ImGui::DragFloat(("Outer Cut Off " + std::to_string(index)).c_str(), &outerCutoff);
	}

	spotLight->setPosition(position);
	spotLight->setDirection(direction);
	spotLight->setColor(color);
	spotLight->setCutoff(cutoff);
	spotLight->setOuterCutoff(outerCutoff);
}


