#pragma once

#include "Hazel/Input.h"

namespace Hazel
{
	class WindowsInput : public Input
	{
	private:
		bool IsKeyPressedImpl(int keycode) const override;
		bool IsMouseButtonPressedImpl(int button) const override;

		float GetMouseXImpl() const override;
		float GetMouseYImpl() const override;
		std::pair<float, float> GetMousePosImpl() const override;
	};
}