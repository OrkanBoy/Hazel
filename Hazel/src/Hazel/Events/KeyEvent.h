#pragma once

#include "hzpch.h"
#include "Event.h"

namespace Hazel
{
	class HAZEL_API KeyEvent : public Event
	{
	public: 
		int GetKeyCode() const { return keycode; }

		EVENT_CATEGORY(InputCategory | KeyboardCategory)

	protected:
		KeyEvent(int keycode)
			: keycode(keycode) {}

		int keycode;
	};

	class HAZEL_API KeyPressedEvent : public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KeyPressed)

		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), repeatCount(repeatCount) {}

		int GetRepeatCount() const { return repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << keycode << " (" << repeatCount << " repeats)";
			return ss.str();
		}
		
	private:
		int repeatCount;
	};

	class HAZEL_API KeyReleasedEvent : public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KeyReleased)

		KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << keycode;
			return ss.str();
		}
	};

	class HAZEL_API KeyTypedEvent : public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KeyTyped)

			KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << keycode;
			return ss.str();
		}
	};
}