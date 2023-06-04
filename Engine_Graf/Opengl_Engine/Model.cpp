#include "Model.h"

#include <Windows.h>
#include <glm/gtc/type_ptr.hpp>


Model::Model(const std::string& filePath, int initPositionX, int initPositionY, int initPositionZ, Shader* shader) :
	Entity3d(initPositionX, initPositionY, initPositionZ)
{
	this->shader = shader;
	loadModel(filePath);

	generateVertexBuffer();
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
	glm::mat4 nodeTransform = aiMatrix4x4ToGlm(node->mTransformation);
	localModel = glm::mat4(1.0f);

	// Multiply the node's transformation with the parent's transformation
	localModel *= nodeTransform;

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
	unsigned int vertexOffset = numVertices * 8;

	// Process vertices, normals, and texture coordinates
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		aiVector3D position = mesh->mVertices[i];
		aiVector3D normal = mesh->mNormals[i];
		aiVector3D texCoords;

		if (mesh->HasTextureCoords(0))
		{
			texCoords = mesh->mTextureCoords[0][i];
		}
		else
		{
			texCoords = aiVector3D(0.0f, 0.0f, 0.0f); // Si no hay coordenadas de textura, se asigna un valor por defecto
		}

		vertices.push_back(position.x);
		vertices.push_back(position.y);
		vertices.push_back(position.z);

		vertices.push_back(normal.x);
		vertices.push_back(normal.y);
		vertices.push_back(normal.z);

		vertices.push_back(texCoords.x);
		vertices.push_back(texCoords.y);
	}

	// Process indices
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices.push_back(face.mIndices[j] + vertexOffset);
		}
	}

	numVertices += mesh->mNumVertices;
	numIndices += mesh->mNumFaces * 3;
}

void Model::setVertices()
{

}

void Model::setIndixs()
{


}

void Model::setTexture(std::string imageName)
{
	texture = new Texture("res/textures/" + imageName);
	shader->Bind();

	shader->SetUniforms1i("u_Texture", 0);

	shader->Unbind();
}

void Model::generateVertexBuffer()
{
	vb = new VertexBuffer(vertices.data(), vertices.size() * sizeof(float));
	layout = VertexBufferLayout();
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	va = new VertexArray();
	va->AddBuffer(*vb, layout);

	ib = new IndexBuffer(indices.data(), indices.size());

	va->Unbind();
	vb->UnBind();
	ib->UnBind();
}


glm::mat4 Model::aiMatrix4x4ToGlm(const aiMatrix4x4& aiMatrix)
{
	glm::mat4 glmMatrix;
	glmMatrix[0][0] = aiMatrix.a1;
	glmMatrix[1][0] = aiMatrix.a2;
	glmMatrix[2][0] = aiMatrix.a3;
	glmMatrix[3][0] = aiMatrix.a4;
	glmMatrix[0][1] = aiMatrix.b1;
	glmMatrix[0][2] = aiMatrix.c1;
	glmMatrix[0][3] = aiMatrix.d1;
	glmMatrix[1][1] = aiMatrix.b2;
	glmMatrix[1][2] = aiMatrix.c2;
	glmMatrix[1][3] = aiMatrix.d2;
	glmMatrix[2][1] = aiMatrix.b3;
	glmMatrix[2][2] = aiMatrix.c3;
	glmMatrix[2][3] = aiMatrix.d3;
	glmMatrix[3][1] = aiMatrix.b4;
	glmMatrix[3][3] = aiMatrix.d4;
	glmMatrix[3][2] = aiMatrix.c4;

	//glmMatrix = glm::make_mat4(&aiMatrix.a1);

	return glmMatrix;
}

