#pragma once

#include "Hazel/Renderer/Buffer.h"

#include <glad/glad.h>

namespace Hazel
{
	static GLenum ShaderDataTypeToGLType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:
		case ShaderDataType::Float2:
		case ShaderDataType::Float3: 
		case ShaderDataType::Float4:
		case ShaderDataType::Mat2:
		case ShaderDataType::Mat3:
		case ShaderDataType::Mat4: return GL_FLOAT;
		case ShaderDataType::Int: 
		case ShaderDataType::Int2: 
		case ShaderDataType::Int3: 
		case ShaderDataType::Int4: return GL_INT;
		case ShaderDataType::Bool: return GL_BOOL;
		}
		HZ_CORE_ASSERT(false, "Unknown ShaderDataType");
		return GL_INVALID_ENUM;
	}

	///////Vertex Buffer//////////////////////////////////////
	class OpenGLVertexBuffer : public VertexBuffer 
	{
	public:
		OpenGLVertexBuffer(const std::span<const float>& vertices, const BufferLayout& layout);
		~OpenGLVertexBuffer() override { glDeleteBuffers(1, &id); }

		void Bind() const override { glBindBuffer(GL_ARRAY_BUFFER, id); }
		void Unbind() const override { glBindBuffer(GL_ARRAY_BUFFER, 0); }
		void SetData(const std::span<const float>& vertices) override;

	private:
		uint32_t id;
	};

	///////Index Buffer//////////////////////////////////////
	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(const std::span<const uint32_t>& indices);
		~OpenGLIndexBuffer() override { glDeleteBuffers(1, &id); }

		void Bind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id); }
		void Unbind() const override { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }

		void SetData(const std::span<const uint32_t>& indices) override;

	private:
		uint32_t id;
	};
}