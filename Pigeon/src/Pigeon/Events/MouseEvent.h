#pragma once


#include "Event.h"


namespace Pigeon {

	// 鼠标移动事件
	class PIGEON_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}


		inline float GetX() const { return m_MouseX; }
		inline float GetY() const { return m_MouseY; }

		std::string ToString() const override
		{
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_MouseX, m_MouseY;
	};

	// 鼠标滚动事件
	class PIGEON_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffSet(xOffset), m_YOffset(yOffset) {}

		inline float GetXOffset() const { return m_XOffSet; }
		inline float GetYOffset() const { return m_YOffset; }

		std::string ToString() const override
		{
            std::stringstream ss;
			ss << "MouseScrolledEvent: " << m_XOffSet << ", " << m_YOffset;
            return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_XOffSet, m_YOffset;
	};

	// 鼠标按键事件基类
	class PIGEON_API MouseButtonEvent : public Event
	{
	public:
		inline int GetButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	// 鼠标按键按下事件
    class PIGEON_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int button)
            : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_Button;
            return ss.str();
		}

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    // 鼠标按键释放事件
    class PIGEON_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int button)
            : MouseButtonEvent(button) {}

		std::string ToString() const override
		{
            std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
            return ss.str();
		}

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}