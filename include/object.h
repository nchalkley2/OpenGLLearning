#pragma once
#include <vector>
#include <string>

#pragma pack(push, 1)
struct Pos
{
	float x = 0.f, y = 0.f, z = 0.f;
};
#pragma pack(pop)

class Mesh
{
public:
	template <class... U>
	static Mesh* Create(U&& ... u)
	{
		return Meshes.emplace_back(new Mesh(std::forward<U>(u)...)).get();
	};

	static void DrawMeshes();
	static void CompileShaders();
	static void TerminateMeshes();
	static int ShaderProgram;

public:
	Mesh();
	~Mesh();

	void Draw();

	int Shader;
	unsigned int VBO, VAO, EBO;

	std::vector<Pos> Vertices;
	std::vector<unsigned int> Indicies;

private:
	static std::vector<std::unique_ptr<Mesh>> Meshes;

	Mesh(const Mesh&) = delete;
	void operator=(const Mesh&) = delete;
};