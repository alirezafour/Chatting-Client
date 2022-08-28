#pragma once
#include "Four\Input.h"

namespace four {

	class WindowInput : public Input
	{
	protected:
		virtual bool IsKeyPressedImplementation(Key keycode);

		virtual bool IsMouseButtonPressedImplementation(MouseKey button) override;
		virtual std::pair<float, float> GetMouseXYImplementation() const override;
		virtual float GetMouseXImplementation() const override;
		virtual float GetMouseYImplementation() const override;

	};
}