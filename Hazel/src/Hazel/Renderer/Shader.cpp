#include "hzpch.h"
#include "Shader.h"
#include "Renderer.h"

#include <string>
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
	Shader* Shader::Create(const std::string& vertSrc, const std::string& fragSrc)
	{
		switch (RendererAPI::GetAPI())
		{
			case RendererAPI::API::OpenGL: return new OpenGLShader(vertSrc, fragSrc);
			default: HZ_ASSERT(false, "API Unsupported");
		}
	}
}