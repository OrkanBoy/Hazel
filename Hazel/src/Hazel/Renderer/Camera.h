#pragma once

#include <glm/glm.hpp>

namespace Hazel
{
	class Camera 
	{
	public:
		Camera(float width, float height, glm::vec3 position, float rotation)
			: width(width), height(height), position(position), rotation(rotation) { Recalculate(); }

		void SetWidth(float width) { this->width = width; Recalculate(); }
		void SetHeight(float height) { this->height = height; Recalculate(); }
		void SetPosition(glm::vec3 position) { this->position = position; Recalculate(); }
		void SetRotation(float rotation) { this->rotation = rotation; Recalculate(); }

		float GetWidth() const { return width; }
		float GetHeight() const { return height; }
		glm::vec3 GetPosition() const { return position; }
		float GetRotation() const { return rotation; }
		const glm::mat4& GetViewProj() const{ return viewProj; }

	private:
		float width, height;
		glm::vec3 position;
		float rotation;

		void Recalculate();
		glm::mat4 viewProj;
	};
}