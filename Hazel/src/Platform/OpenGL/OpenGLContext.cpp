#include "hzpch.h"
#include "OpenGLContext.h"

#include <GLAD/glad.h>

namespace Hazel
{
	OpenGLContext::OpenGLContext(GLFWwindow* window) 
		: window(window)
	{
		HZ_CORE_ASSERT(window, "Window handler cannot be null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		HZ_CORE_ASSERT(status, "Failed to initialize Glad");

		HZ_CORE_INFO("OpenGL Info:");
		HZ_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		HZ_CORE_INFO("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		HZ_CORE_INFO("	Version: {0}", (const char*)glGetString(GL_VERSION));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(window);
	}
}