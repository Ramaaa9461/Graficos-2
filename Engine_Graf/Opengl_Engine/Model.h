#pragma once

#include "DDLExport.h"
#include "Entity3d.h"

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <assimp/mesh.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
};


class Model : public Entity3d
{

public:
	DllExport Model(const std::string& filePath, int initPositionX, int initPositionY, int initPositionZ, Shader* shader);
	DllExport void setTexture(std::string imageName);
	

private:

	DllExport void loadModel(const std::string& filePath);

	DllExport void ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& parentTransform);
	DllExport void ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform);

	DllExport void generateVertexBuffer();
	DllExport std::vector<float> FlattenVertices();
		DllExport glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& aiMatrix);
	
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;

	DllExport void  setVertices() override;
	DllExport void  setIndixs()   override; 
};


