#pragma once

#include "Core.h"


#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"
#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "Core/DeltaTime.h"
#include "Renderer/Shader.h"

namespace Hazel
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		bool OnWindowClose(WindowCloseEvent& e);
		void PushLayer(Layer* layer) { layerStack.PushLayer(layer); }
		void PushOverlay(Layer* overlay) { layerStack.PushOverlay(overlay); }

		static Application& Get() { return *instance; }
		Window& GetWindow() { return *window; }
		DeltaTime& GetDeltaTime() { return deltaTime; }
	private:
		std::unique_ptr<Window> window;
		ImGuiLayer* imGuiLayer;
		LayerStack layerStack;
		float lastFrameTime = 0.0f;
		DeltaTime deltaTime;
		bool running = true;

		static Application* instance;
	};
	
	Application* CreateApplication();
}


