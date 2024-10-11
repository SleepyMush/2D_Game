#include "Render.h"

Render::Mesh Render::CreateMesh(std::vector<Vertex> const& vertices, std::vector<uint16_t> const& indices)
{
    Mesh mesh;

    // Generate VAO, VBO, and EBO
    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glGenBuffers(1, &mesh.ebo);

    // Bind VAO
    glBindVertexArray(mesh.vao);

    // Setup VBO
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Setup EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), indices.data(), GL_STATIC_DRAW);

    // Unbind VAO
    glBindVertexArray(0);

    return mesh;
}

void Render::DrawMesh(GLuint& vao, std::vector<uint16_t> const& indices)
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<uint16_t>(indices.size()), GL_UNSIGNED_SHORT, nullptr);
}

Render::Mesh Render::CreateMultiMesh(std::vector<Vertex> const& vertices, std::vector<uint16_t> const& indices)
{
    Mesh mesh;

    // Generate VAO, VBO, and EBO
    glGenVertexArrays(1, &mesh.vao);
    glGenBuffers(1, &mesh.vbo);
    glGenBuffers(1, &mesh.ebo);

    // Bind VAO
    glBindVertexArray(mesh.vao);

    // Setup VBO
    glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // Setup EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint16_t), &indices[0], GL_STATIC_DRAW);

    // Unbind VAO
    glBindVertexArray(0);

    return mesh;
}

void Render::DrawMultiMesh(GLuint& vao, std::vector<uint16_t> const& indices, uint16_t count)
{
    glBindVertexArray(vao);
    glDrawElementsInstanced(GL_TRIANGLES, static_cast<uint16_t>(indices.size()), GL_UNSIGNED_SHORT, 0, count);
}

Render::~Render()
{
    Mesh mesh;
    glDeleteVertexArrays(1, &mesh.vao);
    glDeleteBuffers(1, &mesh.vbo);
    glDeleteBuffers(1, &mesh.ebo);
}

