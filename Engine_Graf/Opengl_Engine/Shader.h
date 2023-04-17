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
		//"#shader vertex								\n"
		"#version 330 core\n"
		"\n"
		"layout(location = 0) in vec4 position;"
		"\n"
		"layout(location = 1) in vec3 normal;"
		"\n"
		"out vec3 v_Normal;\n"
		"uniform mat4 u_MVP;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = u_MVP * position;\n"
		"	v_Normal = normal;\n"
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

	std::string fragmentShaderNoTexture =
		//"#shader fragment							\n"
		"#version 330 core\n"
		"\n"
		"	layout(location = 0) out vec4 color;"
		"\n"
		"uniform vec4 u_Color;"
		"\n"
		"uniform vec4 lightColor;"
		"\n"
		"uniform vec4 objectColor;"
		"\n"
		"uniform float ambientStrength;"
		"\n"
		"void main()\n"
		"{\n"
		"   vec4 ambient = ambientStrength * lightColor;\n"
		"   vec4 result = ambient * u_Color;\n"
		"	color = result;"
		"};\n";

	/*
	"#version 330 core\n"
    "out vec4 FragColor;\n"
    "uniform vec3 lightColor;\n"
    "uniform vec3 objectColor;\n"
    "void main()\n"
    "{\n"
    "   float ambientStrength = 0.2f;\n"
    "   vec3 ambient = ambientStrength * lightColor;\n"
    "   vec3 result = ambient * objectColor;\n"
    "   FragColor = vec4(result, 1.0f);\n"
    "}\n\0";
	*/

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
	DllExport void SetUniformsMat4f(const std::string name, const glm::mat4& matrix);

private:
	DllExport unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	DllExport unsigned int CompileShader(unsigned int type, const std::string& source);
	DllExport unsigned int GetUniformLocation(const std::string& name);
	//ShaderProgramSource ParseShader(const std::string& filepath);
};

