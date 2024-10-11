#include "Camera.h"

Camera::Camera(glm::vec2 position, float aspectratio, float zoom)
{
	OrginalPosition = position;
	AspectRatio = aspectratio;
	Zoom = zoom;
}

void Camera::Updatecamera(glm::vec2 position)
{
	//float lerp = 0.100f;
	//OrginalPosition = glm::mix(OrginalPosition , -position, lerp);

	OrginalPosition = -position;
}

glm::mat4 Camera::ReturnProjection(int width, int height) const
{
	// Calculate the height bounds using the zoom factor
	float top = height / (2.0f * Zoom);
	float bottom = -top;

	// Adjust the width bounds based on the aspect ratio
	float right = top * AspectRatio;
	float left = -right;

	glm::mat4 projection = glm::mat4(1.0f);
	projection = glm::ortho(left, right, bottom, top, 0.01f, 10.0f);
	return projection;
}

glm::mat4 Camera::ReturnView() const
{
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(OrginalPosition, -1.0f));
	return view;
}
