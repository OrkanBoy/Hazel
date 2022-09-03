#include "hzpch.h"
#include "OpenGLBuffer.h"

namespace Hazel
{

	///////Vertex Buffer//////////////////////////////////////
	OpenGLVertexBuffer::OpenGLVertexBuffer(const std::span<const float>& vertices, const BufferLayout& layout)
	{
		this->layout = layout;
		glCreateBuffers(1, &id);
		SetData(vertices);
	}

	void OpenGLVertexBuffer::SetData(const std::span<const float>& vertices)
	{
		Bind();
		glBufferData(GL_ARRAY_BUFFER, vertices.size_bytes(), &vertices.front(), GL_STATIC_DRAW);
	}

	///////Index Buffer//////////////////////////////////////
	OpenGLIndexBuffer::OpenGLIndexBuffer(const std::span<const uint32_t>& indices)
	{
		glCreateBuffers(1, &id);
		SetData(indices);
	}

	void OpenGLIndexBuffer::SetData(const std::span<const uint32_t>& indices)
	{
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size_bytes(), &indices.front(), GL_STATIC_DRAW);
		count = (uint32_t)indices.size_bytes() / sizeof(uint32_t);
	}
}
