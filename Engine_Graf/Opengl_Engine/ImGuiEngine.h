#pragma once

#include "glm/glm.hpp"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw_gl3.h"

#include "Entity2d.h"
#include "Entity3d.h"

#include "SpotLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class ImGuiEngine
{
private:

	glm::vec3 traslation;
	glm::vec3 rotation;
	glm::vec3 scale;

	static int objectNumber;

	static ImGuiEngine* S_ImGuiEngine;
	DllExport ImGuiEngine();

public:

	DllExport static ImGuiEngine* getImGuiEngine();

	DllExport ~ImGuiEngine();
	
	DllExport void imGuiStartDraw();
	DllExport void imGuiEndDraw();
	
	DllExport void imGuiDrawObject(Entity2d* entity2d, int index);
	DllExport void imGuiDrawObject(Entity3d* entity3d, int index);

	DllExport void imGuiDrawSpotLight(SpotLight* spotLight, int index);
	DllExport void imGuiDrawDirectionalLight(DirectionalLight* directionalLight, int index);
	DllExport void imGuiDrawPointLight(PointLight* pointLight, int index);
};

