#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <string>

struct Vertex
{
	glm::vec3 position;
};

class Render
{
public:
	struct Mesh
	{
		GLuint vao;
		GLuint vbo;
		GLuint ebo;
	};

	Mesh CreateMesh(std::vector<Vertex> const& vertices, std::vector<uint16_t> const& indices);
	void DrawMesh(GLuint& vao, std::vector<uint16_t> const& indices);

	Mesh CreateMultiMesh(std::vector<Vertex> const& vertices, std::vector<uint16_t> const& indices);
	void DrawMultiMesh(GLuint& vao, std::vector<uint16_t> const& indices, uint16_t count);

	~Render();
};