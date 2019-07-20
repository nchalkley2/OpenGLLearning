#include "project.h"
#include "object.h"
#include "engine.h"

#include <filesystem>

std::vector<std::unique_ptr<Mesh>> Mesh::meshes;
<<<<<<< HEAD

void Mesh::CompileShaders()
{
	Shader::LoadShader("shaders/defaultshader.vs", "shaders/defaultshader.fs", "default");
=======
std::vector<Shader> Mesh::shaders;

void Mesh::CompileShaders()
{
	LoadShader("shaders/defaultshader.vs", "shaders/defaultshader.fs", "default");
>>>>>>> 5051886678e9e158040b94001f0bf96848d0970d
}

static AddStaticCallback CompileShadersCallback(Engine::onOpenGLInit, &Mesh::CompileShaders);

void Mesh::DrawMeshes()
{
	for (auto& mesh : meshes)
	{
		mesh->Draw();
	}
}

static AddStaticCallback DrawMeshesCallback(Engine::onOpenGLDraw, &Mesh::DrawMeshes);

void Mesh::TerminateMeshes()
{
	meshes.clear();
}	

static AddStaticCallback TerminateMeshesCallback(Engine::onOpenGLTerminate, &Mesh::TerminateMeshes);

Mesh::Mesh()
{
	vertices = {
		{  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f },
		{  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f },
		{ -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f },
		{ -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f }
	};

	indicies = {
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
	const size_t verticesRawSize = vertices.size() * sizeof(decltype(vertices)::value_type);
	glBufferData(GL_ARRAY_BUFFER, verticesRawSize, vertices.data(), GL_STATIC_DRAW);

	// Vertex positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertices)::value_type), 
		(void*)0);
	glEnableVertexAttribArray(0);

	// Vertex colors
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(decltype(vertices)::value_type), 
		(void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	const size_t indiciesRawSize = indicies.size() * sizeof(decltype(indicies)::value_type);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indiciesRawSize, indicies.data(), GL_STATIC_DRAW);

<<<<<<< HEAD
	shader = Shader::GetShader("default");
=======
	shader = &shaders[0];
>>>>>>> 5051886678e9e158040b94001f0bf96848d0970d
}

void Mesh::Draw()
{
	if (shader && shader->IsValid())
	{
		shader->Use();
		glBindVertexArray(VAO);

		int vertexColorLocation = glGetUniformLocation(shader->GetShaderProgramID(), "ourColor");

		float timeValue = glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;
		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, (void*)0);
	}
}

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}