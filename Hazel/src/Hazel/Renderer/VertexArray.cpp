#include "hzpch.h"
#include "VertexArray.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hazel
{
	VertexArray* VertexArray::Create()
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::OpenGL: return new OpenGLVertexArray();
			default: HZ_ASSERT(false, "API Unsupported");
		}
	}
}