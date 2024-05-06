#pragma once

#include "Event.h"

namespace Hazel 
{

	class  WindowResizeEvent : public Event//window重新设置大小
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)//大小用unsigned int定义，并初始化为width和height
			: m_Width(width), m_Height(height) {}

		inline unsigned int GetWidth() const { return m_Width; }//接收长和宽的数据
		inline unsigned int GetHeight() const { return m_Height; }

		std::string ToString() const override//重载为string并输出
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};
	//以下类功能和名称一致
	class  WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class  AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}