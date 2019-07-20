#pragma once
#include "project.h"

class Shader
{
public:
	template <class... U>
	static Shader* LoadShader(U&& ... u)
	{
		return shaders.emplace_back(new Shader(std::forward<U>(u)...)).get();
	};

	static Shader* GetShader(const std::string& name)
	{
		for (auto& shader : shaders)
		{
			if (shader->name == name)
			{
				return shader.get();
			}
		}

		return nullptr;
	};

	Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& inName);

	bool IsValid() const
	{
		return shaderProgram != -1;
	};

	int GetShaderProgramID() const
	{
		return shaderProgram;
	}

	void Use() const
	{
		glUseProgram(shaderProgram);
	};

	void SetBool(const std::string& name, bool value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value);
	}
	void SetInt(const std::string& name, int value) const
	{
		glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}
	void SetFloat(const std::string& name, float value) const
	{
		glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value);
	}

private:
	// shader program ID
	int shaderProgram = -1;
	std::string name;

	static std::vector<std::unique_ptr<Shader>> shaders;
};