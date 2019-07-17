#include "project.h"
#include "object.h"
#include "engine.h"

static const GLchar* vertexShaderSource = R"HERE(
	#version 330 core

	layout (location = 0) in vec3 aPos;

	void main()
	{
		gl_Position = vec4(aPos, 1.0);
	}
)HERE";

static const GLchar* fragmentShaderSource = R"HERE(
	#version 330 core
	
	out vec4 FragColor;

	void main()
	{
		FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	}
)HERE";

std::vector<std::unique_ptr<Mesh>> Mesh::Meshes;
int Mesh::ShaderProgram;

void Mesh::CompileShaders()
{
	std::vector<int> Shaders;
	ShaderProgram = glCreateProgram();

	const auto CompileShader = [&Shaders](int ShaderType,
		std::vector<const GLchar*> ShaderSources) -> bool
	{
		int Shader = glCreateShader(ShaderType);
		Shaders.push_back(Shader);
		glShaderSource(Shader, ShaderSources.size(), ShaderSources.data(), nullptr);
		glCompileShader(Shader);

		int success;
		char infoLog[512];
		glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(Shader, 512, nullptr, infoLog);
			std::cout << "Error! Shader compilation failed!\n" << infoLog << "\n";
			return false;
		}
		else
		{
			glAttachShader(ShaderProgram, Shader);
			return true;
		}
	};

	CompileShader(GL_VERTEX_SHADER, { vertexShaderSource });
	CompileShader(GL_FRAGMENT_SHADER, { fragmentShaderSource });

	glLinkProgram(ShaderProgram);

	// Check for linking errors
	int success;
	char infoLog[512];
	glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ShaderProgram, 512, nullptr, infoLog);
		std::cout << "Error! Shader linking failed!\n" << infoLog << "\n";
	}

	for (const int Shader : Shaders)
	{
		glDeleteShader(Shader);
	};
}

static AddStaticCallback CompileShadersCallback(Engine::OpenGLInit, &Mesh::CompileShaders);

void Mesh::DrawMeshes()
{
	for (auto& Mesh : Meshes)
	{
		Mesh->Draw();
	}
}

static AddStaticCallback DrawMeshesCallback(Engine::OpenGLDraw, &Mesh::DrawMeshes);

void Mesh::TerminateMeshes()
{
	Meshes.clear();
}

static AddStaticCallback TerminateMeshesCallback(Engine::OpenGLTerminate, &Mesh::TerminateMeshes);

Mesh::Mesh(): Shader(ShaderProgram)
{
	Vertices = {
		{  0.5f,  0.5f, 0.0f },
		{  0.5f, -0.5f, 0.0f },
		{ -0.5f, -0.5f, 0.0f },
		{ -0.5f,  0.5f, 0.0f }
	};

	Indicies = {
		0, 1, 3,
		1, 2, 3
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s),
	// and then configure vertex attribute(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	const size_t VerticesRawSize = Vertices.size() * sizeof(decltype(Vertices)::value_type);
	glBufferData(GL_ARRAY_BUFFER, VerticesRawSize, Vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Pos), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	const size_t IndiciesRawSize = Indicies.size() * sizeof(decltype(Indicies)::value_type);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, IndiciesRawSize, Indicies.data(), GL_STATIC_DRAW);
}

void Mesh::Draw()
{
	glUseProgram(ShaderProgram);
	glBindVertexArray(VAO);
	
	glDrawElements(GL_TRIANGLES, Indicies.size(), GL_UNSIGNED_INT, (void*)0);
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}