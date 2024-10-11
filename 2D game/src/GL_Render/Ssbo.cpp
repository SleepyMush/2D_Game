#include "Ssbo.h"

void Ssbo::SSBObuffer(GLsizeiptr size, int index)
{
    glGenBuffers(1, &ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferData(GL_SHADER_STORAGE_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, index, ssbo);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, index);
}

void Ssbo::updateSSBO(GLsizeiptr size, void* data, int index)
{
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, index, size, data);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, index);
}

void Ssbo::clear()
{
    glDeleteBuffers(1, &ssbo);
}
