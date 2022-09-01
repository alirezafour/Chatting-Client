#include "fourpch.h"
#include "ImGuiLayer.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "Four/Application.h"

// #Temperory
#include "GLFW/glfw3.h"
#include "glad/glad.h"

namespace four {

	#define FOUR_BIND_EVENT_FN(fn) std::bind(fn, this, std::placeholders::_1)

	ImGuiLayer::ImGuiLayer()
		:Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{
// 		ImGui_ImplOpenGL3_Shutdown();
// 		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.f;
			style.Colors[ImGuiCol_WindowBg].w = 1.f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

// 		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
// 		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//ImGui::ImGui_ImplGlfw_KeyToImGuiKey();

		//ImGui_ImplGlfw_InitForOpenGL(window, true);

		const char* glsl_version = "#version 100";
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init(glsl_version);
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();

		io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));

		// Render
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) // docking stuff
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}
	}

// 	void ImGuiLayer::OnUpdate()
// 	{
// 		
// 		ImGuiIO& io = ImGui::GetIO();
// 		Application& app = Application::Get();
// 
// 		io.DisplaySize = ImVec2(static_cast<float>(app.GetWindow().GetWidth()), static_cast<float>(app.GetWindow().GetHeight()));
// 
// 		io.DeltaTime = 1.f / 60.f;
// 
// 		ImGui_ImplOpenGL3_NewFrame();
// 		//ImGui_ImplGlfw_NewFrame();
// 		ImGui::NewFrame();
// 
// 		static bool show = true;
// 		ImGui::ShowDemoWindow(&show);
// 		
// 		ImGui::Render();
// 		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
// 	}
// 
// 	void ImGuiLayer::OnEvent(Event& event)
// 	{
// 		EventDispatcher dispatcher(event);
// 		dispatcher.Dispatch<MouseButtonPressedEvent>(FOUR_BIND_EVENT_FN(&ImGuiLayer::OnMouseButtonPressedEvent));
// 		dispatcher.Dispatch<MouseButtonReleasedEvent>(FOUR_BIND_EVENT_FN(&ImGuiLayer::OnMouseButtonReleasedEvent));
// 		dispatcher.Dispatch<MouseMovedEvent>(FOUR_BIND_EVENT_FN(&ImGuiLayer::OnMouseMoveEvent));
// 		dispatcher.Dispatch<MouseScrolledEvent>(FOUR_BIND_EVENT_FN(&ImGuiLayer::OnMouseScrollEvent));
// 		dispatcher.Dispatch<KeyPressedEvent>(FOUR_BIND_EVENT_FN(&ImGuiLayer::OnKeyPressedEvent));
// 		dispatcher.Dispatch<KeyReleasedEvent>(FOUR_BIND_EVENT_FN(&ImGuiLayer::OnKeyReleasedEvent));
// 		dispatcher.Dispatch<KeyTypedEvent>(FOUR_BIND_EVENT_FN(&ImGuiLayer::OnKeyTypedEvent));
// 		dispatcher.Dispatch<WindowResizeEvent>(FOUR_BIND_EVENT_FN(&ImGuiLayer::OnWindowResizedEvent));
// 	}
// 
// 	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MouseDown[e.GetMouseButton()] = true;
// 
// 		return false;
// 	}
// 
// 	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MouseDown[e.GetMouseButton()] = false;
// 
// 		return false;
// 	}
// 
// 	bool ImGuiLayer::OnMouseMoveEvent(MouseMovedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MousePos = ImVec2(e.GetX(), e.GetY());
// 
// 		return false;
// 	}
// 
// 	bool ImGuiLayer::OnMouseScrollEvent(MouseScrolledEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.MouseWheelH += e.GetXOffset();
// 		io.MouseWheel += e.GetYOffset();
// 
// 		return false;
// 	}
// 
// 	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.KeysDown[e.GetKeyCode()] = true;
// 
// 		io.KeyCtrl	= io.KeysDown[ImGuiKey_LeftCtrl]	|| io.KeysDown[ImGuiKey_RightCtrl];
// 		io.KeyShift	= io.KeysDown[ImGuiKey_LeftShift]	|| io.KeysDown[ImGuiKey_RightShift];
// 		io.KeyAlt	= io.KeysDown[ImGuiKey_LeftAlt]		|| io.KeysDown[ImGuiKey_RightAlt];
// 		io.KeySuper	= io.KeysDown[ImGuiKey_LeftSuper]	|| io.KeysDown[ImGuiKey_RightSuper];
// 
// 		return false;
// 	}
// 
// 	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.KeysDown[e.GetKeyCode()] = false;
// 
// 		return false;
// 	}
// 
// 	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		int keycode = e.GetKeyCode();
// 		if (keycode > 0 && keycode < 0x10000)
// 			io.AddInputCharacter(static_cast<unsigned short>(keycode));
// 
// 		return false;
// 	}
// 
// 	bool ImGuiLayer::OnWindowResizedEvent(WindowResizeEvent& e)
// 	{
// 		ImGuiIO& io = ImGui::GetIO();
// 		io.DisplaySize = ImVec2(static_cast<float>(e.GetWidth()), static_cast<float>(e.GetHeight()));
// 		io.DisplayFramebufferScale = ImVec2(1.f, 1.f);
// 		glViewport(0, 0, static_cast<GLsizei>(e.GetWidth()), static_cast<GLsizei>(e.GetHeight()));
// 
// 		return false;
// 	}

}