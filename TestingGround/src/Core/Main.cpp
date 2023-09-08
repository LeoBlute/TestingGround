#include "pch.hpp"
#include "Application.hpp"
#include "Window.hpp"
#include "Graphics.hpp"
#include "Time.hpp"
#include "Debug.hpp"
#include "imgui/imgui.h"

#define EXIT_ERROR -1
#define EXIT_SUCESS 0

#define ERROR_CATCHING_AND_REPORTING(FUNCTION)\
try {\
	FUNCTION();\
}\
catch (const std::exception& e) {\
	Debug::Error(e.what());\
}

int main(int argc, char* argv[])
{
	if (!Window::Init()) [[unlikely]]
	{
		std::cout << "Window system could not initialize" << std::endl;
		exit(EXIT_ERROR);
	}

	if (!Graphics::Init()) [[unlikely]]
	{
		std::cout << "Graphics system could not initialize" << std::endl;
		exit(EXIT_ERROR);
	}

	Graphics::SetColorStyle(Graphics::ColorStyle::Dark);

	
	ERROR_CATCHING_AND_REPORTING(Application::Start);
	
	//Application Quitting by window closing is handled with Window::CloseCallback
	while (true)
	{
		if(!Application::IsPaused())
			ERROR_CATCHING_AND_REPORTING(Application::Loop);

		Window::ClearScreen();

		Graphics::NewFrame();

		Graphics::Console::PushToRender();

		Graphics::Render();

		Window::ProcessInputs();
		Window::SwapBuffers();
	}
	//Anything beyound here will exit with an error
	exit(EXIT_ERROR);
	return EXIT_ERROR;
}

void Application::Quit()
{
	ERROR_CATCHING_AND_REPORTING(Application::End);

	Graphics::Terminate();

	Window::Terminate();

	exit(EXIT_SUCESS);
}