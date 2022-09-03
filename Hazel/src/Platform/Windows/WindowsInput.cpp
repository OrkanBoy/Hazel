#include "hzpch.h"
#include "WindowsInput.h"

#include "Hazel/Application.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
	Input* Input::instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int keycode) const 
	{
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const 
	{
		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		int state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	float WindowsInput::GetMouseXImpl() const
	{
		auto [x, _] = GetMousePosImpl();
		return x;
	}
	float WindowsInput::GetMouseYImpl() const
	{
		auto [_, y] = GetMousePosImpl();
		return y;
	}
	std::pair<float, float> WindowsInput::GetMousePosImpl() const 
	{
		GLFWwindow* window = (GLFWwindow*)Application::Get().GetWindow().GetNativeWindow();
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return { (float)xpos, (float)ypos};
	}
}