#include "hzpch.h"
#include "Camera.h"

#include "glm/gtc/matrix_transform.hpp"

namespace Hazel
{
	void Camera::Recalculate() 
	{
		viewProj = glm::translate(glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)), -position);
		viewProj = glm::ortho(-width / 2, width / 2, -height / 2, height / 2, -1.0f, 1.0f) * viewProj;
	}
}