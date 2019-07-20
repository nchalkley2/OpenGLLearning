#include "project.h"
#include "shader.h"
#include "filesystem.h"

std::vector<std::unique_ptr<Shader>> Shader::shaders;

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& inName): name(inName)
{
	namespace FS = Filesystem;
	std::string vertexSrc, fragmentSrc;

	if (!FS::ReadFile(vertexPath, vertexSrc))
	{
		std::cout << "Shader::Shader error! Failed to read file from vertexPath\n";
		return;
	}

	if (!FS::ReadFile(fragmentPath, fragmentSrc))
	{
		std::cout << "Shader::Shader error! Failed to read file from fragmentPath\n";
		return;
	}

	std::vector<int> Shaders;
	int shaderProgramTemp = glCreateProgram();

	const auto CompileShader = [&Shaders, shaderProgramTemp](int ShaderType,
		std::vector<const GLchar*> ShaderSources) -> bool
	{
		int Shader = glCreateShader(ShaderType);
		Shaders.push_back(Shader);
		glShaderSource(Shader, ShaderSources.size(), ShaderSources.data(), nullptr);
		glCompileShader(Shader);

		int success;
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char infoLog[512];
			glGetShaderInfoLog(Shader, 512, nullptr, infoLog);
			std::cout << "Error! Shader compilation failed!\n" << infoLog << "\n";
			return false;
		}
		else
		{
			glAttachShader(shaderProgramTemp, Shader);
			return true;
		}
	};

	if (!CompileShader(GL_VERTEX_SHADER, { vertexSrc.c_str() }))
	{
		std::cout << "Shader::Shader error! Failed to compile vertex shader!\n";
		return;
	}

	if (!CompileShader(GL_FRAGMENT_SHADER, { fragmentSrc.c_str() }))
	{
		std::cout << "Shader::Shader error! Failed to compile fragment shader!\n";
		return;
	}

	glLinkProgram(shaderProgramTemp);

	// Check for linking errors
	int success;
	glGetProgramiv(shaderProgramTemp, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgramTemp, 512, nullptr, infoLog);
		std::cout << "Shader::Shader error! Shader linking failed!\n" << infoLog << "\n";
	}

	for (const int Shader : Shaders)
	{
		glDeleteShader(Shader);
	};

	shaderProgram = shaderProgramTemp;
}