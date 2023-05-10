#pragma once
#include <string>
#include <unordered_map>

#include "glm/glm.hpp"

#include "ShaderType.h"

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};


class Shader
{
private:

	//std::string m_FilepPath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;

#pragma region Shaders

	std::string vertexShader =
		//"#shader vertex                                \n"
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;"
		"\n"
		"layout(location = 1) in vec3 normal;"
		"\n"
		"out vec3 v_Normal;					\n"
		"out vec4 FragPos;					\n"
		"uniform mat4 projection;			\n"
		"uniform mat4 view;					\n"
		"uniform mat4 model;				\n"
		"void main()						\n"
		"{\n"
		"    FragPos = model * position;\n"
		"    v_Normal = normal;\n"
		"    gl_Position = projection * view * model * position;\n"
		"};\n";

	//std::string fragmentShaderNoTexture =
	//	"#version 330 core\n"
	//	"\n"
	//	"    layout(location = 0) out vec4 color;"
	//	"\n"
	//	"    in vec4 FragPos;               \n"
	//	"    in vec4 v_Normal;              \n"
	//	"struct Material {					\n"
	//	"vec3 ambient;						\n"
	//	"vec3 diffuse;						\n"
	//	"vec3 specular;						\n"
	//	"float shininess;					\n"
	//	"};									\n"
	//	"									\n"
	//	"uniform Material material;         \n"
	//	"uniform vec4 u_Color;              \n"
	//	"uniform vec4 lightColor;           \n"
	//	"uniform vec4 lightPos;             \n"
	//	"uniform vec4 viewPos;              \n"
	//	"uniform float ambientStrength;     \n"
	//	"uniform float specularStrength;    \n"
	//	"\n"
	//	"void main()\n"
	//	"{\n"
	//	"   vec4 ambient = ambientStrength * lightColor * vec4(material.ambient, 1.0f); \n"
	//	"\n"
	//	"   vec4 norm = normalize(v_Normal);                        \n"
	//	"   vec4 lightDir = normalize(lightPos - FragPos);          \n"
	//	"   float diff = max(dot(norm, lightDir), 0.0);             \n"
	//	"   vec4 diffuseLight = diff * lightColor * vec4(material.diffuse, 1.0f);    \n"
	//	"\n"
	//	"vec4 viewDir = normalize(viewPos - FragPos);					\n"
	//	"vec4 reflectDir = reflect(-lightDir, norm);					\n"
	//	"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);		\n"
	//	"vec4 specular = specularStrength * spec * lightColor * vec4(material.specular, 1.0f);			\n"
	//	"\n"
	//	"   vec4 result = (ambient + diffuseLight + specular) * u_Color;       \n"
	//	"   color = result;                                        \n"
	//	"};\n";

	std::string fragmentShaderNoTexture =
		"#version 330 core\n"
		"\n"
		"    layout(location = 0) out vec4 color;"
		"\n"
		"    in vec4 FragPos;               \n"
		"    in vec3 v_Normal;              \n"
		"struct Material {					\n"
		"vec3 ambient;						\n"
		"vec3 diffuse;						\n"
		"vec3 specular;						\n"
		"float shininess;					\n"
		"};									\n"
		"struct Light {						\n"
		"vec3 position;						\n"
		"vec3 lightColor;					\n"
		"vec3 ambient;						\n"
		"vec3 diffuse;						\n"
		"vec3 specular;						\n"
		"float constant;					\n"
		"float linear;						\n"
		"float quadratic;					\n"	
		"};									\n"
		"									\n"
		"uniform Material material;         \n"
		"uniform Light light;		        \n"
		"uniform vec4 u_Color;              \n"
		"uniform vec4 viewPos;              \n"
		"\n"
		"void main()\n"
		"{\n"
		"   vec3 ambient = light.ambient * material.ambient; \n"
		"\n"
		"   vec3 norm = normalize(v_Normal);                        \n"
		"   vec4 lightDir = normalize(vec4(light.position,1.0) - FragPos);          \n"
		"   float diff = max(dot(vec4(norm,1.0f), lightDir), 0.0);             \n"
		"   vec4 diffuseLight =  vec4(light.diffuse,1.0) * (diff * vec4(material.diffuse,1.0));    \n"
		"\n"
		"vec4 viewDir = normalize(viewPos - FragPos);					\n"
		"vec4 reflectDir = reflect(-lightDir, vec4(norm, 1.0));					\n"
		"float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);		\n"
		"vec4 specular =  vec4(light.specular,1.0) * (spec * vec4(material.specular,1.0));			\n"
		"\n"
		"float distance = length(vec4(light.position,1.0) - FragPos);														    \n"
		"float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); \n"
		"   vec4 result = attenuation * ( vec4(ambient,1.0) + diffuseLight + specular);       \n"
		"   color = result * u_Color;                                        \n"
		"};\n";

	std::string fragmentShaderWithTexture =
		//"#shader fragment							\n"
		"#version 330 core\n"
		"\n"
		"	layout(location = 0) out vec4 color;"
		"\n"
		"	in vec2 v_TexCoord;"
		"\n"
		"	uniform vec4 u_Color;"
		"\n"
		"	uniform sampler2D u_Texture;"
		"\n"
		"void main()\n"
		"{\n"
		"	vec4 texColor = texture(u_Texture, v_TexCoord);"
		"\n"
		"	color = texColor;"
		"};\n";

#pragma endregion

public:
	DllExport Shader(ShaderType shaderType);
	DllExport ~Shader();

	DllExport void Bind() const;
	DllExport void Unbind() const;

	//Set uniforms
	DllExport void SetUniforms1f(const std::string name, float value);
	DllExport void SetUniforms1i(const std::string name, int value);
	DllExport void SetUniforms4f(const std::string name, float v0, float v1, float v2, float v3);
	DllExport void SetUniforms3f(const std::string name, float v0, float v1, float v2);
	DllExport void SetUniformsMat4f(const std::string name, const glm::mat4& matrix);

private:
	DllExport unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	DllExport unsigned int CompileShader(unsigned int type, const std::string& source);
	DllExport unsigned int GetUniformLocation(const std::string& name);

};

