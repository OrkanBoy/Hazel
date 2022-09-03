#pragma once

#include "hzpch.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "Hazel/Core.h"

namespace Hazel
{
	enum EventCategory
	{
		None = 0,
		ApplicationCategory = BIT(0),
		InputCategory = BIT(1),
		KeyboardCategory = BIT(2),
		MouseCategory = BIT(3),
		MouseButtonCategory = BIT(4)
	};

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowdLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

#define EVENT_CATEGORY(categoryFlags) virtual int GetCategoryFlags() const override { return categoryFlags; }

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
	virtual EventType GetType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #type; };

	class HAZEL_API Event
	{
	public:
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
		bool handled = false;
	};
	
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (event.GetType() == T::GetStaticType())
			{
				event.handled = func(*(T*)&event);
				return true;
			}
			return false;
		}

	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) { return os << e.ToString(); }
}

