#pragma once

namespace four {

	class Deltatime
	{
	public:
		Deltatime(float time = 0.f)
			:m_Time(time)
		{
		}

		float GetSecond() const { return m_Time; }
		float GetMilliseconds() const { return m_Time * 1000.f; }

		operator float() const { return m_Time; }

	private:
		float m_Time;
	};
}