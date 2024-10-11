#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera 
{
public:
	glm::vec2 OrginalPosition;
	float AspectRatio;
	float Zoom;

	Camera(glm::vec2 position = glm::vec2(0.0f, 0.0f), float aspectratio = 0.0f, float zoom = 0.0f);
	void Updatecamera(glm::vec2 position);
	glm::mat4 ReturnProjection(int width, int height) const;
	glm::mat4 ReturnView() const;
};
