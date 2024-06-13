#pragma once

#include "pgpch.h"
#include "Pigeon/Core.h"

namespace Pigeon {

    // Event in Pigeon are currently blocking

    // �¼�����
	enum class EventType
	{
		None = 0,
        WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    // �¼�����
    enum EventCategory
    {
        None = 0,
        EventCategoryApplication    = BIT(0),
        EventCategoryInput          = BIT(1),
        EventCategoryKeyboard       = BIT(2),
        EventCategoryMouse          = BIT(3),
        EventCategoryMouseButton    = BIT(4)
    };

    // ʵ���������麯��, �Լ��������ط���ȡ�¼����͵ľ�̬����
#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
                                virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    // �¼�����
    class PIGEON_API Event
    {
        friend class EventDispatcher;
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        
        // ���ڵ���
        virtual std::string ToString() const { return GetName(); }

        // �ж��¼��Ƿ�����ĳ������
        inline bool IsInCategory(EventCategory category)
        {
            return GetCategoryFlags() & category;
        }

    protected:
        bool m_Handled = false; // �ж��¼��Ƿ񱻴���
    };

    // �¼��ɷ���, �����¼����͵����¼�
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
                m_Event.m_Handled = func(*(T*)&m_Event);
                return true;
            }
            return false;
        }

    private:
        Event& m_Event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}