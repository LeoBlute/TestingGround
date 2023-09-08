#include "pch.hpp"
#include "Core/Debug.hpp"
#include "Core/Application.hpp"
#include "Core/Graphics.hpp"

void Application::Start()
{
	//Little demonstration

	//Works similar to printf or std::cout,but it will only print/log to the Logger
	//Each Loggin Method has different color and different applications
	Debug::Info("Application started");
	//Debug::Warning("Application Warning");
	//Debug::Error("Application Error!");

	//Create a float,a integer and a boolean with following names
	Debug::GetFloat("Float");
	Debug::GetInteger("Integer");
	//Boolean will be created with true as default
	Debug::SetBoolean("Boolean", true);

	//Set a slider functionality for the "Float" variable
	InputStats float_stats;
	float_stats.currentType = InputType::Slider;
	float_stats.min = -10.0f;
	float_stats.max = 10.0f;
	Debug::SetFloatInputStats("Float", float_stats);

	//Set a drag functionality for the "Integer" variable
	InputStats integer_stats;
	integer_stats.currentType = InputType::Drag;
	integer_stats.speed = 0.1f;
	Debug::SetIntegerInputStats("Integer", integer_stats);

	//All variables can be erased if desired
	//Debug::EraseFloat("Float");
	//Debug::EraseInteger("Integer");
	//Debug::EraseBoolean("Boolean");
}

void Application::End()
{

}

void Application::Loop()
{

}

