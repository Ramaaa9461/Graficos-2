#pragma once

#include "DDLExport.h"
#include "Entity3d.h"

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <assimp/mesh.h>

class Model : public Entity3d
{

public:
	DllExport Model(const std::string& filePath, int initPositionX, int initPositionY, int initPositionZ, Shader* shader);
	DllExport void setTexture(std::string imageName);
	

private:

	DllExport void loadModel(const std::string& filePath);
	DllExport void processNode(aiNode* node, const aiScene* scene);
	DllExport void processMesh(aiMesh* mesh, const aiScene* scene);
	DllExport void generateVertexBuffer();
	DllExport glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& aiMatrix);
	

	std::vector<float> vertices;
	std::vector<unsigned int> indices;
	unsigned int numVertices = 0;
	unsigned int numIndices = 0;

	std::string directory;

	DllExport void  setVertices() override;
	DllExport void  setIndixs()   override; 
};


