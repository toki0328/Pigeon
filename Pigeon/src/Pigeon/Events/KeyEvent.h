#pragma once

#include "Event.h"


namespace Pigeon {

	// 键盘事件基类
	class PIGEON_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(int keycode)
		    : m_KeyCode(keycode) {}

        int m_KeyCode;
	};

	// 键盘按压事件，考虑重复按键的情况
	class PIGEON_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() { return m_RepeatCount; }

		std::string ToString() const override 
		{
			std::stringstream ss;
            ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
    private:
        int m_RepeatCount;
	};

	// 键盘释放事件
	class PIGEON_API KeyReleasedEvent : public KeyEvent
	{
    public:
        KeyReleasedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_KeyCode;
            return ss.str();
		}

        EVENT_CLASS_TYPE(KeyReleased)
	};

	class PIGEON_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int keycode)
			: KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTypedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyTyped)
	};
}