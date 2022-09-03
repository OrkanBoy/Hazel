#pragma once

#include "hzpch.h"
#include "Event.h"

namespace Hazel
{
	class HAZEL_API MouseMovedEvent : public Event
	{
	public:
		EVENT_CATEGORY(MouseCategory | InputCategory)
		EVENT_CLASS_TYPE(MouseMoved)
		MouseMovedEvent(float x, float y)
			: x(x), y(y) {}

		float GetX() const { return x; }
		float GetY() const { return y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << x << ", " << y;
			return ss.str();
		}
	private:
		float x, y;
	};

	class HAZEL_API MouseScrolledEvent : public Event
	{
	public: 
		EVENT_CATEGORY(MouseCategory | InputCategory)
		EVENT_CLASS_TYPE(MouseScrolled)
		MouseScrolledEvent(float xOffset, float yOffset)
			: xOffset(xOffset), yOffset(yOffset) {}

		float GetXOffset() const { return xOffset; }
		float GetYOffset() const { return yOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << xOffset << ", " << yOffset;
			return ss.str();
		}

	private:
		float xOffset, yOffset;
	};

	class HAZEL_API MouseButtonEvent : public Event
	{
	public:
		EVENT_CATEGORY(MouseButtonCategory | InputCategory);
		MouseButtonEvent(int button)
			: button(button) {}

		int GetButton() { return button; }

	protected:
		int button;
	};

	class HAZEL_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonPressed)
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button;
			return ss.str();
		}
	};

	class HAZEL_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		EVENT_CLASS_TYPE(MouseButtonReleased)
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button;
			return ss.str();
		}
	};
}