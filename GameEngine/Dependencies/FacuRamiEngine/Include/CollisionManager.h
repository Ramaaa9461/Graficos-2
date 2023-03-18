#pragma once

#include "glm/glm.hpp"
#include "DDLExport.h"

static class CollisionManager
{

private:

public:


	DllExport static bool IntersectPolygons(glm::vec3 verticesA[], int sizeA, glm::vec3 verticesB[], int sizeB, glm::vec3& normal, float& depth);
	DllExport static void ProjectVertices(glm::vec3 vertices[], int size, glm::vec3 axis, float& min, float& max);
	DllExport static glm::vec3 FindArithmeticMean(glm::vec3 vertices[], int size);


};

