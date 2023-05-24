#include "Model.h"

Model::Model(const std::string& filePath)
{
	loadModel(filePath);
}

void Model::draw()
{
	// Render the model here using OpenGL
}

void Model::loadModel(const std::string& filePath) 
{
	Assimp::Importer* importer{};

	const aiScene* scene = importer->ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		// Error handling if the model loading fails
		return;
	}

	directory = filePath.substr(0, filePath.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// Process the node's meshes
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}

	// Recursively process the node's children
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		processNode(node->mChildren[i], scene);
	}
}

void Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	numVertices = mesh->mNumVertices;
	numIndices = 0;

	// Process vertices
	vertices = new Vertex[numVertices];
	for (unsigned int i = 0; i < numVertices; ++i) 
	{
		Vertex& vertex = vertices[i];
		aiVector3D position = mesh->mVertices[i];
		aiVector3D normal = mesh->mNormals[i];

		vertex.position[0] = position.x;
		vertex.position[1] = position.y;
		vertex.position[2] = position.z;

		vertex.normal[0] = normal.x;
		vertex.normal[1] = normal.y;
		vertex.normal[2] = normal.z;
	}

	// Process indices
	numIndices = mesh->mNumFaces * 3;
	indices = new unsigned int[numIndices];
	unsigned int index = 0;
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices[index++] = face.mIndices[j];
		}
	}
}