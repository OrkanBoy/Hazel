#include "hzpch.h"
#include "OpenGLVertexArray.h"

#include "OpenGLBuffer.h"

namespace Hazel
{
	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) 
	{
		HZ_CORE_ASSERT(vertexBuffer->layout.GetAttributes().size(), "No VertexLayout");

		Bind();
		vertexBuffer->Bind();

		int i = 0;
		auto& layout = vertexBuffer->layout;
		for (const auto& attribute : layout)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i,
				GetComponentCount(attribute.type),
				ShaderDataTypeToGLType(attribute.type),
				attribute.normalized,
				layout.GetStride(),
				(const void*)attribute.offset);
			i++;
		}
		vertexBuffers.emplace_back(vertexBuffer);
	}
	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		Bind();
		indexBuffer->Bind();
		this->indexBuffer = indexBuffer;
	}
}