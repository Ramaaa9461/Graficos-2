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

private:

	DllExport void loadModel(const std::string& filePath);
	DllExport void processNode(aiNode* node, const aiScene* scene);
	DllExport void processMesh(aiMesh* mesh, const aiScene* scene);

	std::string directory;
	float* vertices;

	unsigned int* indices;
	unsigned int numVertices;
	unsigned int numIndices;

	DllExport void  setVertices() override;
	DllExport void  setIndixs()   override; 
};


