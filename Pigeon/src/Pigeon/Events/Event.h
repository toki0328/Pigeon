#pragma once

#include "pgpch.h"
#include "Pigeon/Core.h"

namespace Pigeon {

    // Event in Pigeon are currently blocking

    // 事件类型
	enum class EventType
	{
		None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    // 事件分类
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyboard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4)
    };

    // 实现三个纯虚函数, 以及在其他地方获取事件类型的静态方法
#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    // 事件基类
    class PIGEON_API Event
    {
        friend class EventDispatcher;
    public:
        //virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        
        // 用于调试
        virtual std::string ToString() const { return GetName(); }

        // 判断事件是否属于某个分类
        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

        bool Handled = false; // 判断事件是否被处理
    };

    // 事件派发器, 基于事件类型调度事件
    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event)
            : m_Event(event) {} 

        template<typename T>
        bool Dispatch(EventFn<T> func)
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


    // 重写操作符，用于事件日志的输出（暂时无法使用）
    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

}