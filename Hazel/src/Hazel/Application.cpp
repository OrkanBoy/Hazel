#include "hzpch.h"
#include "Application.h"

#include "Renderer/Shader.h"
#include "Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

#include <GLFW/glfw3.h>

namespace Hazel
{
	Application* Application::instance = 0;

	Application::Application() 
	{
		HZ_CORE_ASSERT(!instance, "Application already exists!")
		instance = this;

		window = std::unique_ptr<Window>(Window::Create());
		window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

		imGuiLayer = new ImGuiLayer();
		PushOverlay(imGuiLayer);
	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispacther(e);
		dispacther.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));
		HZ_CORE_INFO(e);
		for (auto it = layerStack.end(); it != layerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.handled) break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		running = false;
		return true;
	}

	void Application::Run()
	{
		while (running)
		{
			float time = (float)glfwGetTime();
			deltaTime = time - lastFrameTime;
			lastFrameTime = time;

			RendererAPI::Clear();

			for (Layer* layer : layerStack)
				layer->OnUpdate();

			imGuiLayer->Begin(); {
				for (Layer* layer : layerStack)
					layer->OnImGuiRender();
			} imGuiLayer->End();

			window->OnUpdate();
		}
	}
}