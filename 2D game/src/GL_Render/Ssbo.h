#pragma once
#include <glad/glad.h>

class Ssbo
{
private:
	GLuint ssbo;
public:
	void SSBObuffer(GLsizeiptr size, int index);
	void updateSSBO(GLsizeiptr size, void* data,int index);
	void clear();
};
