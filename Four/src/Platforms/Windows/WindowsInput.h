#pragma once
#include "Four\Input.h"

namespace four {

	class WindowInput : public Input
	{
	protected:
		bool IsKeyPressedImplementation(Key keycode) override;

		// mouse
		bool IsMouseButtonPressedImplementation(MouseKey button) override;
		std::pair<float, float> GetMouseXYImplementation() const override;
		float GetMouseXImplementation() const override;
		float GetMouseYImplementation() const override;

	};
}