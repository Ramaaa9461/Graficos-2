#include "Model.h"

#include <Windows.h>
#include <glm/gtc/type_ptr.hpp>


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

	glm::mat4 identity(1.0f);
	ProcessNode(scene->mRootNode, scene, identity);
	
	generateVertexBuffer();
}

void Model::ProcessNode(aiNode* node, const aiScene* scene, const glm::mat4& parentTransform)
{
	glm::mat4 currentTransform = parentTransform * aiMatrix4x4ToGlm(node->mTransformation);
	/*/Seguro falta algo aca*/

	// Process the node's meshes
	for (unsigned int i = 0; i < node->mNumMeshes; ++i)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		ProcessMesh(mesh, scene, currentTransform);
	}

	// Recursively process the node's children
	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene, currentTransform);
	}
}

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene, const glm::mat4& transform)
{
	for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
		Vertex vertex;
		glm::vec3 vector;

		// Positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.position = glm::vec3(transform * glm::vec4(vector, 1.0f));

		// Normals
		if (mesh->HasNormals()) 
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.normal = glm::normalize(glm::mat3(transform) * vector);
		}

		// Texture coordinates
		if (mesh->HasTextureCoords(0)) {
			vertex.texCoords.x = mesh->mTextureCoords[0][i].x;
			vertex.texCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else 
		{
			vertex.texCoords = glm::vec2(0.0f, 0.0f); // Si no hay coordenadas de textura, asigna valores predeterminados
		}

		m_Vertices.push_back(vertex);
	}

	unsigned int baseIndex = m_Vertices.size() - mesh->mNumVertices;
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			m_Indices.push_back(baseIndex + face.mIndices[j]);
		}
	}
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
	std::vector<float> flattenedVertices = FlattenVertices();

	vb = new VertexBuffer(flattenedVertices.data(), flattenedVertices.size() * sizeof(float));
	layout = VertexBufferLayout();
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	va = new VertexArray();
	va->AddBuffer(*vb, layout);

	ib = new IndexBuffer(m_Indices.data(), m_Indices.size());

	va->Unbind();
	vb->UnBind();
	ib->UnBind();
}

std::vector<float> Model::FlattenVertices()
{
	std::vector<float> flattenedVertices;
	flattenedVertices.reserve(m_Vertices.size() * 8); // 8 components per vertex (3 for position, 3 for normal, 2 for texCoords)

	for (const Vertex& vertex : m_Vertices) 
	{
		flattenedVertices.push_back(vertex.position.x);
		flattenedVertices.push_back(vertex.position.y);
		flattenedVertices.push_back(vertex.position.z);

		flattenedVertices.push_back(vertex.normal.x);
		flattenedVertices.push_back(vertex.normal.y);
		flattenedVertices.push_back(vertex.normal.z);

		flattenedVertices.push_back(vertex.texCoords.x);
		flattenedVertices.push_back(vertex.texCoords.y);
	}

	return flattenedVertices;
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

	return glmMatrix;
}

