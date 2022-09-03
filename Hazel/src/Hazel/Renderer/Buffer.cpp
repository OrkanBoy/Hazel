#include "hzpch.h"
#include "Buffer.h"
#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

#include <glad/glad.h>

namespace Hazel
{
	BufferLayout::BufferLayout(const std::initializer_list<Hazel::BufferAttribute>& attributes)
		: attributes(attributes)
	{
		stride = 0;
		for (auto& attribute : this->attributes)
		{
			attribute.offset = stride;
			stride += attribute.size;
		}
	}

	VertexBuffer* VertexBuffer::Create(const std::span<const float>& vertices, BufferLayout layout)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(vertices, layout);
		}
		return nullptr;
	}
	IndexBuffer* IndexBuffer::Create(const std::span<const uint32_t>& indices) 
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(indices);
			default: HZ_ASSERT(false, "API Unsupported");
		}
	}
}