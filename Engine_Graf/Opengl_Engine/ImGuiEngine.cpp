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


//void ImGuiEngine::imGuiDrawObject(Shape* shape[], int size)
//{
//	char result[100];
//
//	int a = 0;
//
//	const char* t_name = "Translation\0";
//	const char* r_name = "Rotation\0";
//	const char* s_name = "Scale\0";	
//	
//	char c_number;
//
//	const char* cc_number;	
//
//	for (int i = 0; i < size; i++)
//	{	
//		c_number = static_cast<char>(i);
//
//		//cc_number = &c_number;
//
//		traslation = shape[i]->getPosition();
//		rotation = shape[i]->getRotation();
//		scale = shape[i]->getScale();
//		
//
//		{
//			strcpy_s(result, t_name);
//			//strcat_s(result, &c_number);
//
//			ImGui::SliderFloat3(result, &traslation.x, 0.0f, 960.0f);
//			
//			strcpy_s(result, r_name);
//			//strcat_s(result, &c_number);
//
//			ImGui::SliderFloat3(result, &rotation.x, 0.0f, 360.0f);
//			
//			strcpy_s(result, s_name);
//			//strcat_s(result, &c_number);
//
//			ImGui::SliderFloat3(result, &scale.x, 0.0f, 10.0f);
//		}
//
//		shape[i]->setPosition(traslation);
//		shape[i]->setRotation(rotation);
//		shape[i]->setScale(scale);
//	}
//}