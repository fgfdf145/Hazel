#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel 
{

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then an there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" part of the update stage.

	enum class EventType//定义事件类型
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory//定义事件策略
	{
		None = 0,
		EventCategoryApplication    = BIT(0),
		EventCategoryInput          = BIT(1),
		EventCategoryKeyboard       = BIT(2),
		EventCategoryMouse          = BIT(3),
		EventCategoryMouseButton    = BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
	public:
		bool Handled = false;//判断事件是否处理

		virtual EventType GetEventType() const = 0;//返回事件类型
		virtual const char* GetName() const = 0;//返回事件名称
		virtual int GetCategoryFlags() const = 0;//返回事件类型
		virtual std::string ToString() const { return GetName(); }//用字符串表示事件类型

		inline bool IsInCategory(EventCategory category)//检查当前事件类型是否为给定的类型
		{
			return GetCategoryFlags() & category;
		}
	};

	class EventDispatcher//用于事件分发类
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event)
			: m_Event(event)
		{

		}

		template<typename T>
		bool Dispatch(EventFn<T> func)//这个函数检查m_Event的事件类型是否与模板参数T的静态类型匹配。如果匹配，它将调用func并传递m_Event转换为T类型的引用。如果func处理了事件，它将返回true，否则返回false。
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)//重载为string并输出
	{
		return os << e.ToString();
	}
}

