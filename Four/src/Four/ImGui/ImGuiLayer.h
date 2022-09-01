#pragma once

#include "Four/Layer.h"

#include "Four/Event/MouseEvent.h"
#include "Four/Event/KeyEvent.h"
#include "Four/Event/ApplicationEvent.h"

namespace four {

	class FOUR_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach() override;
		void OnDetach() override;
		void OnImGuiRender() override;

		void Begin();
		void End();

	};

}
