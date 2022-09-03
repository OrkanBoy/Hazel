#pragma once

#include "Hazel/Window.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		uint32_t GetWidth() const override { return data.width; }
		uint32_t GetHeight() const override { return data.height; }

		void SetEventCallback(const EventCallbackFn& callback) override { data.eventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		void* GetNativeWindow() const override { return window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

		GLFWwindow* window;
		GraphicsContext* context;

		struct WindowData
		{
			std::string title;
			uint32_t width, height;
			bool vSync;
			EventCallbackFn eventCallback;
		};

		WindowData data;

	};
}