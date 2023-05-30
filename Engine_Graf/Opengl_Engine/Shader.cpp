#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"

DllExport Shader::Shader(ShaderType shaderType)
{
	m_RendererID = 0;
	ShaderProgramSource source;
	
	source.VertexSource = read_file("res/Shaders/vertex.glsl");
	source.FragmentSource = read_file("res/Shaders/fragment.glsl");
	
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

DllExport Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}

DllExport void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

DllExport void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

DllExport void Shader::SetUniforms4f(const std::string name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniforms3f(const std::string name, float v0, float v1, float v2)
{
	GLCall(glUniform3f(GetUniformLocation(name), v0, v1, v2));
}

DllExport void Shader::SetUniformsMat4f(const std::string name, const glm::mat4& matrix)
{
	GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


DllExport void Shader::SetUniforms1f(const std::string name, float value)
{
	GLCall(glUniform1f(GetUniformLocation(name), value));
}

DllExport void Shader::SetUniforms1i(const std::string name, int value)
{
	GLCall(glUniform1i(GetUniformLocation(name), value));
}

DllExport unsigned int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if (location == -1)
		std::cout << "Warning: uniform " << name << " doesn't exist!" << std::endl;

	m_UniformLocationCache[name] = location;
	return location;
}

std::string Shader::read_file(const std::string& filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) 
	{
		throw std::runtime_error("Failed to open file: " + filename);
	}
	std::string content((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	return content;
}


DllExport unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	GLCall(unsigned int id = glCreateShader(type));
	const char* src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE)
	{
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char* message = (char*)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
	//Terminar
}


DllExport unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	GLCall(unsigned int program = glCreateProgram());
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

