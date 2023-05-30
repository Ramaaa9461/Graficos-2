#include "Model.h"

#include <Windows.h>

Model::Model(const std::string& filePath, int initPositionX, int initPositionY, int initPositionZ, Shader* shader) :
	Entity3d(initPositionX, initPositionY, initPositionZ)
{
	this->shader = shader;
	loadModel(filePath);
}


void Model::loadModel(const std::string& filePath) 
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::string errorString = "Error loading model: ";
		if (!scene)
		{
			errorString += importer.GetErrorString();
		}
		else
		{
			if (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
			{
				errorString += "Incomplete scene. Some data is missing.";
			}
			else if (!scene->mRootNode)
			{
				errorString += "Root node is null.";
			}
		}

		std::cout << errorString;
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

	// Process vertices and normals
	vertices = new float[numVertices * 6];  // 6 floats per vertex (3 for position, 3 for normal)
	for (unsigned int i = 0; i < numVertices; ++i)
	{
		unsigned int vertexOffset = i * 6;
		aiVector3D position = mesh->mVertices[i];
		aiVector3D normal = mesh->mNormals[i];

		vertices[vertexOffset] = position.x;
		vertices[vertexOffset + 1] = position.y;
		vertices[vertexOffset + 2] = position.z;

		vertices[vertexOffset + 3] = normal.x;
		vertices[vertexOffset + 4] = normal.y;
		vertices[vertexOffset + 5] = normal.z;
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

	// Process indices
	numIndices = mesh->mNumFaces * 3;
	indices = new unsigned int[numIndices];
	index = 0;
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices[index++] = face.mIndices[j];
		}
	}
	setVertices();
	setIndixs();

	va = new VertexArray();
	vb = new VertexBuffer(vertices, numVertices * 6 * sizeof(float)); // El size: Cantidad de vertices * cantidad de floats por vertices

	layout = VertexBufferLayout();
	layout.Push<float>(3);
	layout.Push<float>(3);
	va->AddBuffer(*vb, layout);
	va->Bind();

	ib = new IndexBuffer(indices, numIndices);

	va->Unbind();
	vb->UnBind();
	ib->UnBind();
}

void Model::setVertices()
{

}

void Model::setIndixs()
{


}



