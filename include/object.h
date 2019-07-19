#pragma once
#include <vector>
#include <string>

#include "shader.h"

#pragma pack(push, 1)
struct Vert
{
	float x = 0.f, y = 0.f, z = 0.f;
	float r = 1.f, g = 1.f, b = 1.f;
	float u = 0.f, v = 1.f;
};
#pragma pack(pop)

class Mesh
{
public:
	template <class... U>
	static Mesh* Create(U&& ... u)
	{
		return meshes.emplace_back(new Mesh(std::forward<U>(u)...)).get();
	};

	template <class... U>
	static Shader* LoadShader(U&& ... u)
	{
		return &shaders.emplace_back(std::forward<U>(u)...);
	};

	static void DrawMeshes();
	static void CompileShaders();
	static void TerminateMeshes();

public:
	Mesh();
	~Mesh();

	void Draw();

	Shader* shader;
	unsigned int VBO, VAO, EBO;

	std::vector<Vert> vertices;
	std::vector<unsigned int> indicies;

private:
	static std::vector<std::unique_ptr<Mesh>> meshes;
	static std::vector<Shader> shaders;

	// Disallow copying
	Mesh(const Mesh&) = delete;
	void operator=(const Mesh&) = delete;
};