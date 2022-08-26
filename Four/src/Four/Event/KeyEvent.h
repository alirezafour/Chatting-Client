#pragma once

#include "Event.h"

namespace four {

	class FOUR_API KeyEvent : public Event
	{
	public:
		inline int32_t GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int32_t keycode)
			: m_KeyCode(keycode) {}

	private:
		int32_t m_KeyCode;
		
	};

	class FOUR_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int32_t keycode, int32_t repeatCount)
			: KeyEvent(keycode), m_RepeatCount(repeatCount) {}

		EVENT_CLASS_TYPE(KeyPressed)

		inline int32_t GetRepeatCount() const { return m_RepeatCount; }


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << GetKeyCode() << "(( " << m_RepeatCount << " repeats ))";
			return ss.str();
		}

	private:
		int32_t m_RepeatCount;
	};

	class FOUR_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int32_t keycode)
			: KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KeyReleased)


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << GetKeyCode();
			return ss.str();
		}
	};

	class FOUR_API KeyTypedEvent : public KeyEvent
	{
	public:
		KeyTypedEvent(int32_t keycode)
			: KeyEvent(keycode) {}

		EVENT_CLASS_TYPE(KeyTyped)


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyTyped: " << GetKeyCode();
			return ss.str();
		}
	};

}