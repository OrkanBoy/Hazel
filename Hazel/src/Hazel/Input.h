#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
	class HAZEL_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return instance->IsKeyPressedImpl(keycode); }

		static bool IsMouseButtonPressed(int button) { return instance->IsMouseButtonPressedImpl(button); }
		static float GetMouseX() { return instance->GetMouseXImpl(); }
		static float GetMouseY() { return instance->GetMouseYImpl(); }
		static std::pair<float, float> GetMousePos() { return instance->GetMousePosImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) const = 0;

		virtual bool IsMouseButtonPressedImpl(int button) const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;
		virtual std::pair<float, float> GetMousePosImpl() const = 0;

	private:
		static Input* instance;

	};
}