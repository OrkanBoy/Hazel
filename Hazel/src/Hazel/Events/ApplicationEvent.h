#pragma once

#include "hzpch.h"
#include "Event.h"


namespace Hazel
{
	class HAZEL_API WindowResizeEvent : public Event
	{
	public:
		EVENT_CATEGORY(ApplicationCategory)
		EVENT_CLASS_TYPE(WindowResize)
		WindowResizeEvent(uint32_t width, uint32_t height)
			: width(width), height(height) {}

		uint16_t GetWidth() { return width; }
		uint16_t GetHeight() { return height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width << ", " << height;
			return ss.str();
		}

	private:
		uint32_t width, height;
	};

	class HAZEL_API WindowCloseEvent : public Event
	{
	public:
		EVENT_CATEGORY(ApplicationCategory)
		EVENT_CLASS_TYPE(WindowClose)
	};

	class HAZEL_API AppTickEvent : public Event
	{
	public:
		EVENT_CATEGORY(ApplicationCategory)
		EVENT_CLASS_TYPE(AppTick)
	};

	class HAZEL_API AppUpdateEvent : public Event
	{
	public:
		EVENT_CATEGORY(ApplicationCategory)
		EVENT_CLASS_TYPE(AppUpdate)
	};

	class HAZEL_API AppRenderEvent : public Event
	{
	public:
		EVENT_CATEGORY(ApplicationCategory)
		EVENT_CLASS_TYPE(AppRender)
	};
}