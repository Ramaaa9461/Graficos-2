#include "CollisionManager.h"

DllExport void CollisionManager::ProjectVertices(glm::vec3 vertices[], int size, glm::vec3 axis, float& min, float& max)
{
	min =  3.40282347E+38;
	max = -3.40282347E+38;

	for (int i = 0; i < size; i++)
	{
		glm::vec3 v = vertices[i];
		float projection = glm::dot(v, axis);

		if (projection < min) { min = projection; }
		if (projection > max) { max = projection; }
	}
}


DllExport bool CollisionManager::IntersectPolygons(glm::vec3 verticesA[], int sizeA, glm::vec3 verticesB[], int sizeB, glm::vec3& normal , float& depth)
{
	normal = glm::vec3(0, 0, 0);
	depth = 3.40282347E+38;
	float minA, maxA;
	float minB, maxB;

	// Busco entre todos los vertices de A para generar una proyeccion y ver si hay una separacion
	for (int i = 0; i < sizeA; i++)
	{
		glm::vec3 va = verticesA[i];
		glm::vec3 vb = verticesA[(i + 1) % sizeA]; // Asi me aseguro que no me estoy pasando de la capacidad del array y vuelvo al principio

		glm::vec3 edge = vb - va;
		glm::vec3 axis = glm::vec3(-edge.y, edge.x, 0.0f);

		ProjectVertices(verticesA, sizeA, axis, minA, maxA);
		ProjectVertices(verticesB, sizeB, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA) // Se busca si existe un hueco en esta proyeccion, si existe directamente se devuelve que no hay colision
		{
			return false;
		}

		float axisDepth = glm::min(maxB - minA, maxA - minB); // Aca se calcula cual es el menor valor para saber que tan profunda fue la interseccion

		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}

	
	}

	// Lo mismo que con los vertices A pero con los vertices B
	for (int i = 0; i < sizeB; i++)
	{
		glm::vec3 va = verticesB[i];
		glm::vec3 vb = verticesB[(i + 1) % sizeB];

		glm::vec3 edge = vb - va;
		glm::vec3 axis = glm::vec3(-edge.y, edge.x, 0.0f);

		ProjectVertices(verticesA, sizeA, axis, minA, maxA);
		ProjectVertices(verticesB, sizeB, axis, minB, maxB);

		if (minA >= maxB || minB >= maxA)
		{
			return false;
		}

		float axisDepth = glm::min(maxB - minA, maxA - minB);

		if (axisDepth < depth)
		{
			depth = axisDepth;
			normal = axis;
		}
	}

	depth /= glm::length(normal); // Divido la profundidad de la interseccion por la magnitud de la normal para conseguir la profundidad real

	glm::normalize(normal);

	depth /= glm::length(normal);

	// busco los centro de ambos poligonos para encontrar la direccion
	glm::vec3  centerA = FindArithmeticMean(verticesA, sizeA);
	glm::vec3  centerB = FindArithmeticMean(verticesB, sizeB);

	glm::vec3  direction = centerB - centerA;

	// corroboro que la direccion y la normal estan alineadas, si no lo estan invierto la normal
	// Esto es para poder "re-ubicar" de forma correcta los poligonos que interseccionan
	if (glm::dot(direction, normal) < 0)
	{
		normal = -normal;
	}

	return true;

}

DllExport glm::vec3 CollisionManager::FindArithmeticMean(glm::vec3 vertices[], int size)
{
	float sumX = 0;
	float sumY = 0;

	for (int i = 0; i < size; i++)
	{
		sumX += vertices[i].x;
		sumY += vertices[i].y;
	}

	return glm::vec3(sumX / (float)size, sumY / (float)size, 0.0f);
}

