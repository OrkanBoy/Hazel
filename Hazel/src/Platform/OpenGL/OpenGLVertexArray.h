#pragma once

#include "Hazel/Renderer/VertexArray.h"

#include <glad/glad.h>

namespace Hazel
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray() { glCreateVertexArrays(1, &id); }
		~OpenGLVertexArray() override { glDeleteVertexArrays(1, &id); }

		void Bind() const override { glBindVertexArray(id); }
		void Unbind() const override { glBindVertexArray(0); }

		void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
	private:
		uint32_t id;
	};
}