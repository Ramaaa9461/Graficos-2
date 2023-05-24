#pragma once

#include "DDLExport.h"

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <assimp/mesh.h>

class Model
{

public:
	DllExport Model(const std::string& filePath);
	DllExport void draw();

private:

	DllExport void loadModel(const std::string& filePath);
	DllExport void processNode(aiNode* node, const aiScene* scene);
	DllExport void processMesh(aiMesh* mesh, const aiScene* scene);

private:
	struct Vertex {
		float position[3];
		float normal[3];
	};

	std::string directory;
	Vertex* vertices;

	unsigned int* indices;
	unsigned int numVertices;
	unsigned int numIndices;

	// Define any additional member variables and helper functions you may need
};


