#include "pch.hpp"
#include "Graphics.hpp"
#include "Application.hpp"
#include "Window.hpp"
#include "Debug.hpp"
#include "GLFW/include/glfw3.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_stdlib.h"

#define GUI_VAR_IMP(TYPE_NAMING, TYPE)\
namespace Graphics {\
	namespace Console {\
		std::unordered_map<const char*, TYPE> Console##TYPE_NAMING##s;\
	}\
}\
TYPE Graphics::Console::Get##TYPE_NAMING(const char* name)\
{\
	return Console##TYPE_NAMING##s[name];\
}\
void Graphics::Console::Set##TYPE_NAMING(const char* name, TYPE value)\
{\
	Console##TYPE_NAMING##s[name] = value;\
}\
void Graphics::Console::Erase##TYPE_NAMING(const char* name)\
{\
	const auto it = Console##TYPE_NAMING##s.find(name);\
	if (it != Console##TYPE_NAMING##s.end())\
		Console##TYPE_NAMING##s.erase(it);\
}

#define GUI_VAR_INPUT_IMP(TYPE_NAMING)\
namespace Graphics {\
	namespace Console {\
		std::unordered_map<const char*, InputStats> Console##TYPE_NAMING##Inputs;\
	}\
}\
void Graphics::Console::Set##TYPE_NAMING##InputStats\
(const char* name, const InputStats& stats)\
{\
	Console##TYPE_NAMING##Inputs[name] = stats;\
}

namespace Graphics {
	namespace Console {
		struct Message {
			std::string text;
			Graphics::Color color;
			std::chrono::system_clock::time_point creationTime;
		};
		std::vector<std::unique_ptr<Message>> LoggerMessages;
		std::unordered_map<const char*, bool> ConsoleButtons;
	}
}

bool Graphics::Console::IsButtonPressed(const char* name)
{
	return ConsoleButtons[name];
}

void Graphics::Console::EraseButton(const char* name)
{
	const auto it = ConsoleButtons.find(name);
	if (it != ConsoleButtons.end())
		ConsoleButtons.erase(it);
}

void Graphics::Console::ClearLogger()
{
	LoggerMessages.clear();
}

GUI_VAR_IMP(Boolean, bool);
GUI_VAR_IMP(String, std::string);
GUI_VAR_IMP(Float, float);
GUI_VAR_IMP(Double, double);
GUI_VAR_IMP(Integer, int);

GUI_VAR_INPUT_IMP(Float);
GUI_VAR_INPUT_IMP(Integer);

void Graphics::SetColorStyle(ColorStyle style)
{
	switch (style)
	{
	case Graphics::Classic:
		ImGui::StyleColorsClassic();
		break;
	case Graphics::Dark:
		ImGui::StyleColorsDark();
		break;
	case Graphics::Light:
		ImGui::StyleColorsLight();
		break;
	default: [[unlikely]]
		break;
	}
}

bool Graphics::Init()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup Platform/Renderer backends
	GLFWwindow* rawWindow = static_cast<GLFWwindow*>(Window::GetRawWindow());
	ImGui_ImplGlfw_InitForOpenGL(rawWindow, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	constexpr float font_scale = 1.2f;
	ImFontConfig cfg;
	cfg.SizePixels = 13 * font_scale;
	ImGui::GetIO().Fonts->AddFontDefault(&cfg)->Scale = font_scale;
	return true;
}

void Graphics::Terminate()
{
	Console::LoggerMessages.clear();

	Console::ConsoleStrings.clear();
	Console::ConsoleBooleans.clear();
	Console::ConsoleStrings.clear();
	Console::ConsoleFloats.clear();
	Console::ConsoleDoubles.clear();
	Console::ConsoleIntegers.clear();

	Console::ConsoleFloatInputs.clear();
	Console::ConsoleIntegerInputs.clear();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Graphics::NewFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void Graphics::Render()
{
	//Rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	//Allow elements(imgui windows) to be dragged outside of the main Window context bounds
	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
	}

	Window::MakeContextCurrent();
}

void Graphics::Console::PushToRender()
{
	int windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;
	windowFlags |= ImGuiWindowFlags_NoMove;
	windowFlags |= ImGuiWindowFlags_NoCollapse;
	windowFlags |= ImGuiWindowFlags_NoSavedSettings;
	windowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;
	windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;
	windowFlags |= ImGuiWindowFlags_NoNavFocus;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	const float halfWidth = viewport->Size.x / 2;
	constexpr float button_bar_space = 40.0f;

	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize({ halfWidth / 2, viewport->Size.y - button_bar_space });

	if (ImGui::Begin("Console", NULL, windowFlags))
	{
		for (auto& b_pair : ConsoleButtons)
		{
			b_pair.second = ImGui::Button(b_pair.first);
		}
		for (auto& b_pair : ConsoleBooleans)
		{
			ImGui::Checkbox(b_pair.first, &b_pair.second);
		}
		for (auto& b_pair : ConsoleStrings)
		{
			ImGui::InputText(b_pair.first, &b_pair.second);
		}
		for (auto& b_pair : ConsoleFloats)
		{
			const char* name = b_pair.first;
			const InputStats& input_stats = ConsoleFloatInputs[name];
			switch (input_stats.currentType)
			{
			case Graphics::Console::Default:

				ImGui::InputFloat(name, &b_pair.second);
				break;
			case Graphics::Console::Drag:
				ImGui::DragFloat(name, &b_pair.second,
					input_stats.speed);
				break;
			case Graphics::Console::Slider:
				ImGui::SliderFloat(name, &b_pair.second,
					input_stats.min, input_stats.max);
				break;
			default: [[unlikely]]
				break;
			}
		}
		for (auto& b_pair : ConsoleDoubles)
		{
			ImGui::InputDouble(b_pair.first, &b_pair.second);
		}
		for (auto& b_pair : ConsoleIntegers)
		{
			const char* name = b_pair.first;
			const InputStats& input_stats = ConsoleIntegerInputs[name];
			switch (input_stats.currentType)
			{
			case Graphics::Console::Default:
				Debug::Info("Default");
				ImGui::InputInt(name, &b_pair.second);
				break;
			case Graphics::Console::Drag:
				ImGui::DragInt(name, &b_pair.second,
					input_stats.speed);
				break;
			case Graphics::Console::Slider:
				ImGui::SliderInt(name, &b_pair.second,
					input_stats.min, input_stats.max);
				break;
			default: [[unlikely]]
					   break;
			}
		}

		ImGui::End();
	}

	ImGui::SetNextWindowPos({ viewport->Pos.x + (halfWidth * 0.5f), viewport->Pos.y });
	ImGui::SetNextWindowSize({ halfWidth * 1.5f, viewport->Size.y - button_bar_space });

	if (ImGui::Begin("Logger", NULL, windowFlags))
	{
		for (const std::unique_ptr<Message>& ptr : LoggerMessages)
		{
			Message* msg = ptr.get();
			if (!msg)
				continue;

			Color color = msg->color;
			const char* txt = msg->text.c_str();
			ImGui::TextColored(
				ImVec4(color.r, color.g, color.b, color.a), txt);
		}
		ImGui::End();
	}

	windowFlags |= ImGuiWindowFlags_NoTitleBar;
	ImGui::SetNextWindowPos
	({ viewport->Pos.x, viewport->Pos.y + viewport->Size.y - button_bar_space });
	ImGui::SetNextWindowSize({ viewport->Size.x , button_bar_space });
	if (ImGui::Begin("Pause Button Bar", NULL, windowFlags))
	{
		const char* button_text = Application::IsPaused() ? "Unpause" : "Pause";

		if (ImGui::Button("Clear Logger"))
			ClearLogger();
		if (ImGui::Button("Clear Console"))
			ClearConsole();
		if (ImGui::Button(button_text))
		{
			Application::SetPause(!(Application::IsPaused()));
		}
		ImGui::End();
	}
}

void Graphics::Console::ClearConsole()
{
	ConsoleBooleans.clear();
	ConsoleButtons.clear();
	ConsoleDoubles.clear();
	ConsoleFloats.clear();
	ConsoleIntegers.clear();
	ConsoleStrings.clear();
}

void Graphics::Console::LogMessage(const char* msg, const Color& color)
{
	LoggerMessages.push_back(std::make_unique<Message>(Message{ msg, color, std::chrono::system_clock::now() }));
	auto sortAlgorithm = [](const std::unique_ptr<Message>& a, const std::unique_ptr<Message>& b) {
		return a->creationTime > b->creationTime;
		};

	std::sort(LoggerMessages.begin(), LoggerMessages.end(), sortAlgorithm);
}

